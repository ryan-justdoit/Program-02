#include "header.h"
#include "common.h"
void background(int argc,char **argv)
{
	if(argc != 2)
	{
		printf("�÷�: %s <BMPͼƬ>\n", argv[0]);
		exit(0);
	}

	display();
	freelcd();

}
