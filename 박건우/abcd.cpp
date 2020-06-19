#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable : 4996)
#define SIZE 100
int main(void)
{
    FILE* fp1;
    FILE* fp2;
    char a[SIZE];
    char b[SIZE];
    char f1[SIZE];
    char f2[SIZE];
    int bytes = 0;
    printf("첫번째 파일 이름: ");
    gets_s(a);
    printf("두번째 파일 이름: ");
    gets_s(b);
    if ((fp1 = fopen(a, "r")) == NULL)
    {
        fprintf(stderr, "파일 열기 오류1\n");
        exit(1);
    }
    if ((fp2 = fopen(b, "r")) == NULL)
    {
        fprintf(stderr, "파일 열기 오류2\n");
        exit(1);
    }
    while (1)
    {
        fgets(f1, sizeof(f1), fp1); //fgets는 \n(개행문자) 나올 때까지 문자열을 받음 
        fgets(f2, sizeof(f2), fp2);
        if (strcmp(f1, f2) != 0) // f1이 크면 양, f2가 크면 음, 같으면 0
        {
            printf("<< %s\n", f1);
            printf(">> %s\n", f2);
            break;
        }
        if (feof(fp1) != 0) // 파일의 끝이면 not0, 끝이 아니면 0
        {
            printf("파일은 서로 일치함\n");
            break;
        }
    }
    return 0;
}
