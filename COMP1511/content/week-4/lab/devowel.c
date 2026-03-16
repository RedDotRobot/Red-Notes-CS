// Devowelling Text
// devowel.c
//
// This program was written by Lucas Cheung (z5763342)
// on 12-03-2026
//
// Program that outputs a string without the vowels

#include <stdint.h>
#include <stdio.h>

#define SIZE 100

int is_vowel(char letter);

int main(void) {
	char text[SIZE];

	while (fgets(text, SIZE, stdin) != NULL) {
		for (int i = 0; text[i] != '\0'; i++) {
			if (!is_vowel(text[i])) {
				printf("%c", text[i]);
			}
		}
	}
	return 0;
}

int is_vowel(char letter) {
	if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u') {
		return 1;
	} else {
		return 0;
	}
}
