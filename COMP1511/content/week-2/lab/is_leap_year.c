// Leap Year
// is_leap_year.c
//
// This program was written by Lucas Cheung (z5763342)
// on 26-02-2026
//
// Check if a year is a leap year or not

#include <stdio.h>

int main(void) {
	int year;
	printf("Enter year: ");
	scanf("%d", &year);
	if ((year % 4 == 0) && (!(year % 100 == 0)||(year % 400 == 0))) {
		printf("%d is a leap year.\n", year);
	} else {
		printf("%d is not a leap year.\n", year);
	}
	return 0;
}
