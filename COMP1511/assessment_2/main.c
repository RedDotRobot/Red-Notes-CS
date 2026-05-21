// Assignment 2 26T1 COMP1511: CS Karting
// main.c
//
// Written by LUCAS CHEUNG, z5763342
// on 22-04-2026
//
// main file for cs_karting

#include <stdio.h>

#include "cs_karting.h"

int main(void) {
    print_welcome_banner();
    
    printf("Enter the name of your racing series: ");
    char series_name[MAX_SIZE];
    scan_name(series_name);
    struct series *my_series = create_series(series_name);

    command_loop(my_series);

    quit_series(my_series);
    printf("\nThank you for playing CS Karting!\n");
    return 0;
}
