#include<stdio.h>
#include<stdlib.h>
#include<tchar.h>
#include<windows.h>
#include<tlhelp32.h>

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hProcessSnap =
		CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	//현재 모든 프로세스들의 상태를 스냅합니다.

	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreateToolhelp32Snapshot error \n"));
		exit(EXIT_FAILURE);
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	//프로세스 상태 정보를 담을 구조체를 선언합니다.

	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First error ! \n"));
		CloseHandle(hProcessSnap);
		exit(EXIT_FAILURE);
	}
	//첫번째 프로세스의 정보를 가져오는 경우와 다음 프로세스 정보를
	//가져올 경우에 다른 함수를 쓰게 됩니다. Process32First ,Process32Next

	_tprintf(_T("\t[Process name] \t[PID]\t[ThreadID]\t[PPID] \n"));

	do {
		_tprintf(_T("%25s %8d %8d %8d \n"),
			pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.th32ParentProcessID);
	} while (Process32Next(hProcessSnap, &pe32));
	//PROCESSENTRY32 구조체에 위에서 출력한 정보들보다
	// 더 많은 정보들이 저장되어 있습니다. while()을 이용하여 모두 출력 후 종료

	return 0;
}