// Sawtooth
// sawtooth.c
//
// This program was written by Lucas Cheung (z5763342)
// on 01-02-2026
//
// Program to print a sawtooth pattern

#include <stdio.h>

int main(void) {

	int height;
	int length;
	printf("Please enter the height of the sawtooth: ");
	scanf("%d", &height);
	printf("Please enter the length of the sawtooth: ");
	scanf("%d", &length);

	int width = length/height;

	int i = 0;
	int j = 0;
	int k = 0;

	while (true) {
		if (i <= height) {
			printf("*");
			if (j <= length) {
				if (k <= length) {
					printf(" ");
					printf("%d\n", k);
				}
				k++;
			}
			j++;
		}
	}
	
	return 0;
}
