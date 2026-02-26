// Print Letters, Given Their Numbers
// get_letter.c
//
// This program was written by YOUR-NAME-HERE (zXXXXXXX)
// on INSERT-DATE-HERE
//
// One line summary of what this exercise does.

#include <stdio.h>

int main(void) {

	char is_uppercase;
	int capital_offset;
	int index;

	printf("Uppercase: ");
	scanf("%c", &is_uppercase);
	printf("Index: ");
	scanf("%d", &index);
	if (is_uppercase == 'y') {
		capital_offset = 0;
	} else {
		capital_offset = 32;
	}

	index = 65 + index + capital_offset;
	printf("The letter is %c\n", index);
	return 0;
}
