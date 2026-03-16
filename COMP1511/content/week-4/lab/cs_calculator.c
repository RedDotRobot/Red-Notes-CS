// CS Calculator
// cs_calculator.c
//
// This program was written by Lucas Cheung (z5763342)
// on 12-03-2026
//
// Simple calculator

#include <stdio.h>

int main(void) {

	char operation;
	int num1;
	int num2;

	printf("Enter instruction: ");

	while (scanf(" %c", &operation) != -1) {

		if (operation == 's') {
			scanf("%d", &num1);
			printf("%d\n", num1*num1);

		} else if (operation == 'p') {
			scanf("%d %d", &num1, &num2);
			int power = 1;
			for (int i = num2; i != 0; i--) {
				power *= num1;
			}
			printf("%d\n", power);
		}

		printf("Enter instruction: ");
	}
	return 0;
}
