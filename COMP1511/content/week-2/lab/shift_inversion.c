// Shift Inversion
// shift_investion.c
//
// This program was written by Lucas Cheung (z5763342)
// on 26-02-2026
//
// Takes a character and applies transformations to it


#include <stdio.h>

int main(void) {
	char character;
	char invert_state;
	int shift;
	printf("Please enter a character: ");
	scanf(" %c", &character);
	printf("Would you like to invert the case? y or n: ");
	scanf(" %c", &invert_state);
	printf("By how much would you like to shift the character? ");
	scanf(" %d", &shift);
	
	// Flip between capital and lowercase
	if (invert_state == 'y') {
		if (character >= 97) {
			character -= 32;
		} else {
			character += 32;
		}
	}

	if (65 <= character <= 90) {
		// Set A to index 0
		character = character - 65;
		printf("%d\n", character);
		character = (character + shift) % 26;
		printf("%d\n", character);
		character = character + 65;
	} else {
		character = character - 97;
		character = (character + shift) % 26;
		character = character + 97;
	}
	printf("The character is %c!\n", character);

	return 0;
}
