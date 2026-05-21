// Stellar Information Capture
// stella_information.c
//
// This program was written by Lucas Cheung (z5763342)
// on 02-04-2026
//
// This program simulates a star system in space

#include <stdio.h>
#include <string.h>

#define CONVERSION_CONSTANT 9.461e12
#define LIGHT_SPEED 299792.458

// TODO: TASK 1
struct star {
	char name[50];
	double distance;
	char spectral_type;
};

void print_star_information(struct star *star);
void input_star_information(struct star *star);
double time_travel(struct star *star);

int main() {

	struct star star;
	struct star *star_ptr = &star;

    input_star_information(star_ptr);
    print_star_information(star_ptr);

    return 0;
}

// Takes in the stars information
void input_star_information(struct star *star) {

	printf("Enter the star's name: ");
	fgets(star->name, 50, stdin);
	star->name[strcspn(star->name, "\n")] = '\0';

	printf("Enter the star's distance from Earth (in light-years): ");
	scanf("%lf", &star->distance);

	printf("Enter the star's spectral type: ");
	scanf(" %c", &star->spectral_type);
}

// Estimate travel time from Earth to the star based on star's distance
double time_travel(struct star *star) {
    double km_dist = CONVERSION_CONSTANT * star->distance;
	double travel_time = km_dist/LIGHT_SPEED;
    return travel_time;
}

// Prints the stars information
void print_star_information(struct star *star) {
	printf("\n");
	printf("Star's Information:\n");
	printf("Name: %s\n", star->name);
	printf("Distance: %lf light-years\n", star->distance);
	printf("Spectral Type: %c\n", star->spectral_type);
	printf("Estimated travel time from Earth: %.2lf seconds\n", time_travel(star));
}

