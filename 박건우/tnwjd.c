#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define BUFFER_SIZE 256
int main() {

    FILE* fp;
    char buffer[BUFFER_SIZE + 1];

    if ((fp = fopen("whitelist.txt", "a")) != NULL) {
        memset(buffer, 0, sizeof(buffer)); //buffer�� 0���� ä���.
        scanf("%s", buffer);

        fwrite(buffer, 1, strlen(buffer), fp);
        fclose(fp);
    }
}