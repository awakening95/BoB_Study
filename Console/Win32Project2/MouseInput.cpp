#include <windows.h>
#include <stdio.h>

/* 콘솔창 우클릭 - 속성(P) - 빠른 편집 모드(Q) 체크 해제 필수 */

//void main()
void MouseInput()
{
	HANDLE hIn, hOut;
	DWORD dw;
	INPUT_RECORD rec;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	while(TRUE) {
		ReadConsoleInput(hIn, &rec, 1, &dw);
		// 키보드 입력 시 그 문자 출력
		if(rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown == TRUE) {
			printf("%c", rec.Event.KeyEvent.uChar.AsciiChar);
		}
		// 드레그 시 그 위치에 "." 찍기
		if(rec.EventType == MOUSE_EVENT) {
			if((rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
				&& (rec.Event.MouseEvent.dwEventFlags & MOUSE_MOVED)) {
				SetConsoleCursorPosition(hOut, rec.Event.MouseEvent.dwMousePosition);
				printf(".");
			}
		}
		// 더블 클릭시 종료
		if (rec.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK) {
			break;
		}
	}
}