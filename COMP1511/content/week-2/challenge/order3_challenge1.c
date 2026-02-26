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
	int num1;
	int num2;
	int num3;
	printf("Enter integer: ");
	scanf("%d", &num1);
	printf("Enter integer: ");
	scanf("%d", &num2);
	printf("Enter integer: ");
	scanf("%d", &num3);

	// Find min
	// Difference between two numbers to make the next line neater
	int min_diff = num1 - num2;			
	// The next line achieves an absolute value without using the math library
	// If the value is positive, (min_diff < 0) is 0 whereas if it is negative, min_diff >= 0 is zero and the number is multiplied by -1
	int min_posi_diff = min_diff * (min_diff >= 0) - min_diff * (min_diff < 0);	
	// The lowest value is found by averaging the numbers, and subtracting the half the absolute value of the numbers' difference 
	double first_min = (num1 + num2)/2 - min_posi_diff/2;

	// The process is repeated using the previously found low and the third number
	int second_min_diff = first_min - num3;
	int second_min_posi_diff = second_min_diff * (second_min_diff >= 0) - second_min_diff * (second_min_diff < 0);
	double second_min = (first_min + num3)/2 - second_min_posi_diff/2;

	printf("%.0lf\n", second_min);

	// Find max
	int max_diff = num1 - num2;
	int max_posi_diff = min_diff * (max_diff >= 0) - max_diff * (max_diff < 0);
	double first_max = (num1 + num2)/2 - max_posi_diff/2;

	int second_max_diff = first_max - num3;
	int second_max_posi_diff = second_max_diff * (second_max_diff >= 0) - second_min_diff * (second_min_diff < 0);
	// Identical process to finding the min, however half the absolute value of the numbers' difference is added
	double second_max = (first_max + num3)/2 + second_max_posi_diff/2;

	printf("%.0lf\n", second_max);

	// Find median
	// Can be found by adding all the numbers and subtracting the min and max
	double med = num1 + num2 + num3 - second_min - second_max;
	printf("The integers in order are: %.0lf %.0lf %.0lf\n", second_min, med, second_max);

	return 0;
}
