// A simpler version of the famous Snake game!
//
// Written by Rory Golledge (z5308772) on 3/3/23
// Modified by Lucas Cheung (z5763342) on 19-3-2026
//

#include <stdio.h>

#define SIZE 8

enum land {
	NOT_VISITED,
	VISITED,
	SNAKE,
	APPLE
};

struct position {
	int row;
	int col;
};

void initialise_map(enum land map[SIZE][SIZE]);
void print_map(enum land map[SIZE][SIZE], struct position player_pos);
void move_snake(char command, enum land map[SIZE][SIZE], struct position *snake);

int main(void) {
	enum land map[SIZE][SIZE];
	initialise_map(map);
 
	printf("Welcome to Snake!\n");

	printf("Please enter apple location: ");
	struct position apple;
	scanf(" %d %d", &apple.row, &apple.col);
	map[apple.row][apple.col] = APPLE;

	printf("Please enter snake location: ");
	struct position snake;
	scanf(" %d %d", &snake.row, &snake.col);

	print_map(map, snake);

	char command;
	while ((apple.row != snake.row) || (apple.col != snake.col)) {
		scanf(" %c", &command);
		move_snake(command, map, &snake);
		print_map(map, snake);
	}

	printf("Chomp!\n");

	return 0;
}

void move_snake(char command, enum land map[SIZE][SIZE], struct position *snake) {
	if (command == 'u') {
		map[snake->row][snake->col] = VISITED;
		snake->row--;
	} else if (command == 'd') {
		map[snake->row][snake->col] = VISITED;
		snake->row++;
	} else if (command == 'l') {
		map[snake->row][snake->col] = VISITED;
		snake->col--;
	} else if (command == 'r') {
		map[snake->row][snake->col] = VISITED;
		snake->col++;
	}
}

/**
 * Initialises the given `map` such that all tiles are `NOT_VISITED`
 * 
 * Parameters:
 *	   map - The map to initialise
 * 
 * Returns:
 *	   Nothing
 */
void initialise_map(enum land map[SIZE][SIZE]) {
	for (int row = 0; row < SIZE; ++row) {
		for (int col = 0; col < SIZE; ++col) {
			map[row][col] = NOT_VISITED;
		}
	}
}

/**
 * Prints the given `map` such that all enum values are printed as nice
 * characters.
 * 
 * Parameters:
 *	   map - The map to print out
 * 
 * Returns:
 *	   Nothing
 */
void print_map(enum land map[SIZE][SIZE], struct position player_pos) {
	for (int row = 0; row < SIZE; ++row) {
		for (int col = 0; col < SIZE; ++col) {
			if (row == player_pos.row && col == player_pos.col) {
				printf("S ");
			} else if (map[row][col] == NOT_VISITED) {
				printf(". ");
			} else if (map[row][col] == VISITED) {
				printf("- ");
			} else if (map[row][col] == APPLE) {
				printf("A ");
			}
		}
		printf("\n");
	}
}

