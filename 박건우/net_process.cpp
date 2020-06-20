#include <stdio.h>
#include <windows.h>
#include <string.h> 

#pragma warning(disable : 4996) 
#define _CRT_SECURE_NO_WARNINGS    
# define MAX_STR_SIZE 65535

void Eliminate(char* str, char ch)
{
    for (; *str != '\0'; str++)//종료 문자를 만날 때까지 반복
    {
        if (*str == ch)//ch와 같은 문자일 때
        {
            strcpy(str, str + 1);
            str--;
        }   
    }
}

void filter()
{
	char str[] = "Geeks-for-Geeks";

	char* token = strtok(str, "-");


	while (token != NULL) {
		printf("%s\n", token);
		token = strtok(NULL, "-");
	}
}

int main() {

    system("tasklist /fo csv > C:/whitelist01.txt");

    FILE* fp = fopen("C:/whitelist01.txt", "r");
    FILE* fp2 = fopen("C:/whiltlist0101.txt", "w");

    char s[4] = "\n\",";
	char buffer[100];
    char* token;
    
    
    while (fgets(buffer, MAX_STR_SIZE, fp)) {
       
       
        token = strtok(buffer, s);

        while (token != NULL) {
            printf(" %s\n", token);
            token = strtok(NULL, s);
            
        }
        fprintf(fp2, "%s", buffer);
    }

    fclose(fp);
    fclose(fp2);

    return 0;

}