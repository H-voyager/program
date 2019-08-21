//queue队列
#pragma once
#include <stdio.h>
#include <stdlib.h>

//定义节点
typedef struct Node
{
	int value;
	struct Node* next;
}Node;

//定义
typedef struct
{
	Node* head; //front
	Node* last;   //rear
}Queue;

//尾插
void QueueListInit(Queue* q)
{
	q->head = q->last = NULL;
}

void QueuePush(Queue* q, int v)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->value = v;
	node->next = NULL;
	if (q -> head = NULL)
	{
		q->head = node;
	}
	else
	{
		q->last->next = node;
		q->last = node;
	}
}

//头删
void PopFront(Queue* q)
{
	Node* second = q->last->next;
	free(q->head);
	q->head = second;

	if (q->head == NULL)
	{
		q->last = NULL;
	}
}

int QueueFront(Queue* q)
{
	return q->head->value;
}

int QueueSize(Queue *q)
{
	int size = 0;
	for ( Node* n = q->head; i !=NULL ; n->next)
	{
		size++;
	}
	return size;
}

bool QueueEmpty(Queue *q)
{
	return q->head == NULL;
}