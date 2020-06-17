#include <stdio.h>
#include <stdlib.h>


int main() {

	system("netstat -an > whitelist02.txt");
	system("tasklist /svc > white03.txt");

	return 0;
}