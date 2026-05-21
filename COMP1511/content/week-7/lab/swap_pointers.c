// Using pointers and a function to swap number values
// swap_pointers.c
//
// This program was written by Lucas Cheung (z5763342)
// on 02-04-2026
//
// Function that swaps two pointers


#include <stdio.h>

void swap_pointers(int *a, int *b);

// This is a simple main function which could be used
// to test your swap_pointers function.
// It will not be marked.
// Only your swap_pointers function will be marked.

int main(void) {
	int first = 1;
	int second = 2;
	
	swap_pointers(&first, &second);
	
	printf("%d, %d\n", first, second);
	return 0;
}

// swap the values in two integers, given as pointers
void swap_pointers(int *a, int *b) {
	int temp = 0;
	temp = *a;
	*a = *b;
	*b = temp;
}

