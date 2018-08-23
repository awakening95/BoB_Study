/*
2018-08-23 임대동

파일 입출력

HANDLE CreateFile(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
BOOL ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
BOOL WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped);
BOOL CloseHandle(HANDLE hObject)
;
DWORD SetFilePointer(HANDLE hFile, LONG IDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
BOOL GetOverlappedResult(HANDLE hFile, LPOVERLAPPED lpOverlapped, LPDWORD lpNumberOfBytesTransferred, BOOL bWait);

BOOL CopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFaillfExists);
BOOL CopyFileEx(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, LPPROGRESS_ROUTINE lpProgressRoutine, LPVOID lpData, LPBOOL pbCancel, DWORD dwCopyFlags);
BOOL MoveFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName);
BOOL MoveFileEx(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, DWORD dwFlags);
BOOL DeleteFile(LPCTSTR lpFileName);

int rename(const char * oldname, const char * newname);
DWORD GetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
DWORD GetFileAttributes(LPCTSTR lpFileName);

int access(const char * path, int mode);
void _splitpath(const char * path, char * drive, char * dir, char * fname, char * ext);

int SHFileOperation(LPSHFILEOPSTRUCT lpFileOp);

디스크의 파일을 액세스하는데는 일반적으로 Open, Access, Close의 과정을 순서대로 진행합니다.
하드 디스크가 CPU에 비해 상대적을 느리기 때문에 단일 함수로 파일을 액세스할 수는 없고 조금이라도 속도를 높이기 위한 준비 과정이 필요합니다.
파일을 연다는 것은 파일 입출력에 필요한 메모리 버퍼를 준비하고 입출력 중에 필요한 변수들을 할당하는 등 필요한 모든 준비를 하는 것입니다.
*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main(int argc, char * argv[]) {
	TCHAR buf[1024];
	//TCHAR * wbuf = "Hello World";
	HANDLE hFile;
	DWORD dwRead;
	DWORD dwWritten;

	/*
	파일 열기 및 생성

	해당 라이브러리 함수 : fopen

	HANDLE CreateFileA(
	LPCSTR                lpFileName,				[파일명(네트워크 경로도 가능)] - MAX_PATH 이하여야 한다.
	운영체제 버전별로 다르지만 260이라고 생각하면 됨.
	DWORD                 dwDesiredAccess,			[접근 모드] - GENERIC_READ, GENERIC_WRITE 플래그가 있다.
	둘 다 쓰려면 두 플래그를 OR 연산자로 연결하면 됨.
	DWORD                 dwShareMode,				[공유 모드] - 0이면 파일은 공유되지 않음.
	FILE_SHARE_DELETE(NT에서만 가능, 삭제 액세스에 대해서만 파일을 열 수 있다.),
	FILE_SHARE_READ(읽기 모드로 열 때만 파일을 열 수 있다.),
	FILE_SHARE_WRITE(쓰기 모드로 열 때만 파일을 열 수 있다.)
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,		[보안 디스크립터] - 리턴된 핸들을 차일드 프로세스로 상속할 것인지 지정 하는 SECURITY_ATTRIBUTES 구조체의 포인터, 사용하지 않을 경우 NULL
	DWORD                 dwCreationDisposition,	[파일을 여는 방법] - CREATE_NEW(새로운 파일을 만들되 만약 지정한 파일이 이미 있으면 만들지 않음),
	CREATE_ALWAYS(새로운 파일을 만들되 만약 지정한 파일이 이미 있으면 기존 파일을 삭제하고 다시 만듬),
	OPEN_EXISTING(이미 있는 파일을 열되 만약 파일이 없으면 에러 코드를 되돌린다.),
	OPEN_ALWAYS(파일을 열되 만약 없으면 새로 만든다.),
	TRUNCATE_EXISTING(파일을 열고 파일 크기를 0으로 만든다. 이 플래그를 쓰려면 GENERIC_WRITE 모드로 파일을 열어야 한다.)
	DWORD                 dwFlagsAndAttributes,		[파일 속성 플래그] - OR 연산자로 묶어줄 수 있다.
	FILE_ATTRIBUTE_ARCHIVE(아카이브 속성),
	FILE_ATTRIBUTE_HIDDEN(숨은 파일),
	FILE_ATTRIBUTE_NORMAL(아무 속성도 가지지 않은 보통 파일, 이플래그는 반드시 단독으로 사용되어야 함),
	FILE_ATTRIBUTE_OFFLINE(연결되지 않은 저장 장치에 있어 즉시 사용할 수 없는 파일),
	FILE_ATTRIBUTE_READONLY(읽기 전용),
	FILE_ATTRIBUTE_SYSTEM(운영체제가 배타적으로 사용하는 파일),
	FILE_ATTRIBUTE_TEMPORARY(임시 저장소에 저장되는 파일, 이 속성의 파일은 디스크에 저장되지 않고 메모리에 저장되므로 입출력 속도가 빠르다. 사용 후에 반드시 지워야 함)
	HANDLE                hTemplateFile				[템플릿 파일 핸들] - 새로 만들고자 하는 파일의 추가 속성을 지원하는 템플릿 파일의 핸들을 지정.
	윈 95/98은 지원하지 않음, 큰 실용성이 없어 통상 사용되지 않아 NULL로 지정하는 경우가 많음.
	);

	https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-createfilea
	*/
	hFile = CreateFileA("Test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	/*
	파일 임의 접근

	DWORD SetFilePointer(
	HANDLE hFile,					[파일 핸들]
	LONG   lDistanceToMove,			[64비트 하위 32비트]
	PLONG  lpDistanceToMoveHigh,	[64비트 상위 32비트]
	DWORD  dwMoveMethod				[이동 시작 위치를 지정]
	);

	https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-setfilepointer
	*/
	//SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

	if (hFile != INVALID_HANDLE_VALUE) {
		/*
		파일 읽기

		해당 라이브러리 함수 : fread

		ReadFile 함수가 파일의 끝에 도달하면 0을 반환하고 GetLastError함수는 ERROR_HANDLE_EOF를 반환

		BOOL ReadFile(
		HANDLE                        hFile,				[파일 핸들]
		__out_data_source(FILE)LPVOID lpBuffer,				[읽은 데이터를 저장할 버퍼]
		DWORD                         nNumberOfBytesToRead,	[읽을 최대 바이트 크기]
		LPDWORD                       lpNumberOfBytesRead,	[동기 입출력 모드에서 읽어들인 데이터의 바이트 수를 넘김]
		LPOVERLAPPED                  lpOverlapped			[비동기 입출력을 위한 OVERLAPPED 구조체의 포인터, 비동기 입출력이 아니라면 NULL을 사용]
		);

		https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-readfile
		*/
		ReadFile(hFile, buf, 1024, &dwRead, NULL);
		/*
		파일 쓰기

		해당 라이브러리 함수 : fwrite

		BOOL WriteFile(
		HANDLE       hFile,						[파일 핸들]
		LPCVOID      lpBuffer,					[파일이나 장치로 부터 데이터를 저장하기 위한 버퍼를 가리키는 포인터]
		DWORD        nNumberOfBytesToWrite,		[쓸 최대 바이트 크기]
		LPDWORD      lpNumberOfBytesWritten,	[동기 입출력 모드에서 실제로 쓰여진 데이터의 바이트 수를 넘김]
		LPOVERLAPPED lpOverlapped				[비동기 입출력을 위한 OVERLAPPED 구조체의 포인터, 비동기 입출력이 아니라면 NULL을 사용]
		);

		https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-writefile
		*/
		WriteFile(hFile, buf, lstrlen(buf), &dwWritten, NULL);
		printf("Read Datas\n");
		/*
		파일 닫기

		해당 라이브러리 함수 : fclose

		파일 핸들은 메모리를 차지하고 입출력을 위해 대량의 버퍼를 사용하므로 다 사용하고 난 후 해제
		사용이 끝난 즉시 메모리 해제

		BOOL WINAPI CloseHandle(
		_In_ HANDLE hObject		[파일 핸들]
		);

		https://msdn.microsoft.com/ko-kr/library/windows/desktop/ms724211(v=vs.85).aspx
		*/
		CloseHandle(hFile);
	}
	else {
		printf("Error\n");
	}
	return 0;

}

/*
비동기 입출력

쓰기가 성공하면 TRUE를 반환하고, 비동기 쓰기의 경우에는 무조건 FALSE를 반환한다.
그러나 GetLastError()를 통해 얻어낸 에러가 ERROR_IO_PENDING이면 함수가 실패 한 것은 아니고, 진행중이다.

BOOL GetOverlappedResult(
HANDLE       hFile,							[파일 핸들]
LPOVERLAPPED lpOverlapped,					[비동기 입출력을 위한 OVERLAPPED 구조체의 포인터]
LPDWORD      lpNumberOfBytesTransferred,	[현재까지 입출력한 바이트 수, 완료시에만 제대로 조사]
BOOL         bWait							[입출력이 완료될 때까지 대기할 것인가 아닌가를 지정]
);

ex)

OVERLAPPED ov;

GetOverlappedResult(hFile, &ov, &Tran, FALSE);

https://docs.microsoft.com/ko-kr/windows/desktop/api/ioapiset/nf-ioapiset-getoverlappedresult
*/