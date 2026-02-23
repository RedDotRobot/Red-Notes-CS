// Labour Day
// labour_day.c
//
// This program was written by Lucas Cheung (z5763342)
// on 23-02-2026
//
// Find the date of Labour Day for a given year

#include <stdio.h>

int main(void) {
	
	return 0;
}#include <stdio.h>

int main(void) {
	int year = 0;
	printf("Enter year: ");
	scanf("%d", &year);

	int days = year * 365.25;
	int leap_year_accounted = 10 - ( days % 7 );

	if (leap_year_accounted == 0) {
		leap_year_accounted = 1;
	} else if (leap_year_accounted > 7) {
		leap_year_accounted -=7;
	}
	printf("In %d, Labour Day is October %d\n", year, leap_year_accounted);

	return 0;
}
