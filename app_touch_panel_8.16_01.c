#include "common.h"

int main()
{
	int tp = open("/dev/input/event0",O_RDWR);

	struct input_event buf;
	
	bool ydone = true;
	bool xdone = false;

	int x_first = 0;
	int y_first = 0;

	int x_second = 0;
	int y_second = 0;

	while(1)
	{
		bzero(&buf,sizeof(struct input_event));
		read(tp,&buf,sizeof(buf));

		if(buf.type == EV_ABS)
		{
			if(buf.code == ABS_X && ydone)
			{
				x_second = buf.value;
				xdone 	 = true;
				ydone	 = false;
				printf("(%d,",x_second);
			}

			if(buf.code == ABS_Y && xdone)
			{
				y_second = buf.value;
				xdone	 = false;
				ydone	 = true;
				printf("%d)\n",y_second);
			}
		}

		if(buf.type == EV_KEY)
		{
		//	if(buf.code == BTN_TOUCH)
		//	{
				if(buf.value > 0)
				{
					printf("手指按下了!\n");
					x_first = x_second;
					y_first = y_second;
					printf("第一次按下的坐标 (%d,%d)\n",x_first,y_first);
				}
				if(buf.value == 0)
				{
					printf("手指松开了!\n");
					printf("松开时的坐标 (%d,%d)\n",x_second,y_second);
					x_first = x_second - x_first;
					y_first = y_second - y_first;
					printf("距离 x= %d,y= %d\n",x_first,y_first);
					if(x_first > 0)
						printf("向右移动了　%d　像素\n",x_first);
					if(x_first < 0)
						printf("向左移动了　%d　像素\n",-x_first);
				}
		//	}
		}
	}

}
