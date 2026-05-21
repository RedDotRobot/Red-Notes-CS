// Word Square
// word_squre.c
//
// This program was written by Lucas Cheung (z5763342)
// on 19-03-2026
//
// Print a word out n amount of times

#include <stdio.h>

#define MAX_SIZE 100

int main(void) {

	char str[MAX_SIZE];

	// User input string
	printf("Input word: \n");
	fgets(str, MAX_SIZE, stdin);

	// Find length of string
	int length = 0;
	for (int i = 0; i < MAX_SIZE && str[i] != '\0'; i++) {
		length++;
	}

	// Print string number of times
	printf("Word square is:\n");
	for (int j = 1; j < length; j++) {
		printf("%s", str);
	}
	
	return 0;
}
