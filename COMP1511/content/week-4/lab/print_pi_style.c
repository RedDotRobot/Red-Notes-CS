// print_pi_style.c
//
// Written by Lucas Cheung (z5763342)
// on 12-02-2026
//
// Prints the first n digits of pi, where n is specified 
// by the user

#include <stdio.h>

#define MAX_DIGITS 10

void print_pi_style(int num_digits);

int main(void) {
	// DO NOT EDIT CODE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf("How many digits of pi would you like to print? ");
	int digits;
	scanf("%d", &digits);
	print_pi_style(digits);

	return 0;
	// DO NOT EDIT CODE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void print_pi_style(int num_digits) {
	// DO NOT CHANGE THIS LINE
	int pi[MAX_DIGITS] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
	// TODO: Finish this function below
	printf("3.");
	for (int i = 1; i < num_digits; i++) {
		printf("%d", pi[i]);
	}
	printf("\n");
}

