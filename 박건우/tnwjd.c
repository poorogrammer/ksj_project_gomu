#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define BUFFER_SIZE 256
int main() {

    FILE* fp;
    char buffer[BUFFER_SIZE + 1];

    if ((fp = fopen("whitelist.txt", "a")) != NULL) {
        memset(buffer, 0, sizeof(buffer)); //buffer를 0으로 채운다.
        scanf("%s", buffer);

        fwrite(buffer, 1, strlen(buffer), fp);
        fclose(fp);
    }
}