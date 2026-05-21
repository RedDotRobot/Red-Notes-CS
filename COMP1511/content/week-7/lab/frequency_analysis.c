// Frequency Analysis
// frequency_analysis.c
//
// This program was written by Lucas Cheung (z5763342)
// on 02-04-2026
//
// Print the frequency of letters in an input

#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 1028

int main(void) {
	char string[MAX_LENGTH];
	int letter_counts[26] = {0};
	double total_letters = 0;

	while (fgets(string, MAX_LENGTH, stdin) != NULL) {
		for (int i = 0; string[i] != '\0' && string[i] != '\n'; i++) {
			char c = string[i];
			
			if (c >= 'A' && c <= 'Z') {
				c += 32;
			}
			
			if (c >= 'a' && c <= 'z') {
				letter_counts[c - 'a']++;
				total_letters++;
			}
		}
	}
	
	for (char i = 'a'; i <= 'z'; i++) {
		double count = letter_counts[i - 'a'];
		double freq = count / total_letters;
		printf("'%c' %.6lf %.0lf\n", i, freq, count);
	}
	
	return 0;
}
