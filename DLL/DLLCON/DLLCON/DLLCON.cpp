// DLLCON.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#pragma comment(lib, "EXDLL.lib")

extern "C" __declspec(dllimport) int add(int a, int b);

int main(int argc, char* argv[])
{
	int a = 10;
	int b = 20;

	printf("%d", add(a, b));
	return 0;
}