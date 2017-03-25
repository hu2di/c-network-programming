// Hello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <conio.h>
int _tmain(int argc, _TCHAR* argv[])
{
	printf("Xin chao cac ban !\n");
	int a,b;
	printf("Hay nhap vao hai so a va b:");
	scanf("%d %d",&a,&b);
	printf("a+b=%d\n",a+b);
	printf("a-b=%d\n",a-b);
	printf("a*b=%d\n",a*b);
	printf("a/b=%d\n",a/b);
	getch();
	return 0;
}

