// Ordering Three Integers Without If Statements
// order3_challenge1.c
//
// This program was written by Lucas Cheung (z5763342)
// on 26-02-2026
//
// Print 3 integers from smallest to largest
// Can only use printf and scanf

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	double num1;
	double num2;
	double num3;

	printf("Enter integer: ");
	scanf("%lf", &num1);
	printf("Enter integer: ");
	scanf("%lf", &num2);

	int min = ((num1 + num2)/2) - ((num1 - num2) * ((num1 - num2) >= 0) - (num1 - num2) * ((num1 - num2) < 0)/2);
	num3 = num2;
	num1 = num1 * (num1 == min) + num3 * (num1 != min);		// Lowest of the values
	num2 = num1 * (num1 != min) + num3 * (num1 == min);
	printf("%d\n", min);
	printf("%.0lf\n", num1);
	printf("%.0lf\n", num2);

	printf("Enter integer: ");
	scanf("%lf", &num3);

	return 0;
}
