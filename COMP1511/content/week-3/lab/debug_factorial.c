// debug_factorial.c
//
// Write a C program that takes a positive integer as input, calculates the
// factorial of that number and prints it out.
//
// This program was written by Lucas Cheung (z5763342)
// on 05-03-2026

#include <stdio.h>

int main (void) {
	int num = 0;
	int factorial = 0;

	printf("Enter a number: ");
	scanf("%d", &num);

	int counter = num-1;
	factorial = num;

	while (counter > 0) {
		factorial *= counter;
		counter--;
	}

	if (factorial == 0) {
		factorial = 1;
	}

	printf("The factorial of %d is %d\n", num, factorial);

	return 0;
}

