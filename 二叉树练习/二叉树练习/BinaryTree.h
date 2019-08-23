#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int value;
	struct Node* Left;
	struct Node* Right;
}Node;

// 空树		Node *root = NULL;
// 只有一个结点		Node *root;		root != NULL && root->left == NULL && root->right == NULL

// Node *node;		本身只是树的一个结点，但有时代表是以 node 为根的整棵树

// 递归
// 1. 递推公式
// 2. 终止条件
//前序遍历
void PreorderTraversal(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	//根
	printf("%d", root->value);
	//左子树
	PreorderTraversal(root->Left);
	//右子树
	PreorderTraversal(root->Right);
	//中序 , 后续只需改变先后顺序
}

void InorderTraversal(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	//左子树
	InorderTraversal(root->Left);
	//根
	printf("%d", root->value);
	//右子树
	InorderTraversal(root->Right);
	//中序 , 后续只需改变先后顺序
}


void PostorderTraversal(Node *root)
{
	if (root == NULL)
	{
		return;
	}
	//左子树
	PostorderTraversal(root->Left);
	//右子树
	PostorderTraversal(root->Right);
	//中序 , 后续只需改变先后顺序
	//根
	printf("%d", root->value);
}


//插入节点
Node* CreateNode(int value)
{
	Node* node = (Node*)malloc(sizeof (Node));
	node->value = value;
	node->Left = node->Right = NULL;
	return node;
}

int count = 0;
void Getsize(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	count++;//根
	Getsize(root->Left);//左子树
	Getsize(root->Right);
} 

//求二叉树的节点数
int GetSize(Node* root)
{
	if (root == NULL)
	{
		return 0;
	}
	return GetSize(root->Left) + GetSize(root->Right) + 1;
}

//定义一个数
void Test()
{
	Node*a = CreateNode(1);
	Node*b = CreateNode(2);
	Node*c = CreateNode(3);
	Node*d = CreateNode(4);
	Node*e = CreateNode(5);
	Node*f = CreateNode(6);
	Node*g = CreateNode(7);
	Node*h = CreateNode(8);

	a->Left = b; a->Right = c;
	b->Left = d; b->Right = e;
	c->Left = f; c->Right = g;
	d->Left = NULL; d->Right = NULL;
	e->Left = NULL; e->Right = h;
	f->Left = NULL; f->Right = NULL;
	g->Left = NULL; g->Right = NULL;
	h->Left = NULL; h->Right = NULL;

	for (int i = 0; i < 8; i++)
	{
		printf("%d: %c\n", i + 1, 'A' + i);
	}

	printf("前序遍历:\n");
	PreorderTraversal(a);
	printf("中序遍历:\n");
	printf("后序遍历:\n");
    PostorderTraversal(a);
}