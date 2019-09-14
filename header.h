#ifndef __HEADER_
#define __HEADER_
#endif // __HEADER_

typedef struct node
{
	char * name;

	struct node *prev;
	struct node *next;

}dlinknode,*dlinklist;


dlinklist init_lianbiao(char *name,dlinklist head);
dlinklist init_list();
dlinklist catalogue(int argc,char **argv);
void background(int argc,char **argv);


static int lcd;
static int lcd_w;
static int lcd_h;
static int lcd_bpp;
static int screen_size;

static struct fb_var_screeninfo vsinfo;

static char *lcdmem;

static bool first = true;
