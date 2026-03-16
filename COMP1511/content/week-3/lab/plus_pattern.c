// Plus Pattern
// plus_pattern.c
//
// This program was written by Lucas Cheung (z5763342)
// on 05-03-2026
//
// Prints a plus pattern

#include <stdio.h>

int main(void) {
	// Take input
	int n;
	printf("Enter size: ");
	scanf("%d", &n);

	for (int i = 0; i < n/2; i++) {
		for (int j = 0; j < n/2; j++) {
			printf(" ");
		}
		printf("*\n");
	}

	for (int k = 0; k < n; k++) {
		printf("*");
	}

	printf("\n");
	for (int l = 0; l < n/2; l++) {
		for (int m = 0; m < n/2; m++) {
			printf(" ");
		}
		printf("*\n");
	}
	return 0;
}
