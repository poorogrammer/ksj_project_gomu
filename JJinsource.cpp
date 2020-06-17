#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <windows.h>
#include <io.h>


#pragma warning(disable : 4996) // 경고 해제
#define MAX_SZIE 16382 // 최대크기를 초과하기 때문에 
#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지
#define BUFFER_SIZE 256

struct _finddata_t fd;

void report(char* rpt_name);
char* get_dft_name(char* rpt_name);
void make_directory(char* full_path);
char* ConvertWCtoC(wchar_t* str);
int localpw();
void WinRm();
int whiteview();
int whiteop();
int isFileOrDir();
void FileSearch(char file_path[]);

#define DFILEPATH "C:\\test2\\testtest\\" //디폴트 경로 파일명 나중에 고치기
#define BUFFER 256

FILE* report_file;

void main() {
	char user_option[BUFFER];
	char option_arr[2][BUFFER];

	WinRm();

	while (true) {
		printf("옵션은 어쩌구 저쩌구\n"); //옵션 설명 다시 적기

		scanf_s("%[^\n]", user_option, BUFFER); getchar();

		char* context = NULL;
		char* token = strtok_s(user_option, " ", &context);
		int i = 0;
		while (token != NULL) {
			strcpy_s(option_arr[i], BUFFER, token);
			token = strtok_s(NULL, " ", &context);

			i++;
		}

		/*****************사용자 옵션 처리****************/
		if (0 == strcmp(option_arr[0], "report")) {
			if (i == 1) {
				strcpy_s(option_arr[1], BUFFER, DFILEPATH);
				strcpy_s(option_arr[1], BUFFER, get_dft_name(option_arr[1]));
			}
			report(option_arr[1]);
			fclose(report_file);	//파일닫기 보고서 작성 하는 함수로 옮기기
			break;
		}
		else if (0 == strcmp(option_arr[0], "localpw")) {
			localpw();
			printf("sdfsdfsdfsdfsdfsd");
		}
		else if (0 == strcmp(option_arr[0], "hello")) {
			printf("hello\n");
		}
		else {
			printf("오류입니다.\n"); //오류 설명 다시 적기
		}
	}
	char file_path[_MAX_PATH] = "c:";    //C:\ 경로 탐색

	FileSearch(file_path);
	system("netstat -an > whitelist02.txt");
	system("tasklist /svc > white03.txt");

}

void report(char* rpt_name) {
	make_directory(rpt_name);

	fopen_s(&report_file, rpt_name, "a");
	if (report_file == NULL) {
		printf("파일 오류 입니다.\n");	//오류 발생 메세지 다시적기
	}
	else if (report_file != NULL) {
		fputs("asdf\n", report_file);
		fputs("asdf\n", report_file);
		fputs("asdf\n", report_file);
		fputs("asdf\n", report_file);
	}
}

char* get_dft_name(char* rpt_name) {
	char dft_report[BUFFER];
	time_t t = time(NULL);
	struct tm date;

	localtime_s(&date, &t);
	strftime(dft_report, BUFFER, "%Y-%m-%d_%H%M%S.txt", &date);

	strcat_s(rpt_name, BUFFER, dft_report);

	return rpt_name;
}

void make_directory(char* full_path) {
	char temp[BUFFER], * sp;
	strcpy_s(temp, BUFFER, full_path);
	sp = temp;

	while ((sp = strchr(sp, '\\'))) {
		if (sp > temp && *(sp - 1) != ':') {
			*sp = '\0';
			_mkdir(temp);
			*sp = '\\';
		}
		sp++;
	}
}

int localpw() {
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
				return 4;
			else
				return 0;
		}
		fclose(localpolicies);
	}
	if (localpolicies == NULL) {
		printf("sdfs");
	}
}

char* ConvertWCtoC(wchar_t* str) {
	char* pStr;
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	pStr = new char[strSize];

	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}

// 관리자 권한으로 실행해야 한다.
void WinRm() {

	system("winrm quickconfig > C:/winrm.txt"); // cmd 명령어 수행

	char buffer[5] = { 0, }; // 문자열 데이터 4바이트 NULL 1바이트. 4 + 1 = 5
	int count = 0;

	FILE* fp = fopen("C:/winrm.txt", "r");

	while (feof(fp) == 0)    // 파일 포인터가 파일의 끝이 아닐 때 계속 반복
	{
		count = fread(buffer, sizeof(char), 4, fp);    // 1바이트씩 4번(4바이트) 읽기
		printf("%s", buffer);                          // 읽은 내용 출력
		memset(buffer, 0, 5);                          // 버퍼를 0으로 초기화
	}
	fclose(fp);
}


int whiteview()
{
	char fname[20];
	char str[100];
	printf("%s\n", "열 화이트 리스트 파일을 입력해주세요");
	scanf("%s", fname);

	FILE* fpr = fopen(fname, "r");
	if (fpr == NULL)
	{
		printf("%s\n", "ERROR: 파일명을 다시 확인해주세요 ");
		exit(1);
	}

	while (fgets(str, 100, fpr)) {
		printf("%s", str);
	}
	fclose(fpr);
	return 0;
}



int whiteop() {

	FILE* fp;
	char buffer[BUFFER_SIZE + 1];

	if ((fp = fopen("whitelist.txt", "a")) != NULL) {
		memset(buffer, 0, sizeof(buffer)); //buffer를 0으로 채운다.
		scanf("%s", buffer);

		fwrite(buffer, 1, strlen(buffer), fp);
		fclose(fp);
	}
}







int isFileOrDir()
{
	if (fd.attrib & _A_SUBDIR)
		return 0; // 디렉토리면 0 반환
	else
		return 1; // 그밖의 경우는 "존재하는 파일"이기에 1 반환

}

void FileSearch(char file_path[])
{
	intptr_t handle;
	int check = 0;
	char file_path2[_MAX_PATH];

	strcat(file_path, "\\");
	strcpy(file_path2, file_path);
	strcat(file_path, "*");

	if ((handle = _findfirst(file_path, &fd)) == -1)
	{
		printf("No such file or directory\n");
		return;
	}

	while (_findnext(handle, &fd) == 0)
	{
		char file_pt[_MAX_PATH];
		strcpy(file_pt, file_path2);
		strcat(file_pt, fd.name);

		check = isFileOrDir();    //파일인지 디렉토리 인지 식별

		if (check == 0 && fd.name[0] != '.')
		{
			FileSearch(file_pt);    //하위 디렉토리 검색 재귀함수
		}
		else if (check == 1 && fd.size != 0 && fd.name[0] != '.')
		{
			printf("파일명 : %s, 크기:%d\n", file_pt, fd.size);
		}
	}
	_findclose(handle);
}
