#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//新建通讯录
//联系人管理系统
//1.管理联系人: 姓名,电话,公司,地址
//2.怎么管理.
//3.怎么增删改查(CRUD)

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

int menu( ){
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
	printf("请输入您的选择: ");
	int choice;
	scanf("%d", &choice);
	return choice;
}

void Init(addressbook* addr_book) {
	assert(addr_book != NULL);//对指针进行判空操作
	//addr_book->size = 0;
	// max_size = sizeof(addr_book->person_infos) / sizeof(addr_book->person_infos[0]);典型计算结构体长度方式
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

	personinfo* p = &addr_book -> person_infos[addr_book->size];
	
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
	printf("添加成功!\n");
}

void delpersoninfo(addressbook* addr_book){
	assert(addr_book != NULL);
	printf("删除联系人!\n");
	printf("请输入您要删除的序号 : ");
	int id = 0;
	scanf("%d", &id);
	if (id < 0||id >=addr_book ->size){
		printf("您输入的序号有误!删除失败!\n");
		return;
	}
	//删除某个数组中的元素,推荐使用指针的方式获取
	//如果直接获取结构体变量的可能会造成无谓的拷贝
	personinfo*p = &addr_book->person_infos[id];
	printf("您要删除的元素是[&d] %s,输入 Y 确认\n", id, p->name);
	char cmd[1024] = { 0 };
	scanf("%s", cmd);
	if (strcmp(cmd, "Y") != 0 ){
		printf("删除取消!\n");
		return;
	}
	//删除操作
	//把最后一个元素搬运到删除的元素位置,
	personinfo* from = &addr_book->person_infos[addr_book->size - 1];
	personinfo* to = &addr_book->person_infos[id];
	*to = *from;//搬运一个元素
	//size--
	--addr_book->size;
	printf("删除成功!");
}

void modifypersoninfo(addressbook* addr_book){
	assert(addr_book != NULL);
	printf("对联系人进行修改! ");
	printf("请输入要修改的记录序号");
	int id = 0;
	scanf("%d", &id);
	if (id < 0 || id >= addr_book->size){
		printf("您输入的序号有误! 修改失败\n");
		return;
	}
	personinfo* p = &addr_book->person_infos[id];
	printf("您修改的序号为[%d] %s,请输入 Y\n", id , p->name);
	char cmd[1024] = { 0 };
	scanf("%s", cmd);
	if (strcmp(cmd, "Y") != 0){
		printf("修改取消!\n");
		return;
	}
	char input[1024] = { 0 };

	printf("请输入修改姓名(输入空格跳过): ");
	scanf("%s", input);
	if (strcmp(input, " ") != 0){
		strcpy(p->name, input);
	}	
	printf("请输入修改地址(输入空格跳过): ");
	scanf("%s", input);
	if (strcmp(input, " ") != 0){
		strcpy(p->address, input);
	}	
	printf("请输入修改公司(输入空格跳过): ");
	scanf("%s", input);
	if (strcmp(input, " ") != 0){
		strcpy(p->company, input);
	}	
	printf("请输入修改电话(输入空格跳过): ");
	scanf("%s", input);
	if (strcmp(input, " ") != 0){
		strcpy(p->phone, input);
	}
	printf("修改成功!");
}

void findpersoninfo(addressbook* addr_book){
	assert(addr_book != NULL);
	printf("进行查找!\n");
	printf("请输入姓名:");
	char name[1024] = { 0 };
	scanf("%s", name);
	for (int  i = 0; i < addr_book->size; i++){
		personinfo* p = &addr_book->person_infos[i];
		if (strcmp(name, p->name) == 0){
			printf("[%d] %s\t%s\t%s\t%s\n", i, p->name, p->phone, p->company, p->address);

		}
	}
	printf("查找成功!\n");
}
void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}
void sortpersoninfo(addressbook* addr_book){
	assert(addr_book != NULL);






}

void printfallpersoninfo(addressbook* addr_book){
	assert(addr_book != NULL);
	personinfo* p = addr_book->person_infos;
	for (int i = 0; i < addr_book ->size; i++) {
		printf("[%d] %s\t%s\t%s\t%s\n", i ,p[i].name,p[i].phone,p[i].address,p[i].company);
	}
	printf("显示完毕!共显示 %d 条记录!\n", addr_book->size);
}

void clearpersoninfo(addressbook* addr_book){
	assert (addr_book != NULL);
	printf("清空所有元素!\n");
	printf("确认请输入: Y \n");
	char input[1024] = { 0 };
	if (strcmp ( input , "Y") != 0 ){
		printf("清空	取消Thanks♪(･ω･)ﾉ");
		return;
	}
	addr_book->size = 0;
	printf("清空成功!\n");
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
		int choice = menu();
		if (choice < 0 || choice > choice > sizeof(func_table) / sizeof (func_table[0])) {
			printf("您的输入非法! 请重新输入!\n");
			continue;
		}
		if (choice == 0){
			printf("GOODBYE!\n");
			break;
		}
		func_table[choice - 1](&g_addr_book);
	}
		system("pause");
		return 0;
}