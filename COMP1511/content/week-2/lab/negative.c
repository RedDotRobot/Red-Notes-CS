// Don't be so negative
// negative.c
//
// This program was written by Lucas Cheung (z5763342)
// on date
//
// Verify whether a number is positive, negative, or zero

#include <stdio.h>

int main(void) {
	int number = 0;
	scanf("%d", &number);
	if (number > 0) {
		printf("You have entered a positive number.\n");
	} else if (number < 0) {
		printf("Don't be so negative!\n");
	} else {
		printf("You have entered zero.\n");
	}
	return 0;
}
