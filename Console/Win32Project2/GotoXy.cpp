#include <windows.h>

//void main()
void GotoXy()
{
	HANDLE hOut;
	TCHAR str[50];
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;
	COORD Cur;
	DWORD dw;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// 현재의 커서 위치 확인
	GetConsoleScreenBufferInfo(hOut, &BufInfo);
	wsprintf(str, "X=%d,y=%d", BufInfo.dwCursorPosition.X, BufInfo.dwCursorPosition.Y);

	// 임의의 위치 지정
	Cur.X = 50;
	Cur.Y = 10;
	SetConsoleCursorPosition(hOut, Cur);
	// 지정한 위치에 문자열 출력
	WriteFile(hOut, str, lstrlen(str), &dw, NULL);
}