// Palindrome
// palindrome.c
//
// This program was written by Lucas Cheung (z5763342)
// on 19-03-2026
//
// Print if palindromic


#include <stdio.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

int is_palindrome(char my_string[MAX_STRING_LENGTH]);

//////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////
int main (void) {
    // You don't need to understand this code to complete the exercise.

    // Scans in a string from the user.
    char my_string[MAX_STRING_LENGTH];
    fgets(my_string, MAX_STRING_LENGTH, stdin);

    // removing the newline character from the end of the string
    int length = strlen(my_string);
    if (length != 0 && my_string[length - 1] == '\n') {
        my_string[length - 1] = '\0';
    }
    
    // Runs your function and prints results
    if (is_palindrome(my_string)) {
        printf("%s is a palindrome!\n", my_string);
    } else {
        printf("%s is not a palindrome!\n", my_string);
    }
    
    return 0;
}
//////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

// Determines if the given `my_string` is a palindrome or not.
// Returns `1` if it is, otherwise `0`
int is_palindrome(char my_string[MAX_STRING_LENGTH]) {

	int palindrome = 1;
	for (int i = strlen(my_string) - 1; i >= 0; i--) {
		if (my_string[strlen(my_string) - 1 - i] != my_string[i]) {
			palindrome = 0;
		}
	}
	return palindrome;
}

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE ABOVE HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

