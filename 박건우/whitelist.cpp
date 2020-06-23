#include <stdio.h>
#include <stdlib.h> //exit함수사용을위함

#pragma warning(disable : 4996)

int main()
{
	char fname[20];
	char str[100];
	printf("%s\n", "열 화이트 리스트 파일을 입력해주세요");
	scanf("%s", fname);

	FILE* fpr = fopen(fname, "r");
	if (fpr == NULL)
	{
		printf("%s\n", "ERROR: 파일명을 다시 확인해주세요 ");
		exit(1);
	}

	while (fgets(str, 100, fpr)) {
		printf("%s", str);
	}
	fclose(fpr);
	return 0;
}

	
