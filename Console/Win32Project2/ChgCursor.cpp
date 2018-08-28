#include <windows.h>
#include <stdio.h>

//void main(int argc, char* argv[])
void ChgCursor(int argc, char* argv)
{
	HANDLE hOut;
	int Size;
	CONSOLE_CURSOR_INFO CurInfo;

	for(Size = 1; Size<10; Size++)
	{
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		// 커서 모양 변경
		if(argv[0] == '-') {
			CurInfo.dwSize = 1;
			CurInfo.bVisible = FALSE;
		}
		else {
			CurInfo.dwSize = Size * 10;
			CurInfo.bVisible = TRUE;
		}
		SetConsoleCursorInfo(hOut, &CurInfo);
		Sleep(1000);
	}
}