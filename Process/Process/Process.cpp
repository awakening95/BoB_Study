#include <stdio.h>
#include <windows.h> // OpenProcess(), ExitProcess(), CreateProcess()
#include <TlHelp32.h> // CreateToolhelp32Snapshot(), Process32First(), Process32Next()

int main()
{
	int i;
	printf("Select number : ");
	scanf_s("%d", &i);

	switch (i)
	{	
		/*HANDLE OpenProcess(
		DWORD dwDesiredAccess, // ���� ����, ���� ����, PROCESS_ALL_ACCESS�� ��� ����
		BOOL  bInheritHandle, // ��ӿ���	
		DWORD dwProcessId // ���μ��� ID(PID)
		);
		���μ����� handle�� ��ȯ*/
		case 1:
		{
			HANDLE hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 11328);
			printf("%d", hProcessHandle);
		}

		/*DECLSPEC_NORETURN VOID ExitProcess(
		UINT uExitCode // ���μ��� ���� �ڵ带 ����, ���� ���� �ΰ�� 0�� �� ���� ������ ��� -1�� �Է�
		);
		��ȯ �� ����
		�Լ��� ȣ���� ���μ���(���μ��� �� ��� ������ ����)�� ����*/
		case 2:
		{
			ExitProcess(0);
		}

		/*BOOL CreateProcess(
		LPCTSTR lpApplicationName, // ������ ���μ����� �������� �̸��� �����θ� ������ ���ڷ� ����
		LPTSTR lpCommandLine, // ���μ����� ���ڸ� ������ �� �̿��ϰų� ù ��° ���ڿ� NULL�� 
                                 �� ��� ǥ�� �˻� ����� ���������� �̸��� ����
		LPSECURITY_ATTRIBUTES lpProcessAttributes, // ���μ����� ���� �Ӽ��� ����, NULL�� ������ ��� ����Ʈ ���� �Ӽ� ����
		LPSECURITY_ATTRIBUTES lpThreadAttributes, // �������� ���� �Ӽ��� ����, NULL�� ������ ��� ����Ʈ ���� �Ӽ� ����
		BOOL bInheritHandles, // �������ڰ� TRUE�� ���, �����Ǵ� �ڽ� ���μ����� �θ� ���μ����� �����ϴ� handle�� �Ϻθ� ���
		DWORD dwCreationFlags, // �����ϴ� ���μ����� Ư��(�켱���� ��)�� �������� �� ���, �������� ���� ���� 0�� ����
		LPVOID lpEnvironment, // ������ ���μ����� ����� ȯ�溯���� ������ ����, NULL�� �����ϸ� �θ� ���μ����� ȯ������ ���
		LPCTSTR lpCurrentDirectory, // ���� ���丮�� �����ϴ� ����, 
                                        NULL�� ���޽� �θ� ���μ����� ���͸��� ���� ���͸��� ��
		LPSTARTUPINFO lpStartupInfo, // STRATUPINFO ����ü ������ �ʱ�ȭ �� ������ �� ������ �����͸� �μ��� ����
		LPPROCESS_INFORMATION lpProcessInformation // �����ϴ� ���μ��� ������ ��� ���� ���Ǵ� ����, 
                                                       PROCESS_INFORMATION ����ü ������ �ּ� ���� ���ڷ� ����
		);
		�ڽ� ���μ��� ����*/
		case 3:
		{
			STARTUPINFO StartUpInfo = { 0 };
			StartUpInfo.cb = sizeof(STARTUPINFO);
			PROCESS_INFORMATION ProcessInfo;
			CreateProcess("C:\\Program Files (x86)\\Notepad++\\notepad++.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &StartUpInfo, &ProcessInfo);
		}

		/* HANDLE CreateToolhelp32Snapshot(
			DWORD dwFlags, // ������ ������ ���� ����
			DWORD th32ProcessID // ������ ������ ������ ����� ����, 0 �Է½� ��� ���μ����� ������ ������
		); */

		/* BOOL Process32First(
		HANDLE           hSnapshot,
		LPPROCESSENTRY32 lppe
		); */

		/* typedef struct tagPROCESSENTRY32 {
			DWORD   dwSize;					����Ʈ ������ ����ü�� ũ��,  Process32First() �Լ� ȣ���ϱ� ���� �� ����� sizeof(PROCESSENTRY32)�� �����ؾ� ��
			DWORD   cntUsage;				// �ش� ����� ���̻� ������ ����, 0���� ����
			DWORD   th32ProcessID;          // ���� ���μ��� ID
			ULONG_PTR th32DefaultHeapID;	// �ش� ����� ���̻� ������ ����, 0���� ����
			WORD   th32ModuleID;			// �ش� ����� ���̻� ������ ����, 0���� ����
			DWORD   cntThreads;				// �� ���μ����� ���� ����Ǵ� �������� ��
			DWORD   th32ParentProcessID;    // �θ� ���μ��� ID
			LONG    pcPriClassBase;			// �� ���μ������� ���� ��� �������� �⺻ �켱����
			DWORD   dwFlags;				// �ش� ����� ���̻� ������ ����, 0���� ����
			CHAR    szExeFile[MAX_PATH];	// ���μ��� ���� ���� �̸�


		} PROCESSENTRY32; */

		case 4:
		{
			/* ������ ��� ���μ��� ������ ������ ���� �� �ش� �������� ���� �ڵ� ��ȯ */
			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			/* ���μ��� ���� ������ ���� ����ü ���� */
			PROCESSENTRY32 pe32;
			/* ����ü ������ �Ҵ� */
			pe32.dwSize = sizeof(PROCESSENTRY32);
			/* ù ��° ���μ��� ����Ʈ�� ��ü�� ���ۿ� ����Ǹ� next�� TRUE�� ��ȯ�ϰ� ù ��° ���μ��� ������ pe32�� �Ҵ� */
			BOOL next = Process32First(hSnapshot, &pe32);
			/* pe32�� �Ҵ�� ���μ��� ���� ������ �̸� �� ���μ��� ID ��� */
			printf("ProcessID of %s is %d\n", pe32.szExeFile ,pe32.th32ProcessID);
			/* ���� ���μ��� ����Ʈ�� ��ü�� ���ۿ� ����Ǹ� next�� TRUE�� ��ȯ�ϰ� ���� ���μ��� ������ pe32�� �Ҵ� */
			Process32Next(hSnapshot, &pe32);
			/* pe32�� �Ҵ�� ���μ��� ���� ������ �̸� �� ���μ��� ID ��� */
			printf("ProcessID of %s is %d\n", pe32.szExeFile, pe32.th32ProcessID);
			CloseHandle(hSnapshot);
		}

		case 5:
		{
			int i;
			printf("Select process number : ");
			scanf_s("%d", &i);
			HANDLE hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, i);
			/* Ư�� ���μ��� ���� */
			TerminateProcess(hProcessHandle ,0);
		}
	}
	scanf_s("%d", &i);
}