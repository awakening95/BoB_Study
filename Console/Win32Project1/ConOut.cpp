#include <windows.h>
#include <iostream>
#include <stdio.h>

//void main() {
void ConOut() {
	HANDLE hOut;
	TCHAR *str = "Console Test\n";
	DWORD dwWritten;

	printf("%s", str);

	std::cout << str;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	/* dwWritten = 함수 호출 완료 후 전송된 실제 데이터 크기가 담기는 변수 */
	WriteFile(hOut, str, lstrlen(str), &dwWritten, NULL);

	WriteConsole(hOut, str, lstrlen(str), &dwWritten, NULL);
}