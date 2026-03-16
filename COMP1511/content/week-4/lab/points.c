// points.c
//
// Written 12-03-2026
// By Lucas Cheung (z5763342)
//
// Scan points into array of structs and print
//

#include <stdio.h>

#define MAX_POINTS 10

struct point {
    // TODO: fill this in so that the struct can hold an x and y position
    //
    // i.e. This struct should contain:
    //      the x-coordinate and y-coordinate (doubles).
	double xcoord;
	double ycoord;
};

// Prints a point out.
void print_point(int point_no, double x, double y);

int main(void) {
    // TODO: Declare an array of points of size MAX_POINTS

    printf("How many points in the shape? ");
    // TODO: scan in number of points in the shape
	int num_points;
	scanf("%d", &num_points);

	struct point points_list[num_points];

    printf("Enter points:\n");
    // TODO: scan in the details of each point into the array
	for (int i = 0; i < num_points; i++) {
		scanf("%lf %lf", &points_list[i].xcoord, &points_list[i].ycoord);
	}

    printf("\nShape Points:\n");
    // TODO: print all the points
	
	for (int i = 0; i < num_points; i++) {
		print_point(i+1, points_list[i].xcoord, points_list[i].ycoord);
	}

    return 0;
}

//  Prints a single point in the correct format.
//
// Parameters:
// - `point_no` -- The point number
// - `x`        -- The x-coordinate of the point
// - `y`        -- The y-coordinate of the point
//
// Returns: nothing.
void print_point(int point_no, double x, double y) {
    printf("%2d: x = %.3lf, y = %.3lf\n", point_no, x, y);
}

