/*函数名：linelink.h
 *功能：存放链表
 *
 *
 *
 */

#ifdef DL_NODE_TYPE
#define DL_NODE_TYPE int
#endif

//typedef DL_NODE_TYPE datatype;

typedef struct node
{
	char * name;

	struct node *prev;
	struct node *next;

}dlinknode,*dlinklist;



