// Perfect Number
// perfect_number.c
//
// This program was written by Lucas Cheung (z5763342)
// on 05-02-2026
//
// Determine if an inputted integer is a perfect number

#include <stdio.h>

int main(void) {
	
	int n = 0;
	printf("Enter a number: ");
	while (scanf("%d", &n) == 1) {
		if (n == 1) {
			printf("The sum of 1's factors is:  = 0\n");
			printf("No, %d is not a perfect number.\n", n);
			printf("Enter a number: ");
		} else {
			printf("The sum of %d's factors is: 1", n);
			int sum = 1;
			for (int i = 2; i < n; i++) {
				if ((n % i) == 0) {
					printf(" + %d", i);
					sum += i;
				}
			}
			printf(" = %d\n", sum);

			if (sum == n) {
				printf("Yes, %d is a perfect number!\n", n);
			} else {
				printf("No, %d is not a perfect number.\n", n);
			}
			printf("Enter a number: ");
		}
	}

	printf("\n");
	return 0;
}

