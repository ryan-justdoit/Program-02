#ifndef __HEADER_

#define PLAY_BEGIN_TOUCH ( ((x_first>160) && (x_first<300)) && ((y_first>180) && (y_first<320)) )
#define PLAY_END_TOUCH   ( x_diff<140 && y_diff<140 )
#define PLAY 1

#define STOP_BEGIN_TOUCH ( ((x_first>340) && (x_first<480)) && ((y_first>180) && (y_first<320)) )
#define STOP_END_TOUCH   ( x_diff<140 && y_diff<140 )
#define STOP 2

#define EXITT_BEGIN_TOUCH ( ((x_first>510) && (x_first<650)) && ((y_first>180) && (y_first<320)) )
#define EXITT_END_TOUCH   ( x_diff<140 && y_diff<140 )
#define EXITT 3

#define Prior_BEGIN_TOUCH ( ((x_first>0) && (x_first<100)) && ((y_first>0) && (y_first<100)) )
#define Prior_END_TOUCH   ( x_diff<100 && y_diff<100 )
#define Prior 4

#define NEXT_BEGIN_TOUCH ( ((x_first>700) && (x_first<800)) && ((y_first>0) && (y_first<100)) )
#define NEXT_END_TOUCH   ( x_diff<100 && y_diff< 100)
#define NEXT 5

int screen_op();
extern int option;

typedef struct node
{
	char * name;

	struct node *prev;
	struct node *next;

}dlinknode,*dlinklist;


dlinklist init_lianbiao(char *name,dlinklist head);
dlinklist init_list();
dlinklist catalogue(int argc,char **argv);
void display();
void freelcd();
void background(int argc,char **argv);

void play(dlinklist *now);
void stop(dlinklist *now);
void exitt(dlinklist *now);
void prior(dlinklist *now,dlinklist head);
void next(dlinklist *now,dlinklist head);


#define __HEADER_
#endif // __HEADER_


