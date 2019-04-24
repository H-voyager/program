#pragma once

#include <stdio.h>
#include <stdlib.h>

//for (int  i = 1; i < size; i = i *2) 循环log(n)层,二叉树的深度

void PrintArray(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}

void Swap(int array[], int i, int j)
{
	int t = array[i];
	array[i] = array[j];
	array[j] = t;
}

/*
时间复杂度:
	最好	O(n)	    有序
	平均	O(n^2)
	最坏	O(n^2)  逆序
空间复杂度:
	O(1)
稳定性: 稳定
*/

//插入排序
void InsertSort(int array[], int size)
//一次处理一个数,所以需要循环size次
//严格意义上, size - 1次就够了
//有序[0.i - 1]
//要处理[i]
//无序[i + 1,size - 1]
{
	for (int i = 0; i < size; i++)				
	{
		int j;
		for ( j = i - 1; j >= 0 && array[j] > array[i]; j--){}

		//把 array[i] 插进去
		if (j + 1 != i)
		{//看作把array[i]插入到[0,i - 1]的顺序表里
		//插入的下标是j
			int key = array[i];
			for (int k = i; k > j +1; k--)
			{
				array[k] = array[k - 1];
			}
			 
			array[j + 1] = key;
		}
	}
}

void InterSortWithGap(int array[], int size,int gap)
{
	//ShellSort中定义gap
	for (int i = 0; i < size; i++)
	{
		int key = array[i];
		int j;
		for (j = i - gap; j >= 0 && array[j] > key; j -=gap)
		{
			array[j + gap] = array[j];
		}
		array[j + gap] = key;
	}
}

void InsertSort2(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int key = array[i];
		int j;
		for (j = i - 1; j >= 0 && array[j] > key; j--)
		{
			array[j + 1] = array[j];
		}

		array[j + 1] = key;
	}
}


void BubberSort(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		//int isSorted = 1;
		for (int  j = 0; j < size - 1 -i; j++)
		{
			if (array[j] >array[j + 1])
			{
				Swap( array,j, j + 1);
				//isSorted = 0;
			}
		}

		//if (isSorted == 1)
		//{
		//	break;
		//}
	}
}

void ShellSort(int array[], int size)
{
	int gap = size;
	while (1)
	{
		gap = gap / 3 + 1;

		InterSortWithGap(array, size, gap);
		if (gap == 1)
		{
			break;
		}
	}
}
//void sum()
//{
//	int sum = 0;
//	int i = 0;
//	scanf_s("%d", &i);
//	for (int j = 0; j <=i; j++)
//	{
//		sum = sum + j;
//	}
//	printf_s("%d", sum);
//}


/*选择排序
1.直接排序
时间复杂度: 数据不敏感 O(n^2)
空间复杂度 : O(1)
稳定性: 不稳定
*/


void SelectSort(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		//有序区域: [size - i,size - 1]
		//无序空间: [0,size - 1 - i]
		int maxIndex = 0;
		//记录数组最大下标
		for (int j = 0; j < size -1 - i; j++)
		{
			//找到整个无序区间的最大值得下标
			if (array[j] >array[maxIndex])
			{
				maxIndex = j;
			}
			//maxIndex与无序区间的而最后一个位置进行交换
			Swap(array, maxIndex, size - 1 - i);
		}
	}
}

//2.堆排序
//时间复杂度 O(n * log(n))
//空间复杂度O(1)
//稳定性: 不稳定
void Heapify(int array[], int size, int index)
{
	/*
	1.判断是不是叶子
	2.找到最大的孩子
		1)没有右孩子
		2)右孩子
			1)左孩子大
			2)右孩子大
	3.最大的孩子和根比较,如果跟比较大,退出
	4.交换并且继续调整
	*/
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if (left >= size)
	{
		return;
	}
	int max = left;
	if (right < size && array[right] > array[left])
	{
		max = right;
	}
	if (array[max] <= array[index])
	{
		return;
	}
	Swap(array, max, index);

	Heapify(array, size, max);
}

void CreateHeap(int array[], int size)
{
	for (int i = (size - 2) / 2; i >=0 ; i--)
	{
		Heapify(array, size, i);
	}
}

void HeapSort(int array[], int size)
{
	CreateHeap(array, size);

	for (int i = 0; i < size; i++)
	{
		Swap(array, 0, size - 1 - i);
		Heapify(array, size - 1 - i, 0);
	}
}



void Test()
{
	int array[] = {9,8,7,6,5,4,3,3,1};
	int  size = sizeof(array) / sizeof(int);

	PrintArray(array, size);
	//sertSort(array, size);
	//BubberSort(array, size);
	//InterSortWithGap(array, size, 8);
	//InsertSort2(array, size);
	//ShellSort(array, size);
	//SelectSort(array, size);
	HeapSort(array, size);
	PrintArray(array, size);
	system("pause");
}