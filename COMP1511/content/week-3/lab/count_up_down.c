// Count Up/Down
// count_up_down.c
//
// This program was written by Lucas Cheung (z5763342)
// on 5-03-2026
//
// A program that reads one integer and prints all integers from 0 to n inclusive

#include <stdio.h>

int main(void) {
	int number;
	printf("Enter number: ");
	scanf("%d", &number);

	int i = 0;

	if (number > 0) {
		while (i <= number) {
			printf("%d\n", i);
			i++;
		}
	} else {
		while (i >= number) {
			printf("%d\n", i);
			i--;
		}
	}

	return 0;
}
