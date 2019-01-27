
#include <stdio.h>
#include <stdlib.h>
//计算阶乘
int Factor(int n)
{
	if ( n ==1)
	{
		return 1;
	}
	return  n * Factor(n - 1);
}


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
		system("pause");
		return 0;
	}
