#include <windows.h>

#define SERVICE_CONTROL_NEWFILE 128

void MyServiceMain(DWORD argc, LPTSTR *argv);
void MyServiceHandler(DWORD opCode);

SERVICE_STATUS_HANDLE g_hSrv;
DWORD g_NowState;
BOOL g_bPause;
HANDLE g_ExitEvent;
TCHAR gbuf[65536] = "�޸� ��� ����\r\n";

int main()
{
	SERVICE_TABLE_ENTRY ste[2] = {
		{ "MemStat",(LPSERVICE_MAIN_FUNCTION)MyServiceMain },
		{ NULL,NULL }
	};

	StartServiceCtrlDispatcher(ste);

	return 0;
}

// ������ ���� ���¸� �����ϴ� �Լ�
void MySetStatus(DWORD dwState, DWORD dwAccept = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE)
{
	SERVICE_STATUS ss;
	ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState = dwState;
	ss.dwControlsAccepted = dwAccept;
	ss.dwWin32ExitCode = 0;
	ss.dwServiceSpecificExitCode = 0;
	ss.dwCheckPoint = 0;
	ss.dwWaitHint = 0;

	// ���� ���¸� ������ �д�.
	g_NowState = dwState;
	SetServiceStatus(g_hSrv, &ss);
}

void MyServiceMain(DWORD argc, LPTSTR *argv)
{
	HANDLE hFile;
	MEMORYSTATUS ms;
	DWORD dwWritten;
	TCHAR str[256];
	SYSTEMTIME st;

	// ���� �ڵ鷯�� ����Ѵ�.
	g_hSrv = RegisterServiceCtrlHandler("MemStat", (LPHANDLER_FUNCTION)MyServiceHandler);
	if (g_hSrv == 0) {
		return;
	}

	// ���񽺰� ���������� �˸���.
	MySetStatus(SERVICE_START_PENDING);

	// ���� ������ �ʱ�ȭ�Ѵ�.
	g_bPause = FALSE;

	// �̺�Ʈ�� �����Ѵ�.
	g_ExitEvent = CreateEvent(NULL, TRUE, FALSE, "MemStatExit");

	// ���ο� �α� ������ �ۼ��Ѵ�.
	hFile = CreateFile("c:\\MemStat.txt", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	CloseHandle(hFile);

	// ���񽺰� ���۵Ǿ����� �˸���.
	MySetStatus(SERVICE_RUNNING);

	// 10�ʿ� �ѹ��� �޸� ��踦 �ۼ��Ѵ�.
	for (;;) {
		if (g_bPause == FALSE) {
			// ���� �ð��� �޸� ���� �����Ͽ� ���ڿ��� �����Ѵ�.
			GetLocalTime(&st);
			GlobalMemoryStatus(&ms);
			wsprintf(str, "%d�� %d�� %02d�� %02d�� %02d�� => "
				"��밡�� ���� �޸�=%dMbytes(%d%%), ��밡�� ����޸�=%dMbytes,"
				" ��밡�� ����¡ ����=%dMbytes\r\n",
				st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
				ms.dwAvailPhys / 1048576, 100 - ms.dwMemoryLoad, ms.dwAvailVirtual / 1048576,
				ms.dwAvailPageFile / 1048576);

			// ���Ϸ� ��踦 ����Ѵ�. ���۰� ������ ��� ������ �ٽ� �����.
			if (lstrlen(gbuf) > 60000) {
				hFile = CreateFile("c:\\MemStat.txt", GENERIC_WRITE, 0, NULL,
					CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				lstrcpy(gbuf, "�޸� ��� ����\r\n");
			}
			else {
				hFile = CreateFile("c:\\MemStat.txt", GENERIC_WRITE, 0, NULL,
					OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			}
			lstrcat(gbuf, str);
			WriteFile(hFile, gbuf, lstrlen(gbuf), &dwWritten, NULL);
			CloseHandle(hFile);
		}
		if (WaitForSingleObject(g_ExitEvent, 10000) == WAIT_OBJECT_0)
			break;
	}
	MySetStatus(SERVICE_STOPPED);
}

// �ڵ鷯 �Լ�
void MyServiceHandler(DWORD fdwControl)
{
	HANDLE hFile;

	// ���� ���¿� ���� ���� �ڵ��� ���� ó���� �ʿ� ����.
	if (fdwControl == g_NowState)
		return;

	switch (fdwControl) {
	case SERVICE_CONTROL_PAUSE:
		MySetStatus(SERVICE_PAUSE_PENDING, 0);
		g_bPause = TRUE;
		MySetStatus(SERVICE_PAUSED);
		break;
	case SERVICE_CONTROL_CONTINUE:
		MySetStatus(SERVICE_CONTINUE_PENDING, 0);
		g_bPause = FALSE;
		MySetStatus(SERVICE_RUNNING);
		break;
	case SERVICE_CONTROL_STOP:
		MySetStatus(SERVICE_STOP_PENDING, 0);
		SetEvent(g_ExitEvent);
		break;
	case SERVICE_CONTROL_NEWFILE:
		hFile = CreateFile("c:\\MemStat.txt", GENERIC_WRITE, 0, NULL,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		lstrcpy(gbuf, "�޸� ��� ����\r\n");
		CloseHandle(hFile);
	case SERVICE_CONTROL_INTERROGATE:
	default:
		MySetStatus(g_NowState);
		break;
	}
}
