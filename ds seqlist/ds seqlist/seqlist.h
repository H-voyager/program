#pragma once

/*
// 静态顺序表
// 顺序表的容量，是在静态时期确定（编译期间，代码里写死）
typedef struct SeqList {
int array[100];	// 容量是 100
int size;		// 顺序表实际存储的数据个数
}	SeqList;
*/

// 动态顺序表
// 容量在动态时期确定（运行时期）
typedef struct Seqlist{
	int *array;
	int capacity; //容量
	int size;//1.有效数据的个数
	           //2.尾插时,可用位置的下标
}Seqlist;

//初始化
void SeqlistInit(Seqlist *ps, int capacity);

//销毁
void SeqlistDestory(Seqlist *ps);

//增, 删,改, 查
//尾插
void SeqlistPushback(Seqlist *ps);

//头插
void SeqlistPushFront(Seqlist *ps);

//尾删
void SeqlistPopback(Seqlist *ps);

//头删
void SeqlistPopfront(Seqlist *ps);

//根据pos下标做删除
void SeqlistErase(Seqlist *ps, int pos);

//查找
int SeqlistFind(Seqlist *ps, int v);

//更新
int SeqlistModify(Seqlist *ps, int pos, int v);

//删除遇到第一个遇到的v
void SeqlistRmove(Seqlist *ps, int v);

//删除所有遇到的v
void SeqlsitRemoveAll(Seqlist *ps, int v);