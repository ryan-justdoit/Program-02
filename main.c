#include "common.h"
#include "bmp.h"
#include "header.h"

int option;
void end(int arg)
{
        system("killall madplay &");
        printf("退出播放.\n");
        printf("退出程序.\n");
        exit(0);
}

int main(int argc, char **argv) // ./main xxx.bmp 100 50
{
        signal(SIGINT,end);

	// 1,显示背景
	background(argc,argv);

        // 2,读取歌曲目录
        dlinklist head = NULL;
        head = catalogue(argc,argv);
        dlinklist now = head->next;


	// 3,判断屏幕动作
	printf("等待屏幕操作...\n");
	while(1)
        {
                option = screen_op();

                switch(option)
                {
                        case PLAY :play(&now); break;
                        case STOP :stop(&now); break;
                        case EXITT:exitt(&now);break;
                        case Prior:prior(&now,head);break;
                        case NEXT :next(&now,head); break;
                }
        }
}











