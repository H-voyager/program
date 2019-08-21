#include "seqlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// 确保容量够用，不需要扩容，什么都不做
// 需要扩容就扩容
// 影响函数的链接属性，从外部链接属性 -> 内部链接属性
// O(n)

static void CheckCapacity(Seqlist *ps)
{
	if (ps->size <ps->capacity)
	{
		return;
	}
	int NewCapacity = ps->capacity * 2;
	int *NewArray = (int *)malloc(sizeof(int)* NewCapacity);
	assert(NewArray != NULL);

	for (int i = 0; i <ps->size; i++)
	{
		NewArray[i]= ps->array[i];
	}

	//释放capacity ,绑定newcapacity
	free(ps->array);
	ps->array=NewArray;
	ps->capacity = NewCapacity;
}
void SeqlistInit(Seqlist *ps, int capacity)
{
	//ps: 期望是变量的地址
	assert(ps != NULL);
	if (ps !=NULL)
	{
		ps->array = malloc(sizeof (int)* capacity);
		assert(ps->array != NULL);
			ps->size = 0;
			ps->capacity = capacity;
	}
}

void SeqlistDestory(Seqlist *ps)
{
	assert(ps != NULL);
	assert(ps->array != NULL);
	free(ps->array);

	//可有可不有
	ps->capacity = 0;
	ps->size = 0;
	ps->array = NULL;
}

//增, 删,改, 查
//尾插
void SeqlistPushback(Seqlist *ps,int v)
{
	CheckCapacity(ps);
	ps->array[ps->size] = v;
	ps->size++;
}

//头插
void SeqlistPushFront(Seqlist *ps,int v,int pos)
{
	CheckCapacity(ps);
	assert(pos >= 0 && pos <= ps->size);
	// pos = 0 就是头插，pos = size 就是尾插

	for (int i = ps->size; i >0 ; i--)
	{
		ps->array[i] = ps->array[i + 1];
	}
	ps->array[0] = v;
	ps->size++;
}

//尾删
void SeqlistPopback(Seqlist *ps)
{
	assert(ps->size > 0);
	ps->size--;
}

//头删
void SeqlistPopfront(Seqlist *ps)
{
	assert(ps->size > 0);

	for ( int i=0; i < ps->size - 2;  i++)
	{
		ps->array[i] = ps->array[i + 1];
	}

	ps->size--;
}

//根据pos下标做删除
void SeqlistErase(Seqlist *ps, int pos)
{
	//assert(ps->size > pos);
	//if (pos < ps->size)
	//{
	//	for (int i = pos; i < ps->size; i++)
	//	{
	//		ps->array[pos] = ps->array[pos = 1];
	//	}
	//	ps->size--;
	//}
	// [0, size - 1]
	assert(pos >= 0 && pos < ps->size);
	for (int i = pos + 1; i < ps->size; i++) {
		ps->array[i - 1] = ps->array[i];
	}

	ps->size--;

}

//查找
int SeqlistFind(Seqlist *ps, int v)
{
	assert(ps->size > 0);
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->array[i] = v)
		{
			return i;
		}
	}
}

//更新
int SeqlistModify(Seqlist *ps, int pos, int v)
{
	//下标size-1
	assert(pos >= 0 && pos < ps->size);
	ps->array[pos] = v;

}

//删除遇到第一个遇到的v
void SeqlistRmove(Seqlist *ps, int v)
{
	assert(ps->size > 0);
	for (int i = 0; i < ps->size; i++)
	{
		if (ps->array[i] = v)
		{
			for (int pos = i; pos < ps->size; pos++)
			{
				ps->array[pos] = ps->array[pos + 1];
			}
		}
	}
	//int pos = SeqListFind(ps, v);
	//if (pos == -1) {
	//	return;
	//}

	//SeqListErase(ps, pos);
}

//删除所有遇到的v
void SeqlsitRemoveAll(Seqlist *ps, int v)
{
	int i, j;
	for (i = 0, j = 0; i < ps->size; i++)
	{
		if (ps->array[i] != v) 
		{
			ps->array[j] = ps->array[i];
			j++;
		}
	}

	ps->size = j;
}