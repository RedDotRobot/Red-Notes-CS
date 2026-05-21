// Planter
// planter.c
//
// This program was written by Lucas Cheung (z5763342)
// on 19-03-2026
//
// Planting game

#include <stdio.h>

#define GARDEN_ROWS 5
#define GARDEN_COLS 5
#define TRUE 1
#define FALSE 0

/*
Provided enum flowers
DO NOT MODIFY THIS ENUM
*/
enum flowers {
	EMPTY,
	DAISY,
	ROSE,
	TULIP
};

/*
Provided struct garden 
DO NOT MODIFY THIS STRUCT
*/
struct garden {
	enum flowers flower;
	int bloom_countdown;
	int is_gardener;
};

/*
provided function prototypes
DO NOT MODIFY THESE FUNCTION PROTOTYPES
*/
void print_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]);
int grow_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]);
int check_grown(struct garden garden[GARDEN_ROWS][GARDEN_COLS]);

int main(void) {

	printf("Welcome to the planter!\n");
	// TODO SECOND: IMPLEMENT THE MAIN FUNCTION

	struct garden garden[GARDEN_ROWS][GARDEN_COLS];

	for (int i = 0; i < GARDEN_ROWS; i++) {
		for (int j = 0; j < GARDEN_COLS; j++) {
			garden[i][j].flower = EMPTY;
			garden[i][j].is_gardener = 0;
			garden[i][j].bloom_countdown = 4;
		}
	}

	garden[0][0].is_gardener = 1;


	int flower_type;
	for (int i = 0; i < GARDEN_ROWS; i++) {

		grow_garden(garden);

		print_garden(garden);
		printf(
			"0. Nothing\n"
			"1. Daisy\n"
			"2. Rose\n"
			"3. Tulip\n"
			"Which flower would you like to plant in this row? "
		);

		scanf(" %d", &flower_type);

		for (int j = 0; j < GARDEN_COLS; j++) {
			if (flower_type == 0) {
				garden[i][j].flower = EMPTY;
			} else if (flower_type == 1) {
				garden[i][j].flower = DAISY;
			} else if (flower_type == 2) {
				garden[i][j].flower = ROSE;
			} else if (flower_type == 3) {
				garden[i][j].flower = TULIP;
			}
		}

		if (i != GARDEN_ROWS - 1) {
			garden[i][0].is_gardener = 0;
			garden[i+1][0].is_gardener = 1;
		} else {
			garden[i][0].is_gardener = 0;
		}
	}

	int finished = 0;
	while (!finished) {
		grow_garden(garden);
		print_garden(garden);
		finished = check_grown(garden);
		if (!finished) {
			printf("Waiting for flowers to bloom...\n");
		}
	}
	return 0;
}

int check_grown(struct garden garden[GARDEN_ROWS][GARDEN_COLS]) {
	int finished = 1;
	for (int i = 0; i < GARDEN_ROWS; i++) {
		for (int j = 0; j < GARDEN_COLS; j++) {
			if (garden[i][j].flower != EMPTY && garden[i][j].bloom_countdown > 0) {
				finished = 0;
			}
		}
	}
	return finished;
}

/*
	Decreases the bloom_countdown for all flowers in the garden
	Parameters:
		garden: a 2D array of struct garden
	Returns:
		int: returns 1 if a flower has grown, 0 otherwise
*/
int grow_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]) {
	// TODO FIRST: decrease bloom_countdown for all flowers in the garden
	for (int i = 0; i < GARDEN_ROWS; i++) {
		for (int j = 0; j < GARDEN_COLS; j++) {
			if (garden[i][j].flower != EMPTY) {
				garden[i][j].bloom_countdown--;
			}
		}
	}
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////
//////////////////// DO NOT MODIFY ANYTHING BELOW THIS LINE ////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
	Prints the garden to the terminal
	Parameters:
		garden: a 2D array of struct garden
	Returns:
		void
*/
void print_garden(struct garden garden[GARDEN_ROWS][GARDEN_COLS]) {
	printf("\n");
	for (int i = 0; i < GARDEN_ROWS; i++) {
		for (int j = 0; j < GARDEN_COLS; j++) {
			if (garden[i][j].is_gardener) {
				printf("# ");
			} else if (garden[i][j].flower == EMPTY) {
				printf(". ");
			} else if (garden[i][j].bloom_countdown > 0) {
				printf("%d ", garden[i][j].bloom_countdown);
			} else if (garden[i][j].flower == DAISY) {
				printf("D ");
			} else if (garden[i][j].flower == ROSE) {
				printf("R ");
			} else if (garden[i][j].flower == TULIP) {
				printf("T ");
			} else {
				printf(". ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

