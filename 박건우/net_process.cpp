#include <stdio.h>
#include <windows.h>
#include <string.h> 

#pragma warning(disable : 4996) 
#define _CRT_SECURE_NO_WARNINGS    
# define MAX_STR_SIZE 65535



int main() {

    system("tasklist /fo csv > C:/whitelist01.txt");

    FILE* fp = fopen("C:/whitelist01.txt", "r");
    FILE* fp2 = fopen("C:/whiltlist0101.txt", "r");

    char s[5] = "\n\",\"";
    char buffer[255];
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
