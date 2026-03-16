// Letters Between
// letters_between.c
//
// This program was written by Lucas Cheung (z5763342)
// on 05-02-2026
//
// Print the shortest distance between two letters

#include <stdio.h>

int main(void) {

	// Handle input
	char starting_letter;
	char target_letter;

	printf("Please enter starting letter: ");
	scanf(" %c", &starting_letter);

	printf("Please enter target letter: ");
	scanf(" %c", &target_letter);

	// Check if forward or backward is shorter
	char i = starting_letter; 
	int forward_count = 0;
	while (i != target_letter) {
		if (i == 'Z' || i == 'z') {
			i -= 25;
		} else {
			forward_count++;
			i++;
		}
	}

	i = starting_letter;
	int backward_count = 0;
	while (i != target_letter) {
		if (i == 'A' || i == 'a') {
			i += 25;
		} else {
			backward_count++;
			i--;
		}
	}
	
	// Print shorter root
	i = starting_letter;
	if (forward_count < backward_count) {
		while (i != target_letter) {
			if (i == 'Z' || i == 'z') {
				printf("%c", i);
				i -= 25;
			} else {
				printf("%c", i);
				i++;
			}
		}
	} else {
		while (i != target_letter) {
			if (i == 'A' || i == 'a') {
				printf("%c", i);
				i += 25;
			} else {
				printf("%c", i);
				i--;
			}
		}
	}

	printf("%c", target_letter);
	printf("\n");
	return 0;
}
