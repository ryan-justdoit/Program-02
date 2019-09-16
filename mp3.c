#include "header.h"
#include "common.h"
void play(dlinklist *now)
{
        if((flag_now == PLAY || flag_now == STOP) && option == PLAY)
        {
                printf("�Ѿ��ڲ�������...\n");
        }
        else
        {
                bzero(buf,100);
                snprintf(buf,sizeof(buf),"madplay -a -10 '%s' &",(*now)->name);
                system(buf);
                flag_now = PLAY;
                printf("ִ�� [%d]:PLAY ���!\n",flag_now);
                printf("���ڲ��� %s\n",(*now)->name);
        }
}

void stop(dlinklist *now)
{
        if(flag_now == PLAY)
        {
                printf("������ͣ...\n");
                system("killall -STOP madplay &");
                flag_now = STOP;
                printf("ִ�� [%d]:STOP ���!\n",flag_now);
                printf("��ͣ���� %s\n",(*now)->name);
        }
        else if(flag_now == STOP)
        {
                printf("���ڻָ�����...\n");
                system("killall -CONT madplay &");
                flag_now = PLAY;
                printf("ִ�� [%d]:PLAY ���!\n",flag_now);
                printf("���ڲ��� %s\n",(*now)->name);
        }
        else
        {
                printf("���ڻ�������ͣ/����!\n");
                printf("���Ȳ���һ�׸�~\n");
        }

}

void exitt(dlinklist *now)
{
        if(flag_now == PLAY)
        {
                printf("�����˳�...\n");
                system("killall madplay &");
                flag_now = EXITT;
                printf("ִ�� [%d]:EXITT ���!\n",flag_now);
                printf("�˳����� %s\n",(*now)->name);
        }
        else if(flag_now == STOP)
        {
                stop(&(*now));
                system("killall madplay &");
                flag_now = EXITT;
                printf("���ս��:�˳����.\n");
        }
        else
        {
                printf("���ڻ������˳�!\n");
                printf("���Ȳ���һ�׸�~\n");
        }

}

void next(dlinklist *now,dlinklist head)
{
        if((*now)->next == head)
        {
                printf("���Ѿ������һ�׸裬�޷��ٲ�����һ��!!!\n");
        }
        else
        {
                exitt(&(*now));
                usleep(100*1000);
                (*now) = (*now)->next;
                printf("������һ�� %s\n",(*now)->name);
                flag_now = NEXT;
                //(*now) = (*now)->next;
                play(&(*now));
        }
}

void prior(dlinklist *now,dlinklist head)
{
        if((*now)->prev == head)
        {
                printf("���Ѿ��ǵ�һ�׸裬�޷��ٲ�����һ��!!!\n");
        }
        else
        {
                exitt(&(*now));
                usleep(100*1000);
                (*now) = (*now)->prev;
                printf("������һ�� %s\n",(*now)->name);
                flag_now = Prior;
                //(*now) = (*now)->prev;
                play(&(*now));
        }

}
