//#define _crt_secure_no_warnings
//#include <stdio.h>
//#include <stdlib.h>
//
//int main(){
//	int num1 = 0;
//	int num2 = 0;
//	printf("请输入两个整数：");
//	scanf("%d %d", &num1, &num2);
//	int num = num1 + num2;
//	printf("sum = %d\n", num);
//	//常量 1.字面值常量2.const 关键字修饰的常量const float pi = 3.14;
//	//3.#define(宏) 定义的常量 4.枚举常量enum
//	////enum{
//	//	male,female,unknow,
//	//}; (0.1.2)

//生命周期与作用域 局部变量在其所在大括号内；全局变量在整个工程中
//c语言中的便令有两个大类;全局变量（在所有的函数外部定义）、局部变量
//c语言定义变量
//类型名 变量名=初始值
//定义变量尽量要对变量进行初始化
//int age = 18;
//char name = 'a';
//long ccore;
//快速注释ctrl+k+c
//printf能按照一定的合适打印字符
//sizeof功能查看某个变量或者类型占用的字节（byte数）
// c语言中没有字符串类型，通过字符数组的方式来表示字符串
//printf("%d\n", sizeof(char));//1
//printf("%d\n", sizeof(short));//2
//printf("%d\n", sizeof(int));//4
//printf("%d\n", sizeof(long));//4
//printf("%d\n", sizeof(long long));//8
//printf("%d\n", sizeof(float)); //4
//printf("%d\n", sizeof(double));//8
//	system("pause");//不同的操作系统下可能会发生变化
//	return 0;
//}
//第二节
//#define _crt_secure_no_warnings
//#include <stdio.h>
//#include <string.h>
//int add(int x, int y){
//	printf("x = %d\n", x);
//	printf("y = %d\n", y);
//	return x + y;
//}
//int main(){
//	int num1 = 0;
//	int num2 = 0;
//	printf("请输入两个整数:");
//	scanf("%d %d", &num1, num2);
//	int sum = add(num1, num2);
//	printf("sum = %d\n", sum);
//
	//\t:表示制表符
	//printf("c:\code\test.c");
	//printf("%d\n", strlen("c:\test\32\test.c"));//\32为ascii值
	//int choice = 0;
	//printf("请输入你的选择: 0 会好好学习 1 我还没玩够");
	//scanf("%d", &choice);
	//if (choice == 0){
	//	printf("ok\n");
	//}else 
	//{
	//	printf("huijia!\n");
//	//}
//	system("pause");
//	return 0	;
//}
//第三节
//#include <stdio.h>
//#include <stdlib.h>
//enum Sex{
//male,
//female,
//unkonw
//     };
////宏在C语言中相当于文本替换
////#define MAX 100
////#define ADD(x,y) x + y
//struct Student{
//	char name[1024];
//	int age;
//	char id[1024];
//	enum  Sex sex;
//};
//
//int main(){
//	struct Student zhangsan = { "张三", 18, "1024", };
//	printf("%s,%s\n", zhangsan.name);
//变量的声明 extern 整个工程变量的声明(跨文件)也可作为函数的跨文件的声明
//void Test(){
//	static int num = 0;//ststic 1.修饰局部变量的时候,可以让变量变为全局周期
//	//(跟随整个程序)而不改变作用域  2.在修饰全局变量/(函数+)时则全局变量/(函数)的作用域仅限于当前.c文件
//	num += 1;
//	printf("%d\n", num);
//}
//typedef long int32_t;重定义
//
//	int main(){
//		long a = 10;
//		int32_t a = 10;
//		int count = 0;
//		while (count < 10){
//			Test();
//			count += 1;
//		}
//system("pause");
//return 0;
//}
//////////////////////////////////////

//int IsPrime(int x){
//	int num = 2;
//	while (num < x){
//		if (x % num == 0){
//			return 0;//说明不是素数
//		}
//		num = num + 1;
//	}
//	return 1;
//
//}
//
//int main(){
//	int i = 1;
	//while (i < 100)
//	{
//		if (IsPrime(i) == 1){
//			printf("%d\n", i);
//		}
//		i += 1;
//	}
//	system("pause");
//	return 0;
//}
//输入大小写字母对应输出相反的字母
#include <stdio.h>
#include <stdlib.h>
int main(){
	int ch = 0;
	while ((ch == getchar( ) != EOF){
		if (ch >= 'A' && ch <= 'Z'){
			putchar (ch + 32);
		}
		else if
	}

	system("pause");
	return  0;
}

