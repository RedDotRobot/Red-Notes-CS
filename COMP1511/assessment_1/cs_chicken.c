// ====================================================================== //
// ====================================================================== //
// 																		  //
// 																		  //
//  ▄▄▄   ▄▄▄▄  ▄▄▄▄ ▄▄  ▄▄▄▄ ▄▄  ▄▄ ▄▄   ▄▄ ▄▄▄▄▄ ▄▄  ▄▄ ▄▄▄▄▄▄     ▄██  //
// ██▀██ ███▄▄ ███▄▄ ██ ██ ▄▄ ███▄██ ██▀▄▀██ ██▄▄  ███▄██   ██        ██  //
// ██▀██ ▄▄██▀ ▄▄██▀ ██ ▀███▀ ██ ▀██ ██   ██ ██▄▄▄ ██ ▀██   ██  ▄▄▄▄▄ ██  //
// 																		  //
//       ▄▄                                                               //
//       ██    ▀▀        ▄▄                                               //
// ▄████ ████▄ ██  ▄████ ██ ▄█▀ ▄█▀█▄ ████▄   ▄████  ▀▀█▄ ███▄███▄ ▄█▀█▄  //
// ██    ██ ██ ██  ██    ████   ██▄█▀ ██ ██   ██ ██ ▄█▀██ ██ ██ ██ ██▄█▀  //
// ▀████ ██ ██ ██▄ ▀████ ██ ▀█▄ ▀█▄▄▄ ██ ██   ▀████ ▀█▄██ ██ ██ ██ ▀█▄▄▄  //
//  											 ██						  //
//										       ▀▀▀						  //
//																		  //
// ====================================================================== //
// ====================================================================== //

// This program was written by LUCAS CHEUNG (z5763342)
// on 13-03-2026

// Packages
#include <stdio.h>

// Constants
#define COLS 10
#define ROWS 10
#define INITIAL_POINTS 0
#define DEFAULT_POINT_TARGET 20

// Enums
enum entity {
	EMPTY,
	COIN,
	TREE,
	ROAD,
	CAR_FACING_RIGHT,
	CAR_FACING_LEFT,
	HEADLIGHTS,
	KANGAROO,
	WOMBAT_TUNNEL,
	BABY_CHICKEN
};

enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// Structs
struct tile {
	enum entity entity;
};

struct position {
	int row;
	int col;
};

//	░█▀█░█▀▄░█▀█░▀█▀░█▀█░█░█░█▀█░█▀▀░█▀▀  //
//	░█▀▀░█▀▄░█░█░░█░░█░█░░█░░█▀▀░█▀▀░▀▀█  //
//	░▀░░░▀░▀░▀▀▀░░▀░░▀▀▀░░▀░░▀░░░▀▀▀░▀▀▀  //

void print_welcome(void);
void initialise_board(struct tile board[ROWS][COLS]);
void print_board(
	struct tile (board)[ROWS][COLS],
	struct position *player_pos,
	int curr_score,
	int target_score
);
void print_board_line(void);
void print_board_footer(int curr_score, int target_score);

char setup_phase(struct tile (board)[ROWS][COLS], struct position *player_pos, int *target_points);
void set_coin(struct tile (board)[ROWS][COLS], struct position *player_pos);
void set_tree(struct tile (board)[ROWS][COLS], struct position *player_pos);
void set_road(struct tile (board)[ROWS][COLS], struct position *player_pos);
void set_car(struct tile (board)[ROWS][COLS], struct position *player_pos);
void set_target(int *target_points);

void gameplay_phase(struct tile (board)[ROWS][COLS], struct position *player_pos, int *target_points, char mode, int driving);
int in_bounds(int row, int col);
int touching_player(struct position *player_pos, int row, int col);
int is_shocked(struct tile board[ROWS][COLS], struct position *player_pos);
int is_dead(struct tile (board)[ROWS][COLS], struct position *player_pos);
int can_move(struct tile (board)[ROWS][COLS], int row, int col);
void move_player(struct tile (board)[ROWS][COLS], struct position *player_pos, char player_input, int *turns_taken, int *step_count);
void has_coin(struct tile (board)[ROWS][COLS], struct position *player_pos, int *points, int *coins);
int check_win_loss(struct tile (board)[ROWS][COLS], struct position *player_pos, int score, int target_points, int *playing, int turns_taken, int step_count, int coins);

void buffer_board(struct tile (board)[ROWS][COLS], struct tile (temp_board)[ROWS][COLS]);
void move_cars(struct tile (board)[ROWS][COLS]);
void add_headlights(struct tile (board)[ROWS][COLS]);

void print_game_statistics(
    int turns_taken, 
    int step_count, 
    int coins, 
    int score
);

void print_game_won(void);
void print_game_lost(void);


//	░█▄█░█▀█░▀█▀░█▀█  //
//	░█░█░█▀█░░█░░█░█  //
//	░▀░▀░▀░▀░▀▀▀░▀░▀  //

int main(void) {

	print_welcome();

	struct tile board[ROWS][COLS];
	initialise_board(board);

	struct position player_pos;
	int target_points = DEFAULT_POINT_TARGET;
	char mode = setup_phase(board, &player_pos, &target_points);

	print_board(
		board,
		&player_pos,
		0, 
		target_points
    );

	gameplay_phase(board, &player_pos, &target_points, mode, 1);

	return 0;
}

//	░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀  //
//	░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█  //
//	░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀  //

//	░█░█░█▀▀░█░░░█▀█░█▀▀░█▀▄░░░█▀▀░█░█░█▀█░█▀▀░▀█▀░▀█▀░█▀█░█▀█░█▀▀  //
//	░█▀█░█▀▀░█░░░█▀▀░█▀▀░█▀▄░░░█▀▀░█░█░█░█░█░░░░█░░░█░░█░█░█░█░▀▀█  //
//	░▀░▀░▀▀▀░▀▀▀░▀░░░▀▀▀░▀░▀░░░▀░░░▀▀▀░▀░▀░▀▀▀░░▀░░▀▀▀░▀▀▀░▀░▀░▀▀▀  //

// Print the welcome banner
// INPUT: void
// OUTPUT: void
void print_welcome(void) {
	printf(
		"_________________________________________   \n"
		"   \\\\                               \\\\  \n"
		"   (o>   !!    Welcome to    !!     (o>     \n"
		"\\\\_//)         CS CHICKEN        \\\\_//) \n"
		" \\_/_)                            \\_/_)   \n"
		"  _|_                              _|_      \n"
		"_________________________________________   \n\n"
	);
}

// Initialise board by setting all tiles to EMPTY
// INPUT: void
// OUTPUT: void
void initialise_board(struct tile board[ROWS][COLS]) {
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			board[row][col].entity = EMPTY;
		}
	}
}

// Print the board
// INPUT:
// 		pointer to board
// 		int player_row
// 		int player_col
// 		int current score
// 		int target score
// 		int is_shocked
// OUTPUT:
// 		void
void print_board(
	struct tile (board)[ROWS][COLS],
	struct position *player_pos,
	int curr_score,
	int target_score
) {
	add_headlights(board);
	print_board_line();
	printf("|          C S   C H I C K E N          |\n");
	print_board_line();

	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			printf("|");
			if (row == player_pos->row && col == player_pos->col) {
				if (is_shocked(board, player_pos)) {
					printf("0_0");
				} else {
					printf("^_^");
				}
			} else if ((board)[row][col].entity == EMPTY) {
				printf("   ");
			} else if ((board)[row][col].entity == COIN) {
				printf(" c ");
			} else if ((board)[row][col].entity == TREE) {
				printf(" T ");
			} else if ((board)[row][col].entity == ROAD) {
				printf("___");
			} else if ((board)[row][col].entity == CAR_FACING_RIGHT) {
				printf("[_0");
			} else if ((board)[row][col].entity == CAR_FACING_LEFT) {
				printf("0_]");
			} else if ((board)[row][col].entity == HEADLIGHTS) {
				printf("###");
			} else {
				printf("   ");
			}
		}
		printf("|\n");
		print_board_line();
	}

	print_board_footer(curr_score, target_score);
	printf("\n");
}

// Helper function for print_board()
// INPUT: void
// OUTPUT: void
void print_board_footer(int curr_score, int target_score) {
    printf("Score: %-3d                     ", curr_score);
    printf("Target: %-2d", target_score);
}

// Helper function for print_board(). 
// INPUT: void
// OUTPUT: void
void print_board_line(void) {
    printf("+");
    for (int col = 0; col < COLS; col++) {
        printf("---+");
    }
    printf("\n");
}
// Print the game statistics
// INPUT:
// 		int turns_taken
// 		int step_count
// 		int coins
// 		int score
// OUTPUT:
// 		void
void print_game_statistics(
    int turns_taken, 
    int step_count, 
    int coins, 
    int score
) {
    printf( 
        "============ Game Statistics ============\n"
        "          Turns taken: %d\n"
        "           Step count: %d\n"
        "      Coins Collected: %d\n"
        "                Score: %d\n",
        turns_taken, step_count, coins, score
    );
}

// Print banner when game is won
// INPUT: void
// OUTPUT: void
void print_game_won(void) {
    printf(
        "_________________________________________   \n"
        "       Penny the Chicken is happy!          \n"
        "   \\\\                               \\\\  \n"
        "   (o>   !!    Thank  you    !!     (o>     \n"
        "\\\\_//)        for playing!       \\\\_//) \n"
        " \\_/_)                            \\_/_)   \n"
        "  _|_                              _|_      \n"
        "_________________________________________   \n\n"
    );
}

// Print banner when game is lost
// INPUT: void
// OUTPUT: void
void print_game_lost(void) {
    printf(
        "_________________________________________   \n"
        "   \\\\                               \\\\  \n"
        "   (x>    !!      Game      !!      (x>     \n"
        "\\\\_//)             Over          \\\\_//) \n"
        " \\_/_)                            \\_/_)   \n"
        "  _|_                              _|_      \n"
        "_________________________________________   \n\n"
    );
}


//	░█▀▀░█▀▀░▀█▀░█░█░█▀█░░░█▀█░█░█░█▀█░█▀▀░█▀▀	//
//	░▀▀█░█▀▀░░█░░█░█░█▀▀░░░█▀▀░█▀█░█▀█░▀▀█░█▀▀	//
//	░▀▀▀░▀▀▀░░▀░░▀▀▀░▀░░░░░▀░░░▀░▀░▀░▀░▀▀▀░▀▀▀	//

// Main function to handle the setup phase, called at main
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// 		pointer to int target_points
// OUTPUT:
// 		char
char setup_phase(struct tile (board)[ROWS][COLS], struct position *player_pos, int *target_points) {


	printf("============== Setup Phase ==============\n");

	int valid_pos = 0;
	int row;
	int col;

	while (valid_pos == 0) {
		printf("Enter the starting position: ");
		scanf("%d %d", &row, &col);

		// Validate user input
		if (in_bounds(row, col)) {
			player_pos->row = row;
			player_pos->col = col;
			valid_pos = 1;
		} else {
			printf("Penny the Chicken cannot start here!\n");
		}
	}

	print_board(
		board,
		player_pos,
		INITIAL_POINTS, 
		DEFAULT_POINT_TARGET
    );

	char command;
	// Setup commands
	printf("Enter setup commands: \n");
	scanf(" %c", &command);
	while (command != 'e' && command != 'd') {
		if (command == 'c') {
			set_coin(board, player_pos);
		} else if (command == 't') {
			set_tree(board, player_pos);
		} else if (command == 'r') {
			set_road(board, player_pos);
		} else if (command == 'v') {
			set_car(board, player_pos);
		} else if (command == 'x') {
			set_target(target_points);
		}
		scanf(" %c", &command);
	}
	return command;
}

// Prompt user to create COIN feature, modify board if allowed
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// OUTPUT:
// 		void
void set_coin(struct tile (board)[ROWS][COLS], struct position *player_pos) {
	int row;
	int col;
	scanf(" %d %d", &row, &col);
	if (in_bounds(row, col)) {
		if (
			!touching_player(player_pos, row, col) &&
			(board)[row][col].entity == EMPTY
		) {
			(board)[row][col].entity = COIN;
		} else {
			printf("Invalid location: tile is occupied!\n");
		}
	} else {
		printf("Invalid location: position is not on map!\n");
	}
}

// Prompt user to create TREE feature, modify board if allowed
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// OUTPUT:
// 		void
void set_tree(struct tile (board)[ROWS][COLS], struct position *player_pos) {
	int row;
	int col;
	scanf(" %d %d", &row, &col);
	if (in_bounds(row, col)) {
		if (
			!touching_player(player_pos, row, col) &&
			(board)[row][col].entity == EMPTY
		) {
			(board)[row][col].entity = TREE;
		} else {
			printf("Invalid location: tile is occupied!\n");
		}
	} else {
		printf("Invalid location: position is not on map!\n");
	}
}

// Prompt user to create ROAD feature, modify board if allowed
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// OUTPUT:
// 		void
void set_road(struct tile (board)[ROWS][COLS], struct position *player_pos) {
	int row;
	int col = 0;
	scanf(" %d", &row);
	if (in_bounds(row, 0)) {
		int deforesting = 0;
		int available = 1;
		for (int i = 0; i < COLS; i++) {
			if (
				touching_player(player_pos, row, col) &&
				(board)[row][i].entity != EMPTY &&
				(board)[row][i].entity != TREE
			) {
				available = 0;
			} else if ((board)[row][i].entity == TREE) {
				deforesting = 1;
			}
		}
		if (deforesting == 1) {
			printf("Deforesting.\n");
		}
		if (available == 1) {
			for (int i = 0; i < COLS; i++) {
				(board)[row][i].entity = ROAD;
			}
		} else {
			printf("Invalid location: road cannot be built.\n");
		}
	} else {
		printf("Invalid location: position is not on map!\n");
	}
}

// Prompt user to create CAR_FACING_LEFT/RIGHT feature, modify board if allowed
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// OUTPUT:
// 		void
void set_car(struct tile (board)[ROWS][COLS], struct position *player_pos) {
	int row;
	int col;
	char direction;
	scanf(" %d %d %c", &row, &col, &direction);
	if (in_bounds(row, col)) {
		if (
			!touching_player(player_pos, row, col) &&
			((board)[row][col].entity == ROAD ||
			(board)[row][col].entity == HEADLIGHTS)
		) {
			if (direction == 'r') {
				(board)[row][col].entity = CAR_FACING_RIGHT;
				(board)[row][col+1].entity = HEADLIGHTS;
			} else if (direction == 'l') {
				(board)[row][col].entity = CAR_FACING_LEFT;
				(board)[row][col-1].entity = HEADLIGHTS;
			}
		} else {
			printf("Invalid location: car must be on a road.\n");
		}
	} else {
		printf("Invalid location: position is not on map!\n");
	}
}

// Prompt user to set target points
// INPUT:
// 		pointer to int target_points
// OUTPUT:
// 		void
void set_target(int *target_points) {
	int target;
	scanf(" %d", &target);
	if (target < 1 || target > 99) {
		printf("Target must be between 1 and 99 inclusive.\n");
	} else {
		*target_points = target;
	}
}

//  ░█▀▀░█▀█░█▄█░█▀▀░█▀█░█░░░█▀█░█░█░░░█▀█░█░█░█▀█░█▀▀░█▀▀  //
//  ░█░█░█▀█░█░█░█▀▀░█▀▀░█░░░█▀█░░█░░░░█▀▀░█▀█░█▀█░▀▀█░█▀▀  //
//  ░▀▀▀░▀░▀░▀░▀░▀▀▀░▀░░░▀▀▀░▀░▀░░▀░░░░▀░░░▀░▀░▀░▀░▀▀▀░▀▀▀  //

// Main function to handle the gameplay phase, called at main
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// 		pointer to int target_points
// OUTPUT:
// 		void
void gameplay_phase(struct tile (board)[ROWS][COLS], struct position *player_pos, int *target_points, char mode, int driving) {

	printf("============ Gameplay Phase =============\n");

	char command;
	int playing = 1;

	int turns_taken = 0;
	int step_count = 0;
	int coins = 0;
	int score = 0;

	while (playing == 1) {
		scanf(" %c", &command);
		if (command == 'w' || command == 'a' || command == 's' || command == 'd') {
			move_player(board, player_pos, command, &turns_taken, &step_count);
			has_coin(board, player_pos, &score, &coins);
			playing = check_win_loss(board, player_pos, score, *target_points, &playing, turns_taken, step_count, coins);
		} else if (command == 'r' || command == 'R') {
			turns_taken += 1;
		} else if (command == 'p') {
			print_game_statistics(turns_taken, step_count, coins, score);
		} else if (command == 'q') {
			playing = 0;
			printf("============= Quitting Game =============\n");
		}

		if (playing == 1 && command != 'q' && command != 'p') {
			if (mode == 'd') {
				move_cars(board);
			}
			print_board(board, player_pos, score, *target_points);
			playing = check_win_loss(board, player_pos, score, *target_points, &playing, turns_taken, step_count, coins);
		}
	}
}

// Handle car movement on car turn
// INPUT: pointer to board
// OUTPUT: void
void move_cars(struct tile (board)[ROWS][COLS]) {
	struct tile temp_board[ROWS][COLS];
	buffer_board(board, temp_board);
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if ((board)[i][j].entity == CAR_FACING_LEFT) {
				if (j == 0 || (board)[i][j-1].entity == CAR_FACING_RIGHT) {
					temp_board[i][j].entity = CAR_FACING_RIGHT;
				} else {
					temp_board[i][j].entity = ROAD;
					temp_board[i][j-1].entity = CAR_FACING_LEFT;
				}
			} else if ((board)[i][j].entity == CAR_FACING_RIGHT) {
				if (j == COLS - 1 || (board)[i][j+1].entity == CAR_FACING_LEFT) {
					temp_board[i][j].entity = CAR_FACING_LEFT;
				} else {
					temp_board[i][j].entity = ROAD;
					temp_board[i][j+1].entity = CAR_FACING_RIGHT;
				}
			}
		}
	}
	buffer_board(temp_board, board);
}

void buffer_board(struct tile (board)[ROWS][COLS], struct tile (temp_board)[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			temp_board[i][j].entity = (board)[i][j].entity;
		}
	}
}

void add_headlights(struct tile (board)[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if ((board)[i][j].entity == CAR_FACING_LEFT) {
				if (in_bounds(i, j-1) && (board)[i][j-1].entity == ROAD) {
				(board)[i][j-1].entity = HEADLIGHTS;
				}
			} else if ((board)[i][j].entity == CAR_FACING_RIGHT) {
				if (in_bounds(i, j+1) && (board)[i][j+1].entity == ROAD) {
				(board)[i][j+1].entity = HEADLIGHTS;
				}
			} 
		}
	}
}

// Check if the player has won or lost the game
// INPUT:
// 		pointer to board
// 		pointer to player_pos
// 		int score
// 		int target_points
// 		int turns_taken
// 		int step_count
// 		int coins
// OUTPUT:
// 		int (0 for game end, 1 for still playing)
int check_win_loss(struct tile (board)[ROWS][COLS], struct position *player_pos, int score, int target_points, int *playing, int turns_taken, int step_count, int coins) {
	
	if (score >= target_points) {
		*playing = 0;
		print_board(board, player_pos, score, target_points);
		print_game_statistics(turns_taken, step_count, coins, score);
		print_game_won();
	} else if (is_dead(board, player_pos)) {
		*playing = 0;
		print_board(board, player_pos, score, target_points);
		print_game_statistics(turns_taken, step_count, coins, score);
		print_game_lost();
	} else {
		*playing = 1;
	}
	return *playing;
}

// Check if a given coord is within the bounds of the board
// INPUT:
// 		int row
// 		int col
// OUTPUT:
// 		int (1 for true, 0 for false)
int in_bounds(int row, int col) {
	if ((0 <= row) && (row < ROWS) && (0 <= col) && (col < COLS)) {
		return 1;
	} else {
		return 0;
	}
}


// Check if a given coord contains the player
// INPUT:
// 		pointer to struct player_pos
// 		int row
// 		int col
// OUTPUT:
// 		int (1 for true, 0 for false)
int touching_player(struct position *player_pos, int row, int col) {
	if (player_pos->row == row && player_pos->col == col) {
		return 1;
	} else {
		return 0;
	}
}

// Check if a given coord contains a TREE
// INPUT:
// 		pointer to board
// 		int row
// 		int col
// OUTPUT:
// 		int (1 for true, 0 for false)
int touching_tree(struct tile (board)[ROWS][COLS], int row, int col) {
	if ((board)[row][col].entity == TREE) {
		return 1;
	} else {
		return 0;
	}
}

// Check if player is in HEADLIGHTS or a CAR
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// OUTPUT:
// 		int (1 for true, 0 for false)
int is_shocked(struct tile board[ROWS][COLS], struct position *player_pos) {
	if (board[player_pos->row][player_pos->col].entity == HEADLIGHTS ||
		board[player_pos->row][player_pos->col].entity == CAR_FACING_LEFT ||
		board[player_pos->row][player_pos->col].entity == CAR_FACING_RIGHT
	) {
		return 1;
	} else {
		return 0;
	}
}

// Check if player is dead
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// OUTPUT:
// 		int (1 for true, 0 for false)
int is_dead(struct tile (board)[ROWS][COLS], struct position *player_pos) {
	if (
		(board)[player_pos->row][player_pos->col].entity == CAR_FACING_LEFT ||
		(board)[player_pos->row][player_pos->col].entity == CAR_FACING_RIGHT
	) {
		return 1;
	} else {
		return 0;
	}
}

// Check if a tile is a valid moving position for the player
// INPUT:
// 		pointer to board
// 		int row
// 		int col
// OUTPUT:
// 		int (1 for true, 0 for false)
int can_move(struct tile (board)[ROWS][COLS], int row, int col) {
	if (in_bounds(row, col)) {
		if (!touching_tree(board, row, col)) {
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

// Handle player movements when given a command
// Increment turns_taken and step_count for statistics
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// 		char player_input
// 		pointer to int turns_taken
// 		pointer to int step_count
// OUTPUT:
// 		void
void move_player(struct tile (board)[ROWS][COLS], struct position *player_pos, char player_input, int *turns_taken, int *step_count) {
	if (player_input == 'w') {
		if (can_move(board, player_pos->row - 1, player_pos->col)) {
			player_pos->row -= 1;
			*step_count += 1;
		}
		*turns_taken += 1;
	} else if (player_input == 's') {
		if (can_move(board, player_pos->row + 1, player_pos->col)) {
			player_pos->row += 1;
			*step_count += 1;
		}
		*turns_taken += 1;
	} else if (player_input == 'a') {
		if (can_move(board, player_pos->row, player_pos->col - 1)) {
			player_pos->col -=1;
			*step_count += 1;
		}
		*turns_taken += 1;
	} else if (player_input == 'd') {
		if (can_move(board, player_pos->row, player_pos->col + 1)) {
			player_pos->col += 1;
			*step_count += 1;
		}
		*turns_taken += 1;
	}
}

// Check if a tile has a coin
// Collect the coin and increment score and coins for statistics
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// 		pointer to int points
// 		pointer to int coins
// OUTPUT:
// 		void
void has_coin(struct tile (board)[ROWS][COLS], struct position *player_pos, int *points, int *coins) {
	if ((board)[player_pos->row][player_pos->col].entity == COIN) {
		(board)[player_pos->row][player_pos->col].entity = EMPTY;
		*points += 5;
		*coins += 1;
	}
}
