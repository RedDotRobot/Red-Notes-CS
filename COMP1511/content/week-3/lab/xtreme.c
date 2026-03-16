// Draw a fancy pattern
// xtreme.c
//
// This program was written by Lucas Cheung (z5763342)
// on 05-03-2026
//
// Doesn't work :/

#include <stdio.h>

int main(void) {
	// Scan n
	int n;
	printf("Enter size: ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || i == n - j - 1) {
				printf("*");
			} else if ( 1 == 2 ) {
				printf("*");
			} else {
				printf("_");
			}
		}
		printf("\n");
	}

	return 0;
}
