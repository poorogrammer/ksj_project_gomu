#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <windows.h>

void report(char* rpt_name);
char* get_dft_name(char* rpt_name);
void make_directory(char* full_path);
char* ConvertWCtoC(wchar_t* str);
int localpw();

#define DFILEPATH "C:\\test2\\testtest\\" //����Ʈ ��� ���ϸ� ���߿� ��ġ��
#define BUFFER 256

FILE* report_file;

void main() {
	char user_option[BUFFER];
	char option_arr[2][BUFFER];

	while (true) {
		printf("�ɼ��� ��¼�� ��¼��\n"); //�ɼ� ���� �ٽ� ����

		scanf_s("%[^\n]", user_option, BUFFER); getchar();

		char* context = NULL;
		char* token = strtok_s(user_option, " ", &context);
		int i = 0;
		while (token != NULL) {
			strcpy_s(option_arr[i], BUFFER, token);
			token = strtok_s(NULL, " ", &context);

			i++;
		}

		/*****************����� �ɼ� ó��****************/
		if (0 == strcmp(option_arr[0], "report")) {
			if (i == 1) {
				strcpy_s(option_arr[1], BUFFER, DFILEPATH);
				strcpy_s(option_arr[1], BUFFER, get_dft_name(option_arr[1]));
			}
			report(option_arr[1]);
			fclose(report_file);	//���ϴݱ� ���� �ۼ� �ϴ� �Լ��� �ű��
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
			printf("�����Դϴ�.\n"); //���� ���� �ٽ� ����
		}
	}
}

void report(char* rpt_name) {
	make_directory(rpt_name);

	fopen_s(&report_file, rpt_name, "a");
	if (report_file == NULL) {
		printf("���� ���� �Դϴ�.\n");	//���� �߻� �޼��� �ٽ�����
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

	system("secedit /export /cfg C:\\new.txt");	//����Ʈ ��� �ٲٱ� ���߿� ���ϻ��� �Ҽ������� �ϱ�
	system("cls");	//���̻� ����

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

