#define _CRT_SECURE_NO_WARNINGS
//宏定义绝对值
#define VALUE(x) ( (x)>0?(x):-(x) ) 


//整数逆序
int reverse(int num)
{
	int a;
	int sum = 0;
	while (num)
	{
		a = num % 10;
		sum = sum * 10 + a;
		num = num / 10;
	}
	return sum;
}


//清零3-5位
void ArrayRrverse(int array[], int size)
{
	int temp; //临时变量
	int i;
	for (i = 0; i<size / 2; i++)
	{
		//第i个值和第size-i-1个值相交换
		temp = array[i];
		array[i] = array[size - i - 1];
		array[size - i - 1] = temp;
	}
}

int CreateArray(int *array, int num)
{
	int i = 0;
	while (num)
	{
		array[i] = num % 10;
		num = num / 10;
		i++;
	}
	return i;
}

void PrintArray(int array[], int size)

{
	for (int i = 0; i < size; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}

void FindZero(int array[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (i < 5 && i > 1)
		{
			array[i] = 0;
		}
	}
}

void BubberSort(char array[], int size)
{
	char tmp[20] = { 0 };
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (strcmp(array[j], array[j + 1]) > 0)
			{
				strcpy(tmp[20], array[j]);
				strcpy(array[j], array[j + 1]);
				strcpy(array[j + 1], tmp[20]);
			}
		}
	}
}

void Compare(char arr1[], char arr2[],int size)
{
	int tmp = strcmp(arr1[size], arr2[size]);
	if ( tmp== 0){
		return 0;
	}
	if (tmp > 0){
		return 1;
	}
	if (tmp < 0)
	{
		return -1;
	}
}

//第一个题
//#include <stdio.h>
//#include<stdlib.h>
//int main()
//{
//	int a, b, c;
//	printf("shu ru di yi ge zheng shu");
//	scanf("%d", &a);
//	printf("shu ru di er ge zheng shu");
//	scanf("%d", &b);
//	c = b;
//	a *= 10;
//	for (; c /= 10; a *= 10);
//	c = a + b;
//	printf("shu chu he bing de zheng shu wei%d", c);
//	system("pause");
//}
//
//
//#include<stdio.h>
//
//#include<stdlib.h>
//
//int _add(int a, int b)
//{
//	return a + b;
//}
//
//int _minus(int a, int b)
//{
//	return a - b;
//}
//
//int _muti(int a, int b)
//{
//	return a*b;
//}
//double divide(int a, int b)
//{
//	if (!b)
//	{
//		printf("Error!\n");
//		exit(1);
//	}
//	return (double)a / b;
//}
