/*
2018-08-23 �Ӵ뵿

���� �����

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

��ũ�� ������ �׼����ϴµ��� �Ϲ������� Open, Access, Close�� ������ ������� �����մϴ�.
�ϵ� ��ũ�� CPU�� ���� ������� ������ ������ ���� �Լ��� ������ �׼����� ���� ���� �����̶� �ӵ��� ���̱� ���� �غ� ������ �ʿ��մϴ�.
������ ���ٴ� ���� ���� ����¿� �ʿ��� �޸� ���۸� �غ��ϰ� ����� �߿� �ʿ��� �������� �Ҵ��ϴ� �� �ʿ��� ��� �غ� �ϴ� ���Դϴ�.
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
	���� ���� �� ����

	�ش� ���̺귯�� �Լ� : fopen

	HANDLE CreateFileA(
	LPCSTR                lpFileName,				[���ϸ�(��Ʈ��ũ ��ε� ����)] - MAX_PATH ���Ͽ��� �Ѵ�.
	�ü�� �������� �ٸ����� 260�̶�� �����ϸ� ��.
	DWORD                 dwDesiredAccess,			[���� ���] - GENERIC_READ, GENERIC_WRITE �÷��װ� �ִ�.
	�� �� ������ �� �÷��׸� OR �����ڷ� �����ϸ� ��.
	DWORD                 dwShareMode,				[���� ���] - 0�̸� ������ �������� ����.
	FILE_SHARE_DELETE(NT������ ����, ���� �׼����� ���ؼ��� ������ �� �� �ִ�.),
	FILE_SHARE_READ(�б� ���� �� ���� ������ �� �� �ִ�.),
	FILE_SHARE_WRITE(���� ���� �� ���� ������ �� �� �ִ�.)
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,		[���� ��ũ����] - ���ϵ� �ڵ��� ���ϵ� ���μ����� ����� ������ ���� �ϴ� SECURITY_ATTRIBUTES ����ü�� ������, ������� ���� ��� NULL
	DWORD                 dwCreationDisposition,	[������ ���� ���] - CREATE_NEW(���ο� ������ ����� ���� ������ ������ �̹� ������ ������ ����),
	CREATE_ALWAYS(���ο� ������ ����� ���� ������ ������ �̹� ������ ���� ������ �����ϰ� �ٽ� ����),
	OPEN_EXISTING(�̹� �ִ� ������ ���� ���� ������ ������ ���� �ڵ带 �ǵ�����.),
	OPEN_ALWAYS(������ ���� ���� ������ ���� �����.),
	TRUNCATE_EXISTING(������ ���� ���� ũ�⸦ 0���� �����. �� �÷��׸� ������ GENERIC_WRITE ���� ������ ����� �Ѵ�.)
	DWORD                 dwFlagsAndAttributes,		[���� �Ӽ� �÷���] - OR �����ڷ� ������ �� �ִ�.
	FILE_ATTRIBUTE_ARCHIVE(��ī�̺� �Ӽ�),
	FILE_ATTRIBUTE_HIDDEN(���� ����),
	FILE_ATTRIBUTE_NORMAL(�ƹ� �Ӽ��� ������ ���� ���� ����, ���÷��״� �ݵ�� �ܵ����� ���Ǿ�� ��),
	FILE_ATTRIBUTE_OFFLINE(������� ���� ���� ��ġ�� �־� ��� ����� �� ���� ����),
	FILE_ATTRIBUTE_READONLY(�б� ����),
	FILE_ATTRIBUTE_SYSTEM(�ü���� ��Ÿ������ ����ϴ� ����),
	FILE_ATTRIBUTE_TEMPORARY(�ӽ� ����ҿ� ����Ǵ� ����, �� �Ӽ��� ������ ��ũ�� ������� �ʰ� �޸𸮿� ����ǹǷ� ����� �ӵ��� ������. ��� �Ŀ� �ݵ�� ������ ��)
	HANDLE                hTemplateFile				[���ø� ���� �ڵ�] - ���� ������� �ϴ� ������ �߰� �Ӽ��� �����ϴ� ���ø� ������ �ڵ��� ����.
	�� 95/98�� �������� ����, ū �ǿ뼺�� ���� ��� ������ �ʾ� NULL�� �����ϴ� ��찡 ����.
	);

	https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-createfilea
	*/
	hFile = CreateFileA("Test.txt", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	/*
	���� ���� ����

	DWORD SetFilePointer(
	HANDLE hFile,					[���� �ڵ�]
	LONG   lDistanceToMove,			[64��Ʈ ���� 32��Ʈ]
	PLONG  lpDistanceToMoveHigh,	[64��Ʈ ���� 32��Ʈ]
	DWORD  dwMoveMethod				[�̵� ���� ��ġ�� ����]
	);

	https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-setfilepointer
	*/
	//SetFilePointer(hFile, 0, NULL, FILE_CURRENT);

	if (hFile != INVALID_HANDLE_VALUE) {
		/*
		���� �б�

		�ش� ���̺귯�� �Լ� : fread

		ReadFile �Լ��� ������ ���� �����ϸ� 0�� ��ȯ�ϰ� GetLastError�Լ��� ERROR_HANDLE_EOF�� ��ȯ

		BOOL ReadFile(
		HANDLE                        hFile,				[���� �ڵ�]
		__out_data_source(FILE)LPVOID lpBuffer,				[���� �����͸� ������ ����]
		DWORD                         nNumberOfBytesToRead,	[���� �ִ� ����Ʈ ũ��]
		LPDWORD                       lpNumberOfBytesRead,	[���� ����� ��忡�� �о���� �������� ����Ʈ ���� �ѱ�]
		LPOVERLAPPED                  lpOverlapped			[�񵿱� ������� ���� OVERLAPPED ����ü�� ������, �񵿱� ������� �ƴ϶�� NULL�� ���]
		);

		https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-readfile
		*/
		ReadFile(hFile, buf, 1024, &dwRead, NULL);
		/*
		���� ����

		�ش� ���̺귯�� �Լ� : fwrite

		BOOL WriteFile(
		HANDLE       hFile,						[���� �ڵ�]
		LPCVOID      lpBuffer,					[�����̳� ��ġ�� ���� �����͸� �����ϱ� ���� ���۸� ����Ű�� ������]
		DWORD        nNumberOfBytesToWrite,		[�� �ִ� ����Ʈ ũ��]
		LPDWORD      lpNumberOfBytesWritten,	[���� ����� ��忡�� ������ ������ �������� ����Ʈ ���� �ѱ�]
		LPOVERLAPPED lpOverlapped				[�񵿱� ������� ���� OVERLAPPED ����ü�� ������, �񵿱� ������� �ƴ϶�� NULL�� ���]
		);

		https://docs.microsoft.com/ko-kr/windows/desktop/api/fileapi/nf-fileapi-writefile
		*/
		WriteFile(hFile, buf, lstrlen(buf), &dwWritten, NULL);
		printf("Read Datas\n");
		/*
		���� �ݱ�

		�ش� ���̺귯�� �Լ� : fclose

		���� �ڵ��� �޸𸮸� �����ϰ� ������� ���� �뷮�� ���۸� ����ϹǷ� �� ����ϰ� �� �� ����
		����� ���� ��� �޸� ����

		BOOL WINAPI CloseHandle(
		_In_ HANDLE hObject		[���� �ڵ�]
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
�񵿱� �����

���Ⱑ �����ϸ� TRUE�� ��ȯ�ϰ�, �񵿱� ������ ��쿡�� ������ FALSE�� ��ȯ�Ѵ�.
�׷��� GetLastError()�� ���� �� ������ ERROR_IO_PENDING�̸� �Լ��� ���� �� ���� �ƴϰ�, �������̴�.

BOOL GetOverlappedResult(
HANDLE       hFile,							[���� �ڵ�]
LPOVERLAPPED lpOverlapped,					[�񵿱� ������� ���� OVERLAPPED ����ü�� ������]
LPDWORD      lpNumberOfBytesTransferred,	[������� ������� ����Ʈ ��, �Ϸ�ÿ��� ����� ����]
BOOL         bWait							[������� �Ϸ�� ������ ����� ���ΰ� �ƴѰ��� ����]
);

ex)

OVERLAPPED ov;

GetOverlappedResult(hFile, &ov, &Tran, FALSE);

https://docs.microsoft.com/ko-kr/windows/desktop/api/ioapiset/nf-ioapiset-getoverlappedresult
*/