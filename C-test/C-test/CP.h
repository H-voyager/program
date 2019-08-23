#include<stdio.h>
#include <time.h>
void dgCal(int a[], int b, int i)
{ 
	if (i>a[0])      
	{ 
		a[0]++; 
	}
	int temp = a[i] + b;
	if (temp >= 10)
	{ 
		a[i] = temp % 10;
		dgCal(a, temp / 10, i + 1);
	} 
	else
	{ a[i] = temp;
	}
}
void calculator(int a[], int b[])
{
	int temp = 0;
	for (int i = 1; i <= b[0]; i++)
	{
		temp = a[i] + b[i];
		if (temp >= 10)
		{
			a[i] = temp % 10;
			dgCal(a, temp / 10, i + 1);
		}
		else
		{
			a[i]=temp;
		}
	}
}    
void copyArray(int a[],int b[])
{      
	for(int i=0;i<=a[0];i++)
	{
			b[i]=a[i];
	}  
}
void printa(int a[])
{
	printf("位数：%d\n",a[0]);
	for(int i=a[0];i>=1;i--)
	{
		printf("%d",a[i]);
	}
	printf("\n");
}
void printb(int b[])
{ 
	printf("位数：%d\n",b[0]);
	for(int i=b[0];i>=1;i--)
	{
		printf("%d",b[i]);
	}
	printf("\n");
}

