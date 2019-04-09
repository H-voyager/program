#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
	int Value;
	struct Node* next;
	struct Node* random;
}Node;

Node* CreateNode(int val)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->Value = val;
	node->next = node->random = NULL;
	return node;
}

void Print(Node* head)
{
	for (Node* cur = head; cur != NULL; cur = cur->next)
	{
		printf("0x%p(%d,random:%p) -->", cur, cur->Value, cur->random);
	}
	printf("NULL\n");
}

Node* copyRandomList(Node* head)
{
	if (head = NULL)
	{
		return NULL;
	}
	
	//复制新节点,插入到老节点后面
	Node* cur = head;
	while (cur != NULL)
	{
		Node* NewNode = (Node*)malloc(sizeof(Node));
		NewNode->Value = cur->Value;
		NewNode->random = NULL;


		//插入到老节点后面
		NewNode->next = cur->next;
		cur->next = NewNode;
		//更新cur节点,指向插入节点的后方
		cur = NewNode->next;
	}

	//根据老节点的random复制新节点的random
	cur = head;

	while (cur !=NULL)
	{
		if (cur->random != NULL)
		{
			cur->next->random = cur->random->next;
		}
		cur = cur->next->next;
	}

	//把链表拆分成两个
	cur = head;
	Node* newHead =head->next;
	while (cur != NULL)
	{
		Node* newNode = cur->next;
		cur->next = newNode->next;
		if (newNode->next !=NULL)
		{
			newNode->next = newNode->next->next;
		}
		cur = cur->next;
	}

	return newHead;
}


void Test()
{
	Node* n1 = CreateNode(1);
	Node* n2 = CreateNode(2);
	Node* n3 = CreateNode(3);
	Node* n4 = CreateNode(4);

	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n1->random = n3;
	n2->random = n1;
	n3->random = n3;

	Print(n1);
	Node* rn1 = copyRandomList(n1);
	Print(rn1);
}