#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//新建通讯录
//联系人管理系统
//1.管理联系人: 姓名,电话,公司,地址
//2.怎么管理.
//3.怎么增加删改()

typedef struct personinfo {
	char name[1024];
	char phone[1024];
	char company[1024];
	char address[1024];
} personinfo;

#define PERSON_INFOS_MAX_SIZE 200

typedef struct addressbook{
	//[0.size) 表示有效的联系人信息
	personinfo person_infos[PERSON_INFOS_MAX_SIZE];
	int size;
} addressbook;

addressbook g_addr_book;

int menu(){
	printf("========================\n");
	printf("1 . 新建联系人\n");
	printf("2 . 删除联系人\n");
	printf("3 . 修改联系人\n");
	printf("4 . 查找联系人\n");
	printf("5 . 排序\n");
	printf("6 . 打印全部联系人\n");  
	printf("7 . 清除全部联系人\n");
	printf("0 . 退出\n");
	printf("========================\n");
	int choice;
	scanf("%d", &choice);
	return choice;
}

void Init(addressbook* addr_book) {
	assert(addr_book != NULL);//对指针进行判空操作
	//addr_book->size = 0;
	//int max_size = sizeof(addr_book->person_infos) / sizeof(addr_book->person_infos[0]);典型计算结构体长度方式
	//for (int i = 0; i < max_size; i++){
	//	memset(addr_book->person_infos[i].name, 0, 1024);
	//	memset(addr_book->person_infos[i].phone, 0, 1024);
	//	memset(addr_book->person_infos[i].company, 0, 1024);
	//	memset(addr_book->person_infos[i].address, 0, 1024);
	//}
	memset(addr_book, 0, sizeof(addressbook));
	//结构体初始化
}

void addpersoninfo(addressbook* addr_book){
	printf("新增联系人\n");
	if (addr_book-> size >= PERSON_INFOS_MAX_SIZE){
		printf("添加失败!存储已满!");
	}

	personinfo* p = &addr_book->person_infos[addr_book->size];
	
	printf("请输入用户名: ");
	scanf("%s",p -> name);
    //此时输入的内容像下标为size的元素上放置
	//scanf("%s", addr_book->person_infos[addr_book->size].name);
	printf("请输入联系人电话: ");
	scanf("%s", p->phone);

	printf("请输入联系人公司: ");
	scanf("%s", p->company);
	
	printf("请输入联系人地址");
	scanf("%s", p->address);

	++addr_book->size;
	printf("添加成功\n");
}

void delpersoninfo(addressbook* addr_book){

}

void modifypersoninfo(addressbook* addr_book){

}

void findpersoninfo(addressbook* addr_book){

}

void sortpersoninfo(addressbook* addr_book){

}

void printfallpersoninfo(addressbook* addr_book){

}

void clearpersoninfo(addressbook* addr_book){

}
int main(){
	//表驱动    函数指针数组
	typedef void(*pfunc_t)(addressbook*);
	pfunc_t func_table[ ] = {
		addpersoninfo,
		delpersoninfo,
		modifypersoninfo,
		findpersoninfo,
		sortpersoninfo,
		printfallpersoninfo,
		clearpersoninfo,
	};
 
	//对数组的元素进行初始化
	Init (&g_addr_book);
	while (1){
		int choice = menu( );
		if (choice < 0 || choice > sizeof(func_table) / sizeof (func_table[0])); {
			printf("您的输入非法! 请重新输入!\n");
			continue;
		}
		if (choice == 7){
			break;
		}
		func_table[choice - 1](&g_addr_book);
	}


	system("pause");
	return 0;
}