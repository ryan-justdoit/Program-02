#include "header.h"
#include "common.h"

int flag = 0;
char buf[100];
void play(dlinklist *now)
{
        if((flag == PLAY || flag == STOP) && option == PLAY)
        {
                printf("已经在播放中了...\n");
        }
        else
        {
                //printf("%d\n",__LINE__);
                bzero(buf,100);
                //printf("%d\n",__LINE__);
                snprintf(buf,sizeof(buf),"madplay -a -10 '%s' &",(*now)->name);
                //printf("%d\n",__LINE__);
                system(buf);
                //printf("%d\n",__LINE__);
                flag = PLAY;
                //printf("%d\n",__LINE__);
                printf("执行 [%d]:PLAY 完毕!\n",flag);
                //printf("%d\n",__LINE__);
                printf("正在播放 %s\n",(*now)->name);
                //printf("%d\n",__LINE__);
                //printf("按时发布三分\n");
        }
}

void stop(dlinklist *now)
{
        if(flag == PLAY)
        {
                printf("正在暂停...\n");
                system("killall -STOP madplay &");
                flag = STOP;
                printf("执行 [%d]:STOP 完毕!\n",flag);
                printf("暂停播放 %s\n",(*now)->name);
        }
        else if(flag == STOP)
        {
                printf("正在恢复播放...\n");
                system("killall -CONT madplay &");
                flag = PLAY;
                printf("执行 [%d]:PLAY 完毕!\n",flag);
                printf("正在播放 %s\n",(*now)->name);
        }
        else
        {
                printf("现在还不能暂停/播放!\n");
                printf("请先播放一首歌~\n");
        }

}

void exitt(dlinklist *now)
{
        if(flag == PLAY)
        {
                printf("正在退出...\n");
                system("killall madplay &");
                flag = EXITT;
                printf("执行 [%d]:EXITT 完毕!\n",flag);
                printf("退出播放 %s\n",(*now)->name);
        }
        else if(flag == STOP)
        {
                stop(&(*now));
                system("killall madplay &");
                flag = EXITT;
                printf("最终结果:退出完毕.\n");
        }
        else
        {
                printf("现在还不能退出!\n");
                printf("请先播放一首歌~\n");
        }

}

void next(dlinklist *now,dlinklist head)
{
        if((*now)->next == head)
        {
                printf("这已经是最后一首歌，无法再播放下一首!!!\n");
        }
        else
        {
                exitt(&(*now));
                usleep(100*1000);
                (*now) = (*now)->next;
                printf("正在下一首 %s\n",(*now)->name);
                flag = NEXT;
                //(*now) = (*now)->next;
                play(&(*now));
        }
}

void prior(dlinklist *now,dlinklist head)
{
        if((*now)->prev == head)
        {
                printf("这已经是第一首歌，无法再播放上一首!!!\n");
        }
        else
        {
                exitt(&(*now));
                usleep(100*1000);
                (*now) = (*now)->prev;
                printf("正在上一首 %s\n",(*now)->name);
                flag = Prior;
                //(*now) = (*now)->prev;
                play(&(*now));
        }

}
