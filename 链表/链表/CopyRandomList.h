#program once

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

