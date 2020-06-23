#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <windows.h>

void report(char* rpt_name);
void setting_report(char* rpt_name);
char* get_dft_name(char* rpt_name);
void make_directory(char* full_path);
char* ConvertWCtoC(wchar_t* str);

int local_policies();
void sharedfolder_policies();

FILE* mitremap(FILE* report_file, int token);

#define DFILEPATH "C:\\test2\\testtest\\" //디폴트 경로 파일명 나중에 고치기
#define BUFFER 256

void main() {
	char user_option[BUFFER];
	char option_arr[2][BUFFER];

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
			break;
		}
		else if (0 == strcmp(option_arr[0], "setting")) {
			if (i == 1) {
				strcpy_s(option_arr[1], BUFFER, DFILEPATH);
				strcpy_s(option_arr[1], BUFFER, get_dft_name(option_arr[1]));
			}
			setting_report(option_arr[1]);
			break;
		}
		else if (0 == strcmp(option_arr[0], "hello")) {
			printf("hello\n");
		}
		else {
			printf("오류입니다.\n"); //오류 설명 다시 적기
		}
	}
}

/*********리포트 작성 함수*********/
void report(char* rpt_name) {
	FILE* report_file;
	FILE* srdfile;
	make_directory(rpt_name);

	fopen_s(&report_file, rpt_name, "a");
	if (report_file == NULL) {
		printf("파일 오류 입니다.\n");	//오류 발생 메세지 다시적기
	}
	else if (report_file != NULL) {
		if (0 == local_policies()) {/////////////////////////////////////////////////
			fputs("암호정책 잘댐\n", report_file);
			
		}
		else if (4 == local_policies()) {
			fputs("암호정책 안좋음 바까조\n", report_file);
			fputs("***********************************\n\n", report_file);
		}
		mitremap(report_file, 4);
		_unlink("D:\\setfile.inf");

		sharedfolder_policies(); ///////////////////////////////////////////
		fopen_s(&srdfile, "C:\\test2\\sfolder.txt", "r+");
		while (!feof(srdfile)) {
			char buff[100];
			fgets(buff, 100, srdfile);
			fputs(buff, report_file);
		}
		fclose(srdfile);
		_unlink("C:\\test2\\sfolder.txt");
	}

	fclose(report_file);
}
void setting_report(char* rpt_name) {
	FILE* report_file, *setfile;
	FILE* srdfile;
	make_directory(rpt_name);

	fopen_s(&report_file, rpt_name, "a");
	if (report_file == NULL) {
		printf("파일 오류 입니다.\n");	//오류 발생 메세지 다시적기
	}
	else if (report_file != NULL) {
		if (0 == local_policies()) {
			fputs("암호정책 잘댐\n", report_file);
			
		} else if (4 == local_policies()) {			// 정책 바꿔주기
			fopen_s(&setfile, "D:\\setfile.inf", "w");
			fputs("[System Access]\n", setfile);
			fputs("PasswordComplexity = 0\n", setfile);
			fputs("[Version]\nsignature=\"\$CHICAGO\$\"\nRevision=1", setfile);
			fclose(setfile);

			system("secedit /configure /db D:\\setfile2.sdb /cfg D:\\setfile.inf");
			_unlink("D:\\setfile2.sdb");
			_unlink("D:\\setfile2.jfm");

			fputs("취약한 암호정보가 변경되었습니다.\n", report_file);
		}
		_unlink("D:\\setfile.inf");

		local_policies();
		fopen_s(&srdfile, "C:\\test2\\sfolder.txt", "r+");
		while (!feof(srdfile)) {
			char buff[100];
			fgets(buff, 100, srdfile);
			fputs(buff, report_file);
		}
		fclose(srdfile);
		_unlink("C:\\test2\\sfolder.txt");
	}

	fclose(report_file);
}


/********로컬 정책 암호화 되지 않은 패스워드********/
int local_policies() {
	FILE* localpolicies;
	char buff[100];
	wchar_t wbuff[100];

	char* ptr;

	system("secedit /export /cfg D:\\setfile.inf");	//디폴트 경로 바꾸기
	//Sleep(1000);
	system("cls");	//좀이상 ㅋㅋ

	fopen_s(&localpolicies, "D:\\setfile.inf", "r+,ccs=UNICODE");
	if (localpolicies != NULL) {
		while (!feof(localpolicies)) {
			fgetws(wbuff, 100, localpolicies);
			strcpy_s(buff, 100, ConvertWCtoC(wbuff));

			ptr = strstr(buff, "PasswordComplexity = 1");	//설정 안됨 = 취약
			if (ptr != NULL) {
				fclose(localpolicies);
				return 4;
			}
			ptr = strstr(buff, "PasswordComplexity = 0");	//설정 됨 = 양호
			if (ptr != NULL) {
				fclose(localpolicies);
				return 0;
			}
		}
	}
	if (localpolicies == NULL) 
		printf("로컬 정책 파일 오류");
	
	return 100000;	//리턴값 수정
}
/**************공유폴더 권한***************/
void sharedfolder_policies() {
	FILE* netshare, * filepolicies, * returnfile;
	char buff[100];
	static int k = 0;

	struct gps {
		char filename[100];
		char groupname[20][100] = {};
		char policy[20][20] = {};
	};

	struct gps gropolset[10];

	/*******공유 파일 읽기********/
	system("net share > C:\\test2\\netshare.txt");
	fopen_s(&netshare, "C:\\test2\\netshare.txt", "r");
	if (netshare != NULL) {	//net share 파일 읽기 시작
		char* token, * temp;

		int i = 0;
		while (!feof(netshare)) {
			fgets(buff, 100, netshare);	//net share 파일 한 줄씩 읽기

			if (i >= 4) {
				strtok_s(buff, " ", &token);
				strtok_s(token, " ", &temp);	//중간에 있는 값 크롭


				if (NULL != strchr(token, 'C')) {	//C로 시작하는 문자열 = 공유폴더
					token = strchr(token, 'C');
					strcpy_s(gropolset[k].filename, 100, token);
					k++;
				}
				else if (NULL != strchr(token, 'D')) {	//D로 시작하는 문자열 = 공유폴더
					token = strchr(token, 'D');
					strcpy_s(gropolset[k].filename, 100, token);
					k++;
				}
			}
			i++;
		}
	}
	fclose(netshare);

	/*******권한 파일 읽기********/
	for (int i = 0; i < k; i++) {
		char icacls[150] = "icacls ";
		char* temp, * groupplo, * groupname;
		strcat_s(icacls, gropolset[i].filename);
		strcat_s(icacls, " > C:\\test2\\temp.txt");
		system(icacls);

		fopen_s(&filepolicies, "C:\\test2\\temp.txt", "r");
		if (filepolicies != NULL) {
			int j = 0;
			while (!feof(filepolicies)) {	//권한 파일 열기
				fgets(buff, 100, filepolicies);

				if (NULL != strchr(buff, ':')) {
					if (j == 0) {
						strtok_s(buff, ":", &temp);
						strtok_s(temp, ":", &groupplo);
						groupname = strrchr(temp, '\\');
					}
					else {
						strtok_s(buff, ":", &groupplo);
						if (NULL == (groupname = strrchr(buff, '\\')))
							groupname = strrchr(buff, ' ');
					}

					if (groupname != NULL) {
						strcpy_s(gropolset[i].groupname[j], groupname + 1);
						if (NULL != (strrchr(groupplo, '\(')))
							strcpy_s(gropolset[i].policy[j], strrchr(groupplo, '\('));
						j++;
					}
				}
			}
		}
		fclose(filepolicies);	//파일삭제
	}

	/*******출력 파일 작성********/
	fopen_s(&returnfile, "C:\\test2\\sfolder.txt", "a");
	char* filename;
	char* token;
	for (int i = 0; i < k; i++) {
		filename = gropolset[i].filename;
		fputs("\n\n공유폴더 ", returnfile);
		fputs(filename, returnfile);
		fputs("의 권한은\n", returnfile);

		for (int j = 0; j < sizeof(gropolset[i].groupname) / sizeof(gropolset[i].groupname[0]); j++) {
			if (0 != *gropolset[i].groupname[j]) {
				if (NULL != strstr(gropolset[i].groupname[j], "Level")) continue;

				fputs(gropolset[i].groupname[j], returnfile);
				fputs("그룹은 현재 ", returnfile);

				strtok_s(gropolset[i].policy[j], "\)", &token);
				if (0 == strcmp(gropolset[i].policy[j], "\(N"))
					fputs("없음", returnfile);
				else if (0 == strcmp(gropolset[i].policy[j], "\(F"))
					fputs("모든", returnfile);
				else if (0 == strcmp(gropolset[i].policy[j], "\(M"))
					fputs("수정", returnfile);
				else if (0 == strcmp(gropolset[i].policy[j], "\(RX"))
					fputs("읽기 및 실행", returnfile);
				else if (0 == strcmp(gropolset[i].policy[j], "\(R"))
					fputs("읽기 전용", returnfile);
				else if (0 == strcmp(gropolset[i].policy[j], "\(W"))
					fputs("쓰기 전용", returnfile);
				else if (0 == strcmp(gropolset[i].policy[j], "\(D"))
					fputs("삭제", returnfile);

				fputs("권한 입니다.\n", returnfile);

				if (0 == strcmp(gropolset[i].groupname[j], gropolset[i].groupname[j + 1]))
					j++;
			}
		}
	}
	fclose(returnfile);
}


/*********마이터 맵핑 함수************/
FILE* mitremap(FILE* report_file, int token) {
	switch (token) {
		case 1: fputs("zzz", report_file); break;
		case 4: fputs("암호화 정책 마이터 어쩌구", report_file); break;
	};

	return report_file;
}


/***********리포트 이름 작성 함수***********/
char* get_dft_name(char* rpt_name) {
	char dft_report[BUFFER];
	time_t t = time(NULL);
	struct tm date;

	localtime_s(&date, &t);
	strftime(dft_report, BUFFER, "%Y-%m-%d_%H%M%S.txt", &date);

	strcat_s(rpt_name, BUFFER, dft_report);

	return rpt_name;
}

/********리포트 작성시 입력된 디렉토리 생성 함수*********/
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

/**********인코딩 변환 함수***********/
char* ConvertWCtoC(wchar_t* str) {
	char* pStr;
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	pStr = new char[strSize];

	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}