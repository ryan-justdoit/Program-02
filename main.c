#include "common.h"
#include "bmp.h"

#include "header.h"

#define PLAY_BEGIN_TOUCH ( ((x_first>160) && (x_first<300)) && ((y_first>180) && (y_first<320)) )
#define PLAY_END_TOUCH   ( x_diff<140 && y_diff<140 )
#define PLAY 1

#define STOP_BEGIN_TOUCH ( ((x_first>340) && (x_first<480)) && ((y_first>180) && (y_first<320)) )
#define STOP_END_TOUCH   ( x_diff<140 && y_diff<140 )
#define STOP 2

#define EXIT_BEGIN_TOUCH ( ((x_first>510) && (x_first<650)) && ((y_first>180) && (y_first<320)) )
#define EXIT_END_TOUCH   ( x_diff<140 && y_diff<140 )
#define EXIT 3

#define BACK_BEGIN_TOUCH ( ((x_first>0) && (x_first<100)) && ((y_first>0) && (y_first<100)) )
#define BACK_END_TOUCH   ( x_diff<100 && y_diff<100 )
#define BACK 4

#define NEXT_BEGIN_TOUCH ( ((x_first>700) && (x_first<800)) && ((y_first>0) && (y_first<100)) )
#define NEXT_END_TOUCH   ( x_diff<100 && y_diff< 100)
#define NEXT 5


int screen_op();


int main(int argc, char **argv) // ./main xxx.bmp 100 50
{
        pid_t pid;
        int flag = 0;
        int option;

        bool read_op = 1;
        char buf[100];
        bzero(buf,100);
	// 1,显示背景
	background(argc,argv);

        // 2,读取歌曲目录
        dlinklist head = NULL;
        head = catalogue(argc,argv);
        dlinklist tmp = head->next;


	// 3,判断屏幕动作
	printf("等待屏幕操作...\n");
	while(1)
        {
                if(read_op == 1)
                {
                       option = screen_op();
                }

                if(option == PLAY)
                {
                        
                        flag = PLAY;
                        snprintf(buf,sizeof(buf),"madplay -a -10 '%s' &",head->next->name);
                        system(buf);
                }
                else if(option == STOP)
                {
                        if(flag == PLAY)
                        {
                              // 暂停
                                flag = STOP;
                                printf("正在暂停...\n");
                                system("killall -STOP madplay &");
                        }
                        else if(flag == STOP)
                        {
                                // 恢复
                                flag = PLAY;
                                printf("正在恢复播放...\n");
                                system("killall -CONT madplay &");
                        }
                        else
                        {
                                printf("请先开始播放!\n");
                        }
                }
                else if( option == EXIT )
                {
                        //退出
                        /*
                        if(flag == NEXT)
                        {
                                system("killall -9 madplay &");
                                option = PLAY;
                                printf("退出这一首\n");
                                continue;
                        }
                        */
                        flag = EXIT;
                        printf("正在退出...\n");
                        system("killall -9 madplay &");
                }
                else if( option == NEXT )
                {
                        // 下一首
                        flag = NEXT;
                        dlinklist now = tmp->next;
                        if( now != head )
                        {
                                bzero(buf,100);
                                snprintf(buf,sizeof(buf),"madplay -a -10 '%s' &",now->name);
                                system(buf);
                                printf("buf =%s\n",buf);

                                tmp = now;
                        }
                        else
                        {
                                bzero(buf,100);
                                snprintf(buf,sizeof(buf),"madplay -a -10 '%s' &",head->next->name);
                                printf("第一首：%s\n",head->next->name);
                                system(buf);
                                printf("该列表播完，回到第一首!\n");
                                printf("buf =%s\n",buf);
                        }


                }
        }

}

dlinklist catalogue(int argc,char **argv)
{
	// 1，确保有一个参数，并且是目录
	if(argc != 2)
	{
		printf("标准用法 %s + 目录\n",argv[0]);
		exit(0);
	}

	struct stat info;
	bzero(&info, sizeof(info));

	if(stat(argv[1], &info) == -1)
	{
		perror("获取指定文件属性失败");
		exit(0);
	}

	if((info.st_mode&S_IFMT) != S_IFDIR)
	{
		printf("给我的不是目录！走人！\n");
		exit(0);
	}

	// 2，打开目录，并循环地读取里面的目录项
	DIR *dp = opendir(argv[1]);
	chdir(argv[1]);
	struct dirent *ep;

        dlinklist head = init_list();

	while(1)
	{
		ep = readdir(dp);

		// 读完收工
		if(ep == NULL)
			break;

		// 跳过所有隐藏文件
		if(ep->d_name[0] == '.')
			continue;

                if(strstr(ep->d_name, ".mp3"))
                {
                        head = init_lianbiao(ep->d_name,head);
                }



                printf("head->next->name2 = %s\n",head->next->name);
		// 获取当前文件的stat信息
		bzero(&info, sizeof(info));
		stat(ep->d_name, &info);

	//	printf("%s: %ld\n", ep->d_name, info.st_size);
	}

	// 3，释放相应的资源
		//closedir(dp);

	return head;
}

void background(int argc,char **argv) // ./main xxx.bmp 100 50
{
	if(argc != 2)
	{
		printf("用法: %s <BMP图片>\n", argv[0]);
		exit(0);
	}

	display();
	freelcd();

}

int screen_op()
{
	int tp = open("/dev/input/event0",O_RDWR);

	struct input_event buf;

	bool ydone = true;
	bool xdone = false;

	int x_first = 0;
	int y_first = 0;

	int x_second = 0;
	int y_second = 0;

	int x_diff = 0;
	int y_diff = 0;

	while(1)
	{
		bzero(&buf,sizeof(struct input_event));
		read(tp,&buf,sizeof(buf));

		if(buf.type == EV_ABS)
		{
			if(buf.code == ABS_X && ydone)
			{
				x_second = buf.value*800/1024;
				xdone	 = true;
				ydone	 = false;
				printf("(%d,",x_second);
			}

			if(buf.code == ABS_Y && xdone)
			{
				y_second = buf.value*480/600;
				xdone 	 = false;
				ydone	 = true;
				printf("%d)\n",y_second);
			}
		}
		if(buf.type == EV_KEY)
		{
			if(buf.code == BTN_TOUCH)
			{
				if(buf.value > 0)
				{
					printf("手指按下了!\n");
					x_first = x_second;
					y_first = y_second;
					printf("第一次按下的坐标（%d,%d）\n",x_first,y_first);
				}
				if(buf.value == 0)
				{
					printf("手指松开了!\n");
					printf("松开时的坐标（%d,%d）\n",x_second,y_second);
					x_diff = x_second - x_first;
					y_diff = y_second - y_first;
					printf("距离 x= %d,y= %d\n",x_diff,y_diff);
					if(PLAY_BEGIN_TOUCH)
					{
						if(PLAY_END_TOUCH)
						{
							printf("播放!\n");
							return PLAY;
						}
					}
					else if(STOP_BEGIN_TOUCH)
					{
						if(STOP_END_TOUCH)
						{
							printf("暂停!/恢复\n");
							return STOP;
						}
					}
					else if(EXIT_BEGIN_TOUCH)
					{
						if(EXIT_END_TOUCH)
						{
							printf("退出!\n");
							return EXIT;
						}
					}
					else if(NEXT_BEGIN_TOUCH)
					{
						if(NEXT_END_TOUCH)
						{
							printf("下一首!\n");
							return NEXT;
						}
					}
					else if(BACK_BEGIN_TOUCH)
					{
						if(BACK_END_TOUCH)
						{
							printf("上一首!\n");
							return BACK;
						}
					}
					else
					{
						printf("请在触摸有效范围!\n");
					}

				}
			}
		}
	}

}








