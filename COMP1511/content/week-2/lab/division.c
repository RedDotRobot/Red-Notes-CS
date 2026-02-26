// Division
// division.c
//
// This program was written by Lucas Cheung (z5763342)
// on 26-02-2026
//
// Divide a number

#include <stdio.h>

int main(void) {

	double dividend;
	double divisor;
	printf("Enter the dividend: ");
	scanf("%lf", &dividend);
	printf("Enter the divisor: ");
	scanf("%lf", &divisor);
	if (divisor == 0) {
		printf("Don't be silly!\n");
	} else {
		printf("%.0lf divided by %.0lf\n", dividend, divisor);
		double quotient = dividend / divisor;
		printf("To the nearest whole number: %.0lf\n", quotient);
		printf("To 1 decimal place: %.1lf\n", quotient);
		printf("To 5 decimal places: %.5lf\n", quotient);
		printf("To 20 decimal places: %.20lf\n", quotient);


	}
	
	return 0;
}
