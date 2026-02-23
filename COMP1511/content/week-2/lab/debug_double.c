// Debugging - Double
// debug_double.c
//
// This program was written by Lucas Cheung (z5763342)
//
// Double the inputted number

#include <stdio.h>

int main(void) {
    // Read in the number:
    int x;
    printf("Enter a number: ");
    scanf("%d", &x);

    // Doubled the value of x and assign it to y.
    int y;
    y = x + x;

    printf("Doubled: %d x 2 = %d\n", x, y);

    return 0;
}

