#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
	int i = 0;
	printf("Select number : ");
	scanf_s("%d", &i);

	char char_x[10] = "1";
	char char_y[10] = "2";

	int x = 0;
	int y = 0;

	switch (i)
	{
	case 1:
		x = GetPrivateProfileInt("Position", "x", 0, "C:\\regi\\IniFile.ini");
		printf("%d\n", x);
		y = GetPrivateProfileInt("Position", "y", 0, "C:\\regi\\IniFile.ini");
		printf("%d\n", y);


		WritePrivateProfileString("Position", "x", char_x, "C:\\regi\\IniFile.ini");
		WritePrivateProfileString("Position", "y", char_y, "C:\\regi\\IniFile.ini");

		break;

	case 2:
		x = GetProfileInt("Position", "x", 1000);
		printf("%d\n", x);
		y = GetProfileInt("Position", "y", 2000);
		printf("%d\n", y);

		WriteProfileString("Position", "x", char_x);
		WriteProfileString("Position", "y", char_y);

		break;

	case 3:
		HKEY key;
		DWORD dwDisp;
		DWORD Size;

		RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Miyongsoft\\RegiTest\\Position", 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp);

		Size = sizeof(LONG);
		if (RegQueryValueEx(key, "x", 0, NULL, (LPBYTE)&x, &Size) != ERROR_SUCCESS)
			x = 100;

		Size = sizeof(LONG);
		if (RegQueryValueEx(key, "y", 0, NULL, (LPBYTE)&y, &Size) != ERROR_SUCCESS)
			y = 200;

		RegCloseKey(key);

		RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Miyongsoft\\RegiTest\\Position", 0, NULL,
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp);

		RegSetValueEx(key, "x", 0, REG_DWORD, (LPBYTE)&x, sizeof(LONG));
		RegSetValueEx(key, "y", 0, REG_DWORD, (LPBYTE)&y, sizeof(LONG));

		RegCloseKey(key);

		break;
	}
	return 0;
}

/* IniFile.ini에 정보 저장 */
/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	RECT rt;
	TCHAR buf[10];
	switch (iMessage)
	{
	case WM_CREATE:
		rt.left = GetPrivateProfileInt("Position", "Left", 0, "IniFile.ini");
		rt.top = GetPrivateProfileInt("Position", "Top", 0, "IniFile.ini");
		rt.right = GetPrivateProfileInt("Position", "Right", 100, "IniFile.ini");;
		rt.bottom = GetPrivateProfileInt("Position", "Bottom", 100, "IniFile.ini");
		MoveWindow(hWnd, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, TRUE);
		return 0;
	case WM_DESTROY:
		GetWindowRect(hWnd, &rt);
		_itoa(rt.left, buf, 10);
		WritePrivateProfileString("Position", "Left", buf, "IniFile.ini");
		_itoa(rt.top, buf, 10);
		WritePrivateProfileString("Position", "Top", buf, "IniFile.ini");
		_itoa(rt.right, buf, 10);
		WritePrivateProfileString("Position", "Right", buf, "IniFile.ini");
		_itoa(rt.bottom, buf, 10);
		WritePrivateProfileString("Position", "Bottom", buf, "IniFile.ini");
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
*/

/* Win.ini에 정보 저장 */
/*
LRESULT CALLBACK WndProc2(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	RECT rt;
	TCHAR buf[10];
	switch (iMessage)
	{
	case WM_CREATE:
		rt.left = GetProfileInt("Position", "Left", 0);
		rt.top = GetProfileInt("Position", "Top", 0);
		rt.right = GetProfileInt("Position", "Right", 100);;
		rt.bottom = GetProfileInt("Position", "Bottom", 100);
		MoveWindow(hWnd, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, TRUE);
		return 0;
	case WM_DESTROY:
		GetWindowRect(hWnd, &rt);
		_itoa(rt.left, buf, 10);
		WriteProfileString("Position", "Left", buf);
		_itoa(rt.top, buf, 10);
		WriteProfileString("Position", "Top", buf);
		_itoa(rt.right, buf, 10);
		WriteProfileString("Position", "Right", buf);
		_itoa(rt.bottom, buf, 10);
		WriteProfileString("Position", "Bottom", buf);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
*/

/* 레지스트리에 정보 저장 */
/*
LRESULT CALLBACK WndProc3(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	RECT rt;
	HKEY key;
	DWORD dwDisp;
	DWORD Size;
	switch (iMessage) {
		case WM_CREATE:
			RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Miyongsoft\\RegiTest\\Position", 0, NULL, 
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp);
			Size = sizeof(LONG);
			if (RegQueryValueEx(key, "Left", 0, NULL, (LPBYTE)&rt.left, &Size) != ERROR_SUCCESS)
				rt.left = 0;
			Size = sizeof(LONG);
			if (RegQueryValueEx(key, "Top", 0, NULL, (LPBYTE)&rt.top, &Size) != ERROR_SUCCESS)
				rt.top = 0;
			Size = sizeof(LONG);
			if (RegQueryValueEx(key, "Right", 0, NULL, (LPBYTE)&rt.right, &Size) != ERROR_SUCCESS)
				rt.right = 100;
			Size = sizeof(LONG);
			if (RegQueryValueEx(key, "Bottom", 0, NULL, (LPBYTE)&rt.bottom, &Size) != ERROR_SUCCESS)
				rt.bottom = 100;
			RegCloseKey(key);
			MoveWindow(hWnd, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, TRUE);
			return 0;
		case WM_DESTROY:
			RegCreateKeyEx(HKEY_CURRENT_USER, "Software\\Miyongsoft\\RegiTest\\Position", 0, NULL,
				REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &key, &dwDisp);
			GetWindowRect(hWnd, &rt);
			RegSetValueEx(key, "Left", 0, REG_DWORD, (LPBYTE)&rt.left, sizeof(LONG));
			RegSetValueEx(key, "Top", 0, REG_DWORD, (LPBYTE)&rt.top, sizeof(LONG));
			RegSetValueEx(key, "Right", 0, REG_DWORD, (LPBYTE)&rt.right, sizeof(LONG));
			RegSetValueEx(key, "Bottom", 0, REG_DWORD, (LPBYTE)&rt.bottom, sizeof(LONG));
			RegCloseKey(key);
			PostQuitMessage(0);
			return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
*/