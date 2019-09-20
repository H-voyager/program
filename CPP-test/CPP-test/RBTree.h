#pragma once
#include <iostream>

using std::cout;
using std::endl;

enum Colour
{
	BLACK,
	RED,
};

template <class T>
struct BRTreeNode
{
	BRTreeNode<T> *_left;
	BRTreeNode<T> *_right;
	BRTreeNode<T> *_parent;

	T _val;
	Colour _col;

	BRTreeNode(const T& val)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _val<val>
		, _col(RED)
	{}
};

template <class K, class T, class KeyOfValue>
class RBTree
{
	typedef BRTreeNode<T> Node;
public:
	bool Insert(const T& val)
	{
		//先按平衡二叉树插入新节点
		if (_root == nullptr)
		{
			_root = new Node(val);
		}
		
		KeyOfValue kov;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kov(cur->_val) < kov(val) )
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kov(cur->_val) > kov(val))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node*(val);
		cur->_col = RED; 
		if (kov(cur->_val) < kov(val))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else if (kov(cur->_val) > kov(val))
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		while (parent && parent->_val == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;

				if (unlce && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}

					RotateR(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;

					break;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(cur, parent);
					}
					RotateL(grandfather);
					parent->_col = BLACK;
					grandfather->_col = RED;
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL; 
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		Node* pNode = parent->_parent;
		parent->_parent = subR;
		if (parent == _root)
		{
			_root = subR;
			_root = nullptr;
		}
		else
		{
			if (parent == pNode->_left)
			{
				pNode->_left = subR;
			}
			else
			{
				pNode->_right = subR;
			}
			subR->_parent = pNode;
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;
		Node* pNode = parent->_parent;
		parent->_parent = subL;
		if (pNode == nullptr)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (pNode->_left == parent)
			{
				pNode->_left = subL;
			}
			else
			{
				pNode->_right = subL;
			}
			subL->_parent = pNode;
		}
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_val<< " ";
		_InOrder(root->_right);
	}
private:
	Node* _root;
};

void TestRBtree()
{
	RBTree<int,int,int> t;
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14, };
	for (auto e : a)
	{
		//t.Insert(make_pair(e,e));
	}

	t.InOrder();
}

