// String Match
// string_match.c
//
// This program was written by Lucas Cheung (z5763342)
// on 02-04-2026
//
// Count how many times a string is inputed

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 128

int main(void) {
	
	char search_term[MAX_LENGTH];
	printf("Enter the search term: ");
	fgets(search_term, MAX_LENGTH, stdin);

	printf("Enter the list of strings:\n");
	int total = 0;
	char string[MAX_LENGTH];
	while (fgets(string, MAX_LENGTH, stdin) != NULL) {
		if (strcmp(search_term, string) == 0) {
			total++;
		}
	}
	printf("There was %d occurrence(s) of the search term in the input.\n", total);

	return 0;
}
