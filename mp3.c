#include "header.h"
#include "common.h"

int flag = 0;
char buf[100];
void play(dlinklist *now)
{
        if((flag == PLAY || flag == STOP) && option == PLAY)
        {
                printf("�Ѿ��ڲ�������...\n");
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
                printf("ִ�� [%d]:PLAY ���!\n",flag);
                //printf("%d\n",__LINE__);
                printf("���ڲ��� %s\n",(*now)->name);
                //printf("%d\n",__LINE__);
                //printf("��ʱ��������\n");
        }
}

void stop(dlinklist *now)
{
        if(flag == PLAY)
        {
                printf("������ͣ...\n");
                system("killall -STOP madplay &");
                flag = STOP;
                printf("ִ�� [%d]:STOP ���!\n",flag);
                printf("��ͣ���� %s\n",(*now)->name);
        }
        else if(flag == STOP)
        {
                printf("���ڻָ�����...\n");
                system("killall -CONT madplay &");
                flag = PLAY;
                printf("ִ�� [%d]:PLAY ���!\n",flag);
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
        if(flag == PLAY)
        {
                printf("�����˳�...\n");
                system("killall madplay &");
                flag = EXITT;
                printf("ִ�� [%d]:EXITT ���!\n",flag);
                printf("�˳����� %s\n",(*now)->name);
        }
        else if(flag == STOP)
        {
                stop(&(*now));
                system("killall madplay &");
                flag = EXITT;
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
                flag = NEXT;
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
                flag = Prior;
                //(*now) = (*now)->prev;
                play(&(*now));
        }

}
