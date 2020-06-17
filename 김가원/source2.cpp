#include <windows.h>
#include <stdio.h>
#include <string.h>

char* ConvertWCtoC(wchar_t* str);

void main() {
	FILE* localpolicies;
	char buff[100];
	wchar_t wbuff[100];

	char* ptr;

	system("secedit /export /cfg C:\\new.txt");	//디폴트 경로 바꾸기 나중에 파일삭제 할수있으면 하기
	system("cls");	//좀이상 ㅋㅋ

	fopen_s(&localpolicies, "C:\\new.txt", "r,ccs=UNICODE");
	if (localpolicies != NULL) {
		while (!feof(localpolicies)) {
			fgetws(wbuff, 100, localpolicies);
			strcpy_s(buff, 100, ConvertWCtoC(wbuff));
	
			ptr = strstr(buff, "PasswordComplexity = 0");
			if (ptr != NULL)
				printf("%s", ptr);
			else ;	//return 값 수정
		}	
		fclose(localpolicies);
	}
	if (localpolicies == NULL) {
		printf("sdfs");
	}
}

char* ConvertWCtoC(wchar_t* str){
	char* pStr;
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	pStr = new char[strSize];

	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}