#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	DWORD dw;
	TCHAR *str = "New Console is created";
	TCHAR *Mes = TEXT("마우스 왼쪽 버튼을 누르면 새로운 콘솔 윈도우를 만듭니다");

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		if (AllocConsole() == FALSE) {
			//콘솔 생성 실패
			puts("");
		}
		// 출력하는 함수 //
		/* 핸들값, 문자열 담은 변수, 문자열의 길이, 함수 호출 후 전송한 실제 길이, NULL */
		WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), str, lstrlen(str), &dw, NULL);
		Sleep(3000);
		FreeConsole();
		break;
	case WM_PAINT:
		// GUI 창 띄우기
		hdc = BeginPaint(hWnd, &ps);
		// GUI 내에 50, 50 위치에 메세지 출력
		TextOut(hdc, 50, 50, Mes, lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}