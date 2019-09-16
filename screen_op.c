#include "header.h"
#include "common.h"

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
				//	printf("��ָ������!\n");
					x_first = x_second;
					y_first = y_second;
				//	printf("��һ�ΰ��µ����꣨%d,%d��\n",x_first,y_first);
				}
				if(buf.value == 0)
				{
				//	printf("��ָ�ɿ���!\n");
				//	printf("�ɿ�ʱ�����꣨%d,%d��\n",x_second,y_second);
					x_diff = x_second - x_first;
					y_diff = y_second - y_first;
				//	printf("���� x= %d,y= %d\n",x_diff,y_diff);
					if(PLAY_BEGIN_TOUCH)
					{
						if(PLAY_END_TOUCH)
						{
							printf("����!\n");
							return PLAY;
						}
					}
					else if(STOP_BEGIN_TOUCH)
					{
						if(STOP_END_TOUCH)
						{
							printf("��ͣ!/�ָ�\n");
							return STOP;
						}
					}
					else if(EXITT_BEGIN_TOUCH)
					{
						if(EXITT_END_TOUCH)
						{
							printf("�˳�!\n");
							return EXITT;
						}
					}
					else if(NEXT_BEGIN_TOUCH)
					{
						if(NEXT_END_TOUCH)
						{
							printf("��һ��!\n");
							return NEXT;
						}
					}
					else if(Prior_BEGIN_TOUCH)
					{
						if(Prior_END_TOUCH)
						{
							printf("��һ��!\n");
							return Prior;
						}
					}
					else
					{
						printf("���ڴ�����Ч��Χ!\n");
					}

				}
			}
		}
	}

}
