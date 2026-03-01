// Shift Inversion
// shift_investion.c
//
// This program was written by Lucas Cheung (z5763342)
// on 26-02-2026
//
// Takes a character and applies transformations to it
//
// Dunno what's happening but there's some weird quirks using the dcc compiler, works completely fine using gcc...


#include <stdio.h>

int main(void) {
	short character;
	short invert_state;
	int shift;
	printf("Please enter a character: ");
	scanf(" %hd", &character);
	printf("Would you like to invert the case? y or n: ");
	scanf(" %hd", &invert_state);
	printf("By how much would you like to shift the character? ");
	scanf(" %d", &shift);
	

	if (65 <= character && character <= 90) {
		// Set A to index 0
		character = character - 65;
		character = character + shift;
		character = character % 26;
		character = character + 65;
	} else {
		character = character - 97;
		character = character + shift;
		character = character % 26;
		character = character + 97;
	}

	// Flip between capital and lowercase
	if (invert_state == 'y') {
		if (character >= 97) {
			character -= 32;
		} else {
			character += 32;
		}
	}
	printf("The character is %c!\n", character);

	return 0;
}
