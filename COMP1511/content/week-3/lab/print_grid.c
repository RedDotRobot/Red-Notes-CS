// Print a Coordinate Grid
// print_grid.c
//
// This program was written by Lucas Cheung (z5763342)
// on 05-03-2026
//
// Print a coordinate grid of size n * n

#include <stdio.h>

int main(void) {
	int grid_size;
	printf("Enter size: ");
	scanf("%d", &grid_size);

	grid_size -= 1;
	
	int i = 0;
	int j = 0;
	
	while (i <= grid_size) {
		j = 0;
		while (j <= grid_size) {
			printf("(%d, %d)", i, j);
			j++;
		}
		printf("\n");
		i++;
	}


	return 0;
}
