//#include <stdio.h>

//int main() {
//	int n = 0x11223344;
//	char *pc = (char *)&n;
//	char *pi = &n;    *pc = 0x55;//重点在调试的过程中观察内存的变化。
//	*pi = 0;   
//	return 0; 
//}
//////////////////////////////////////////////////////
//指针和数组
//#include <stdio.h>
//
//int main() {
//	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
//	int *p = arr; //指针存放数组首元素的地址
//	int sz = sizeof(arr)/sizeof(arr[0]);
//	for (int i = 0; i < sz; i++) {
//		printf("&arr[%d] = %p   <====> p+%d = %p\n", i, &arr[i], i, p + i);
//	}
//
//	system("pause");
//	return 0;
//}
//////////////////////////////////////////////////////////
//#include <stdio.h>
//int main()
//{
	//  int i = 0;
	//   int k = 0;
	//int num = 0;
	//  for (i = 0, k = 0; k = 0; i++, k++){
	//	  k++;
	//	  num++;
	//  }
	//  printf("%d", num);
	//int a = 10;
	//int* p = a;!
	//printf("%x\n", &p);
	//system("pause");
	//return 0;
	//int i = 0, a = 0, b = 2, c = 3, d = 4;
	//i = a++ && ++b && d++; 
	//printf("a = %d\n b = %d\n c = %d\nd = %d\n", a, b, c, d); 
	//////////////////////////////////////////////////////////
	//数组创建[]内必须是一个常量
	//int count = 10;
	//int arr[count];
	////////////////////////////////////////////////////
	//char arr1[] = "abc";//char[4]
	//char arr2[3] = { 'a', 'b', 'c' };//char [3]
	//////////////////////////////////////////////////////
	//int arr[10] = { 1 };//未完全初始化
	//int i = 0;
	//for (i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	//{
	//	int *p = &arr[i];
	//	printf("&arr[%d] = %p\n", i,*p);

	//}
	//////////////////////////////////////////////////////
	//二维数组
	//int arr[3][4] = { 0 };
	//int i = 0;
	//for (i = 0; i<3; i++){
	//	int j = 0;
	//	for (j = 0; j<4; j++)
	//	{
	//		arr[i][j] = i * 4 + j;
	//	}
	//}
	//for (i = 0; i<3; i++){
	//	int j = 0;
	//	{ 
	//		printf("%d ", arr[i][j]); 
	//	} 
	//}
	//////////////////////////////////////////////////////////
	//int arr[3][4];
	//int i = 0;
	//for (i = 0; i < 3; i++)
	//{
	//	int j = 0;
	//	for (j = 0; j < 4; j++)
	//	{
	//		printf("&arr[%d][%d] = %p\n", i, j, &arr[i][j]);
	//	}
	//}
	/////////////////////////////////////////////////////////////
//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include "CP.h"
//int Product(int multiplier)
//{
//	int product = multiplier;
//	while (multiplier > 1)
//	{
//		product = product * (multiplier - 1);
//		multiplier--;
//	}
//	return product;
//}
//int RecursionProduct(int m)
//{
//	if (m !=1 )
//	{
//		return m * RecursionProduct(m - 1);
//	}
//	return 1;
//}

//int CreateArray(int* array,int num)
//{
//	int i = 0;
//	while (num)
//	{
//		array[i]= num & 10;
//		num = num / 10;
//		i++;
//	}
//	return i;
//}
//
//void PrintfArray(int *array[], int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		printf("%d", array[i]);
//	}
//}
//int main()
//{
	//int input ;
	//scanf("%d", &input);	
	//int array[] = { 0 };
	//int tmp;
	//int result = Product(input);
	//tmp = CreateArray(array, result);
	//PrintfArray(array, tmp);
	//printf("Product: %d\n", Product(input));
	//printf("RecursionProduct: %d", RecursionProduct(input));
//	int i, j;
//	clock_t start, finish;
//	double  duration;
//	int a[200];
//	int b[200];//辅助数组
//	for (i = 0; i<200; i++)
//	{
//		a[i] = 0;
//	}
//	a[0] = 1;
//	a[1] = 2;
//	//printa(a);
//	copyArray(a, b);
//	//printb(b);
//	start = clock();
//	for (i = 3; i <= 100; i++)//从3开始
//	{
//		copyArray(a, b);
//		for (j = 0; j<i - 1; j++)//相加i-1次
//		{
//			calculator(a, b);
//		}
//	}
//	printf("100的阶乘：\n");
//	printa(a);
//	printf("99的阶乘：\n");
//	printb(b);
//	finish = clock();
//	duration = (double)(finish - start) / CLOCKS_PER_SEC;
//	printf("\n Use Time: %f seconds\n", duration);
//	system("pause");
//	return 0;
//}

#include<stdio.h>

void MySwap(int *x, int *y);

void MySwap(int *x, int *y){
	int temp = *x;//如果写成int *p=x;x=y;y=p;则还是无法改变实参的值
	*x = *y;
	*y = temp;
}

int main(){
	int a = 5, b = 9;
	int *p1 = a;
	int *p2 = &a;
	int **p3 = &p2;

	printf("%p\n %p\n %p\n %p\n", p1, p2, p3,*p3);
	printf("交换前:a=%d,b=%d \n", a, b);

	MySwap(&a, &b);
	printf("交换后:a=%d,b=%d \n", a, b);
	system("pause");
	return 0;
}

