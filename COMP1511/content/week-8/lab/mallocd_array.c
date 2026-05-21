// Working with malloc'd arrays
// mallocd_array.c
//
// This program was written by Lucas Cheung (z5763342)
// on 09-04-2026
//
// Scan and average an array


#include <stdio.h>
#include <stdlib.h>

//////////////// DO NOT CHANGE ANY OF THE CODE BELOW HERE //////////////////

int *scan_array(int size);
double calculate_average(int *array, int size);

int main (void) {

    int size;
    printf("Enter size: ");
    scanf(" %d", &size);
    if (size <= 0) {
        printf("Invalid Size\n");
        return 1;
    }
    printf("Enter %d integers:\n", size);
    int *array = scan_array(size);

    printf("The average of all values in the array is: %.2lf\n", 
           calculate_average(array, size));

    return 0;
}
//////////////// DO NOT CHANGE ANY OF THE CODE ABOVE HERE //////////////////

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE BELOW HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

// A function which scans in `size` integers and stores them into a 
// malloc'd array.
// returns: a pointer to the malloc'd array
int *scan_array(int size) {

    int *array = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }

    return array;
}

// Given an integer array and it's size, 
// returns the sum of all elements inside the array, divided by the size of the
// array.
double calculate_average(int *array, int size) {
    
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }

    return (sum/size);
}

////////////////////////////////////////////////////////////////////////////
///////////////////// ONLY WRITE CODE ABOVE HERE ///////////////////////////
////////////////////////////////////////////////////////////////////////////

