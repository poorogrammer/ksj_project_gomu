#include <stdio.h>
#include <windows.h>
#pragma warning(disable : 4996) // 경고 해제
#define MAX_SZIE 16382 // 최대크기를 초과하기 때문에 
#define _CRT_SECURE_NO_WARNINGS    // fopen 보안 경고로 인한 컴파일 에러 방지

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


int main() {

    WinRm();

    return 0;
}