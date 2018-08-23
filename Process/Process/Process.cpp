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
		DWORD dwDesiredAccess, // 접근 유형, 접근 권한, PROCESS_ALL_ACCESS는 모든 권한
		BOOL  bInheritHandle, // 상속여부	
		DWORD dwProcessId // 프로세스 ID(PID)
		);
		프로세스의 handle을 반환*/
		case 1:
		{
			HANDLE hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 11328);
			printf("%d", hProcessHandle);
		}

		/*DECLSPEC_NORETURN VOID ExitProcess(
		UINT uExitCode // 프로세스 종료 코드를 설정, 정상 종료 인경우 0을 비 정상 종료인 경우 -1을 입력
		);
		반환 값 없음
		함수를 호출한 프로세스(프로세스 내 모든 스레드 포함)를 종료*/
		case 2:
		{
			ExitProcess(0);
		}

		/*BOOL CreateProcess(
		LPCTSTR lpApplicationName, // 생성할 프로세스의 실행파일 이름을 절대경로를 포함한 인자로 전달
		LPTSTR lpCommandLine, // 프로세스에 인자를 전달할 때 이용하거나 첫 번째 인자에 NULL을 
                                 준 경우 표준 검색 경로의 실행파일의 이름을 전달
		LPSECURITY_ATTRIBUTES lpProcessAttributes, // 프로세스의 보안 속성을 지정, NULL을 전달할 경우 디폴트 보안 속성 지정
		LPSECURITY_ATTRIBUTES lpThreadAttributes, // 쓰레드의 보안 속성을 지정, NULL을 전달할 경우 디폴트 보안 속성 지정
		BOOL bInheritHandles, // 전달인자가 TRUE일 경우, 생성되는 자식 프로세스는 부모 프로세스가 소유하는 handle중 일부를 상속
		DWORD dwCreationFlags, // 생성하는 프로세스의 특성(우선순위 등)을 결정지을 떄 사용, 설정하지 않을 때는 0을 전달
		LPVOID lpEnvironment, // 생성될 프로세스가 사용할 환경변수의 포인터 지정, NULL을 지정하면 부모 프로세스의 환경블록을 상속
		LPCTSTR lpCurrentDirectory, // 현재 디렉토리를 설정하는 인자, 
                                        NULL로 전달시 부모 프로세스의 디렉터리를 현재 디렉터리로 함
		LPSTARTUPINFO lpStartupInfo, // STRATUPINFO 구조체 변수를 초기화 한 다음에 이 변수의 포인터를 인수로 전달
		LPPROCESS_INFORMATION lpProcessInformation // 생성하는 프로세스 정보를 얻기 위해 사용되는 인자, 
                                                       PROCESS_INFORMATION 구조체 변수의 주소 값을 인자로 전달
		);
		자식 프로세스 생성*/
		case 3:
		{
			STARTUPINFO StartUpInfo = { 0 };
			StartUpInfo.cb = sizeof(STARTUPINFO);
			PROCESS_INFORMATION ProcessInfo;
			CreateProcess("C:\\Program Files (x86)\\Notepad++\\notepad++.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &StartUpInfo, &ProcessInfo);
		}

		/* HANDLE CreateToolhelp32Snapshot(
			DWORD dwFlags, // 생성할 스냅샷 종류 설정
			DWORD th32ProcessID // 스냅샷 정보를 생성할 대상을 지정, 0 입력시 모든 프로세스의 정보를 스냅샷
		); */

		/* BOOL Process32First(
		HANDLE           hSnapshot,
		LPPROCESSENTRY32 lppe
		); */

		/* typedef struct tagPROCESSENTRY32 {
			DWORD   dwSize;					바이트 단위인 구조체의 크기,  Process32First() 함수 호출하기 전에 이 멤버를 sizeof(PROCESSENTRY32)로 설정해야 함
			DWORD   cntUsage;				// 해당 멤버는 더이상 사용되지 않음, 0으로 설정
			DWORD   th32ProcessID;          // 현재 프로세스 ID
			ULONG_PTR th32DefaultHeapID;	// 해당 멤버는 더이상 사용되지 않음, 0으로 설정
			WORD   th32ModuleID;			// 해당 멤버는 더이상 사용되지 않음, 0으로 설정
			DWORD   cntThreads;				// 이 프로세스에 의해 실행되는 스레드의 수
			DWORD   th32ParentProcessID;    // 부모 프로세스 ID
			LONG    pcPriClassBase;			// 이 프로세스에서 만든 모든 스레드의 기본 우선순위
			DWORD   dwFlags;				// 해당 멤버는 더이상 사용되지 않음, 0으로 설정
			CHAR    szExeFile[MAX_PATH];	// 프로세스 실행 파일 이름


		} PROCESSENTRY32; */

		case 4:
		{
			/* 지정한 모든 프로세스 스냅샷 정보를 생성 및 해당 스냅샷에 대한 핸들 반환 */
			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			/* 프로세스 상태 정보를 담을 구조체 선언 */
			PROCESSENTRY32 pe32;
			/* 구조체 사이즈 할당 */
			pe32.dwSize = sizeof(PROCESSENTRY32);
			/* 첫 번째 프로세스 리스트의 객체가 버퍼에 복사되면 next에 TRUE를 반환하고 첫 번째 프로세스 정보를 pe32에 할당 */
			BOOL next = Process32First(hSnapshot, &pe32);
			/* pe32에 할당된 프로세스 실행 파일의 이름 및 프로세스 ID 출력 */
			printf("ProcessID of %s is %d\n", pe32.szExeFile ,pe32.th32ProcessID);
			/* 다음 프로세스 리스트의 객체가 버퍼에 복사되면 next에 TRUE를 반환하고 다음 프로세스 정보를 pe32에 할당 */
			Process32Next(hSnapshot, &pe32);
			/* pe32에 할당된 프로세스 실행 파일의 이름 및 프로세스 ID 출력 */
			printf("ProcessID of %s is %d\n", pe32.szExeFile, pe32.th32ProcessID);
			CloseHandle(hSnapshot);
		}

		case 5:
		{
			int i;
			printf("Select process number : ");
			scanf_s("%d", &i);
			HANDLE hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, i);
			/* 특정 프로세스 종료 */
			TerminateProcess(hProcessHandle ,0);
		}
	}
	scanf_s("%d", &i);
}