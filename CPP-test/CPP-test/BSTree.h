#pragma once
#include <iostream>

template<class T>
struct BSTNode
{
	BSTNode(const T& data = T())
		: _pleft(nullptr)
		, _pright(nullptr)
		, _data(data)
	{}
	BSTNode<T> *_pleft;
	BSTNode<T> *_pright;
	T _data;
};

template<class T>
class BSTree
{
	typedef BSTNode<T> Node;
	typedef Node* PNode;
public:
	BSTree()
		:_proot(nullptr)
	{}

	//根据二叉树的查找性质: 找到值为data的节点在二叉树中的位置
	PNode Find(const T& data);
	bool Insert(const T& data)
	{
		if (_proot == nullptr)
		{
			_proot = new Node(data);
			return true;
		}

		PNode pParent = nullptr;
		PNode pcur = _proot;

		while (pcur)
		{
			pParent = pcur;
			if (data > pcur->_data)
			{
				pcur = pcur->_pleft;
			}
			else if (data < pcur->_data)
			{
				pcur = pcur->_pright;
			}
			else
			{
				return false;
			}
		}

		pcur = new Node(data);
		if (data < pParent->_data)
		{
			pParent->_pleft = pcur;
		}
		else
		{
			pParent->_pright = pcur;
		}
		return true;

	}
	bool Erase(const T& data)
	{
		//如果树为空删除失败
		if (_proot == nullptr)
		{
			return false;
		}
		 
		//查找data在树中所在位置
		PNode pcur = _proot;
		PNode pParent = nullptr;
		while (pcur)
		{
			if (data == pcur->_data);
			{
				break;
			}
			else if (data > pcur->_data)
			{
				pParent = pcur;
				pcur = pcur->_pright;
			}
			else
			{
				pParent = pcur;
				pcur = pcur->_pleft;
			}

			//data不在树中,删除失败
			if (pcur == nullptr)
			{
				return false;
			}

			//只有左孩子
			if (nullptr == pcur->_pright)
			{
				if (pParent->_pleft == pcur)
				{
					pParent->_pleft == pcur->pleft;
				}
				else
				{
					pParent->_pright == pcur->pleft;
				}
			}
			//只有右孩子
			if (nullptr == pcur->_pleft)
			{
				if (pParent->_pleft == pcur)
				{
					pParent->_pleft == pcur->pright;
				}
				else
				{
					pParent->_pright == pcur->pright;
				}
			}
			else
			{
				Node* rpParent = pcur;
				Node* replace = pcur->_pright;
				while (replace->_pleft)
				{
					rpParent = replace;
					replace = replace->_pleft;
				}
				pcur->_data = replace->_data;
				pcur = replace;
				if (rpParent->_pleft == replace)
				{
					rpParent->_pleft = replace->_pright;
				}
			}
			delete pcur;
			return true;
		}
		return false;
	}

	void InOrder()
	{
		_InOrder(_proot);
		cout << endl;
	}

	void _InOrder(Node* _proot)
	{
		if (_proot == nullptr)
			return;

		_InOrder(_proot->_pleft);
		cout << _proot->_data << " ";
		_InOrder(_proot->_pright);

	}

private:
	PNode _proot;
};


void TestBSTree()
{
	BSTree<int> tree;
	tree.Insert(1);
	tree.Insert(3); 
	tree.Insert(2);
	tree.Insert(6);
	tree.InOrder();
}