#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>

void report(char* rpt_name);
char* get_dft_name(char* rpt_name);
void make_directory(char* full_path);

#define DFILEPATH "C:\\test2\\testtest\\" //디폴트 경로 파일명 나중에 고치기
#define BUFFER 256

FILE* report_file;

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
			fclose(report_file);	//파일닫기 보고서 작성 하는 함수로 옮기기
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

void report(char* rpt_name) {
	make_directory(rpt_name);

	fopen_s(&report_file, rpt_name, "a");
	if (report_file == NULL) {
		printf("파일 오류 입니다.\n");	//오류 발생 메세지 다시적기
	}
	else if (report_file != NULL){
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

void make_directory(char* full_path){
	char temp[BUFFER], *sp;
	strcpy_s(temp, BUFFER,full_path); 
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
