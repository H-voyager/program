#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
//计算阶乘
//int Factor(int n)
//{
//	if ( n ==1)
//	{
//		return 1;
//	}
//	return  n * Factor(n - 1);
//}


int main(){
//计算字符串长度
//int Strlen(char str [ ])
//{
//	if (*str == '\0')
//	{
//		return 0;
//	}
//	return 1 + Strlen(str + 1);
//}
//	char str[ ] = "hehe";
//	int len = Strlen(str);
//	printf("%d", len);



//调用函数num自增1
//int addone(int* num){
//	*num = *num + 1;
//}
//int main( ){
//	int num = 0;
//	addone(&num);
//		printf("%d", num);
//	int num = 0;
	//int i = 0;
	//int k = 0;
	//for ( i = 0 , k = 0; k  == 0; i++,k++)
	//{
	//	k++;
	//	++num;
	//
	//}
	//printf("%d", num);
	//do
	//{
	//	printf("%d ", num);
	//	++num;
	//} while (num < 10);
	int n = 0;
	scanf("%d", &n);
	int ret = 1;
	for ( int i = 1; i <= n; i++)
	{
		ret = ret * i;
	}
	printf("%d", ret);
	system("pause");
	return 0;
}
