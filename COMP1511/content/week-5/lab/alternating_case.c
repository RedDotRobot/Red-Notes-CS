// Written by Lucas Cheung (z5763342)
// June, 2022

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1024

//////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////
void make_alternating(char string[MAX_STRING_LENGTH]);

int main (void) {
    //You don't need to understand this code to complete the exercise.

    //Scans in a string from the user.
    char buffer[MAX_STRING_LENGTH];
    fgets(buffer, MAX_STRING_LENGTH, stdin);

    // Runs your function
    make_alternating(buffer);

    // Prints resulting string.
    printf("%s", buffer);

    return 0;
}
//////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

// Modifies `string` so that the first letter is converted to lowercase, 
// and the case of each following letter alternates.
// i.e. in the resulting string: 
//      the first letter is lowercase, 
//      second letter is uppercase, 
//      third letter is lower case, 
//      etc.
//
// e.g.: "Hello" -> "hElLo"
void make_alternating(char string[MAX_STRING_LENGTH]) {

	int make_lower = 1;

	for (int i = 0; i < MAX_STRING_LENGTH && string[i] != '\0'; i++) {
		if (string[i] >= 'A' && string[i] <= 'Z' && make_lower == 1) {
			string[i] = string[i] + 32;
		} else if (string[i] >= 'a' && string[i] <= 'z' && make_lower == 0) {
			string[i] = string[i] - 32;
		}

		if ((string[i] >= 'A' && string[i] <= 'Z') ||
			(string[i] >= 'a' && string[i] <= 'z')
		) {
			if (make_lower) {
				make_lower = 0;
			} else {
				make_lower = 1;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE ABOVE HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

