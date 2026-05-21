// debug_stringcmp.c
//
// This program takes in two strings as input and checks if they are the same
// Wrriten by Lucas Cheung, z5763342
// on 19-03-2026

#include <stdio.h>

#define MAX_SIZE 100

int main(void) {
    char str1[MAX_SIZE];
    char str2[MAX_SIZE];

    // Read input from user
    printf("Enter the first string: ");
	fgets(str1, MAX_SIZE, stdin);

    printf("Enter the second string: ");
	fgets(str2, MAX_SIZE, stdin);

    // Check if the strings are equal
	int is_equal = 0;
	for (int i = 0; i < MAX_SIZE && str1[i] != '\0' && str2[i] != '\0'; i++) {
		if (str1[i] == str2[i]) {
			is_equal = 1;
		} else {
			is_equal = 0;
		}
	}

	if (is_equal) {
		printf("The strings are equal!\n");
	} else {
		printf("The strings are not equal!\n");
	}

    return 0;
}
