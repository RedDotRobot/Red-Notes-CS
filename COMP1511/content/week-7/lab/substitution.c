// Encrypting Text with a Substitution Cipher
// substitution.c
//
// This program was written by Lucas Cheung (z5763342)
// on 02-04-2026
//
// Read characters from a command line argument and produce an encrypted message

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 256

enum boolean {
	FALSE,
	TRUE
};


int is_upper(char letter);
int is_lower(char letter);

int main(int argc, char *argv[]) {

	// Store each character into an array map
	char mapping[26];
	for (int i = 0; i < 26; i++) {
		mapping[i] = argv[1][i];
	}

	printf("Enter text:\n");
	char string[MAX_LENGTH];
	while (fgets(string, MAX_LENGTH, stdin) != NULL) {
		for (int i = 0; string[i] != '\0'; i++) {

			char letter = string[i];
			int index;

			if (is_upper(letter)) {
				index = letter - 'A';
				letter = mapping[index];
				letter = toupper(letter);
			} else if (is_lower(letter)) {
				index = letter - 'a';
				letter = mapping[index];
			}

			printf("%c", letter);
		}
	}
	return 0;
}

int is_upper(char letter) {
	if (letter >= 'A' && letter <= 'Z') {
		return TRUE;
	} else {
		return FALSE;
	}
}

int is_lower(char letter) {
	if (letter >= 'a' && letter <= 'z') {
		return TRUE;
	} else {
		return FALSE;
	}
}
