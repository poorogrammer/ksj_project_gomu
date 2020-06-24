#include <stdio.h>
#include <windows.h>
#include <string.h> 

#pragma warning(disable : 4996) 
#define _CRT_SECURE_NO_WARNINGS    
# define MAX_STR_SIZE 65535



int main() {

    system("tasklist /fo csv > C:/whitelist01.txt");

    FILE* fp = fopen("C:/whitelist01.txt", "r");
    FILE* fp2 = fopen("C:/whiltlist0101.txt", "w");

    char s[4] = "\n\",";
    char s2[2] = "\"";
    char buffer[255];
    char* token;
    char* pStr;


    while (fgets(buffer, sizeof(buffer), fp)) {


        token = strtok(buffer, s);

        while (token != NULL) {
            printf(" %s\n", token);
            token = strtok(NULL, s);

        }
        char* input = strchr(buffer, '\"');
        fprintf(fp2, "%s\n", input+1);

    }


    fclose(fp);
    fclose(fp2);

    return 0;

}
