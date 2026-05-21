// Summation
// summation.c
//
// This program was written by Lucas Cheung (z5763342)
// on 02-04-2026
//
// Sum integers taken as command line arguments

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int sum = 0;
	for (int arg = 0; arg < argc; arg++) {
		sum += atoi(argv[arg]);
	}
	printf("Sum: %d\n", sum);
	return 0;
}
