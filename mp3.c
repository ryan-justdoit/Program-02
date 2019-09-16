#include "header.h"
#include "common.h"
void play(dlinklist *now)
{
        if((flag_now == PLAY || flag_now == STOP) && option == PLAY)
        {
                printf("已经在播放中了...\n");
        }
        else
        {
                bzero(buf,100);
                snprintf(buf,sizeof(buf),"madplay -a -10 '%s' &",(*now)->name);
                system(buf);
                flag_now = PLAY;
                printf("执行 [%d]:PLAY 完毕!\n",flag_now);
                printf("正在播放 %s\n",(*now)->name);
        }
}

void stop(dlinklist *now)
{
        if(flag_now == PLAY)
        {
                printf("正在暂停...\n");
                system("killall -STOP madplay &");
                flag_now = STOP;
                printf("执行 [%d]:STOP 完毕!\n",flag_now);
                printf("暂停播放 %s\n",(*now)->name);
        }
        else if(flag_now == STOP)
        {
                printf("正在恢复播放...\n");
                system("killall -CONT madplay &");
                flag_now = PLAY;
                printf("执行 [%d]:PLAY 完毕!\n",flag_now);
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
        if(flag_now == PLAY)
        {
                printf("正在退出...\n");
                system("killall madplay &");
                flag_now = EXITT;
                printf("执行 [%d]:EXITT 完毕!\n",flag_now);
                printf("退出播放 %s\n",(*now)->name);
        }
        else if(flag_now == STOP)
        {
                stop(&(*now));
                system("killall madplay &");
                flag_now = EXITT;
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
                flag_now = NEXT;
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
                flag_now = Prior;
                //(*now) = (*now)->prev;
                play(&(*now));
        }

}
