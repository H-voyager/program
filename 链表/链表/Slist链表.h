#pragma once
//C/C++杂注，只要在头文件的最开始加入这条杂注，就能够保证头文件只被编译一次

#include <stdlib.h>
#include <assert.h>

//链表的节点
typedef struct Node
{
	int value;
	struct Node* next;
}Node;

//初始化链表就是一条空链表,一个节点都没有
void SListInit(Node ** ppFirst)
{
	*ppFirst = NULL;
}

//销毁链表
void SListDestory(Node *first)
{
	Node *next;
	for (Node *cur = first; cur != NULL; cur = next)
	{
		next = cur->next;
		free (cur);
	}
}

//头插 O(1)
void SListPushFront(Node **ppFirst, int v)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;

	node->next = *ppFirst;
	*ppFirst = node;
}

//头删O(1)
void SListPopFront(Node **ppFirst)
{
	assert(*ppFirst != NULL);
	//*ppFirst指向第一个节点
	Node *next = (*ppFirst)->next;
	free(*ppFirst);
	*ppFirst = next;
}

//尾插O(n)
void SListPushBack(Node** ppFirst, int v)
{
	if (*ppFirst == NULL)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		node->value = v;

		node->next = *ppFirst;
		*ppFirst = node;
	}

	//找到最后一个节点,隐含链表中至少有一个节点\
	//current现在的
	Node  *cur = *ppFirst;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}

	//此时cur是最后一个节点
	Node *node = (Node*)malloc(sizeof(Node));
	node->value = v;
	node->next = NULL;

	//让原来的最后一个节点的 next = 新的节点;
	cur->next = node;
}



