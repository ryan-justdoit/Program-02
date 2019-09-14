/*函数名：init_lianbiao.c
 *功能：放入读到的图片名字
 *
 *
 */




#include "common.h"

#include "header.h"


void list_add_tail(dlinklist new,dlinklist head)
{
	dlinklist tail;
	for(tail = head->next; tail->next != head; tail=tail->next);

	new->prev = tail;
	new->next = head;
	tail->next = new;
	head->prev = new;
}


dlinklist new_node(char *name)
{
	dlinklist new = calloc(1,sizeof(dlinknode));

	if(new != NULL)
	{
		new->name = name;
		new->prev = new->next = new;
	}

	return new;

}

dlinklist init_list()
{
	dlinklist head = calloc(1,sizeof(dlinknode));

	if(head != NULL)
	{
		head->prev = head->next = head;
	}

	return head;
}


bool is_empty(dlinklist head)
{
	return head == head->next;
}

void show(dlinklist head)
{
	if(is_empty(head))
	{
		return;
	}
	dlinklist tmp;
	for(tmp=head->next; tmp != head; tmp = tmp->next)
	{
		printf("%s\t",tmp->name);
	}
	printf("\n");
}


dlinklist init_lianbiao(char *name,dlinklist head)
{
	//创建新节点new
	dlinklist new = new_node(name);

	//将新节点new插入到链表的末尾
	list_add_tail(new,head);

	show(head);

        printf("head->next->name1 = %s\n",head->next->name);


	return head;
}
