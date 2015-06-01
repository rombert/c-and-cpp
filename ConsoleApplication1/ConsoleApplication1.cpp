#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("Hello, world\n");
	FILE* f = fopen("C:\\Windows\\System32\\drivers\\etc\\hosts", "r");
	if (!f) {
		printf("Error opening file\n");
		return -1;
	}
	return 0;
}

