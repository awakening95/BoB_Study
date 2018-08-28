#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <iostream>
#include <stdio.h>



//void main()
void ConIn()
{
	HANDLE hIn, hOut;
	TCHAR buf[20], str[50];
	DWORD dw;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	printf("input your name : ");
	scanf("%s20s", buf);
	printf("your name is %s\n", buf);

	std::cout << "input your name : ";
	std::cin >> buf;
	std::cout << "your name is " << buf << std::endl;

	WriteFile(hOut, "input your name : ", 19, &dw, NULL);
	memset(buf, 0, sizeof(buf));
//	ReadFile(hIn, buf, 20, &dw, NULL);
	ReadConsole(hIn, buf, 20, &dw, NULL);
	wsprintf(str, "your name is %s", buf);
	WriteFile(hOut, str, lstrlen(str), &dw, NULL);
}