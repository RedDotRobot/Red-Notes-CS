// =====================================================!================ //
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
#define MAX_WOMBAT_TUNNELS 10

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

enum boolean {
	FALSE,
	TRUE
};

// Structs
struct tile {
	enum entity entity;
	int wombat_id;
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
	struct tile board[ROWS][COLS],
	struct position *player_pos,
	int curr_score,
	int target_score
);
void print_board_line(void);
void print_board_footer(int curr_score, int target_score);

char setup_phase(struct tile board[ROWS][COLS], struct tile coin_board[ROWS][COLS], struct tile wombat_board[ROWS][COLS], struct position *player_pos, int *target_points);
void set_coin(struct tile board[ROWS][COLS], struct tile coin_board[ROWS][COLS], struct position player_pos);
void set_tree(struct tile board[ROWS][COLS], struct position player_pos);
void set_road(struct tile board[ROWS][COLS], struct position player_pos);
void set_car(struct tile board[ROWS][COLS], struct position player_pos);
void set_target(int *target_points);
void set_wombat(struct tile board[ROWS][COLS], struct position player_pos, int *wombat_count);

void gameplay_phase(struct tile board[ROWS][COLS], struct tile coin_board[ROWS][COLS],struct tile wombat_board[ROWS][COLS], struct position *player_pos, int *target_points, char mode, int driving);
int in_bounds(int row, int col);
int touching_player(struct position player_pos, int row, int col);
int is_shocked(struct tile board[ROWS][COLS], struct position *player_pos);
int is_dead(struct tile board[ROWS][COLS], struct position *player_pos);
int can_move(struct tile board[ROWS][COLS], int row, int col);
int move_player(struct tile board[ROWS][COLS], struct position *player_pos, char player_input, int *turns_taken, int *step_count, char mode);
void has_coin(struct tile board[ROWS][COLS], struct position *player_pos, int *points, int *coins);
int check_win_loss(struct tile board[ROWS][COLS], struct position *player_pos, int score, int target_points, int *playing, int turns_taken, int step_count, int coins);

void buffer_board(struct tile board[ROWS][COLS], struct tile (temp_board)[ROWS][COLS]);
void buffer_board_no_cars(struct tile board[ROWS][COLS], struct tile next_board[ROWS][COLS]);
void save_cars(struct tile board[ROWS][COLS], struct tile empty_board[ROWS][COLS]);
void move_cars(struct tile board[ROWS][COLS]);
void add_headlights(struct tile board[ROWS][COLS]);
void scroll_board(struct tile board[ROWS][COLS], struct tile coin_board[ROWS][COLS], struct position *player_pos, char command, int *step_count, int player_moved);

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

	struct tile coin_board[ROWS][COLS];
	initialise_board(coin_board);

	struct tile wombat_board[ROWS][COLS];
	initialise_board(wombat_board);

	struct position player_pos;
	int target_points = DEFAULT_POINT_TARGET;
	char mode = setup_phase(board, coin_board, wombat_board, &player_pos, &target_points);

	print_board(
		board,
		&player_pos,
		0,
		target_points
	);

	gameplay_phase(board, coin_board, wombat_board, &player_pos, &target_points, mode, 1);

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
	struct tile board[ROWS][COLS],
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
			} else if (board[row][col].entity == EMPTY) {
				printf("   ");
			} else if (board[row][col].entity == COIN) {
				printf(" c ");
			} else if (board[row][col].entity == TREE) {
				printf(" T ");
			} else if (board[row][col].entity == ROAD) {
				printf("___");
			} else if (board[row][col].entity == CAR_FACING_RIGHT) {
				printf("[_0");
			} else if (board[row][col].entity == CAR_FACING_LEFT) {
				printf("0_]");
			} else if (board[row][col].entity == HEADLIGHTS) {
				printf("###");
			} else if (board[row][col].entity == WOMBAT_TUNNEL) {
				printf("(%d)", board[row][col].wombat_id);
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
char setup_phase(struct tile board[ROWS][COLS], struct tile coin_board[ROWS][COLS], struct tile wombat_board[ROWS][COLS], struct position *player_pos, int *target_points) {


	printf("============== Setup Phase ==============\n");

	int valid_pos = 0;
	int row;
	int col;
	int wombat_count = 0;

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
	while (command != 'e' && command != 'd' && command != 's') {
		if (command == 'c') {
			set_coin(board, coin_board, *player_pos);
		} else if (command == 't') {
			set_tree(board, *player_pos);
		} else if (command == 'r') {
			set_road(board, *player_pos);
		} else if (command == 'v') {
			set_car(board, *player_pos);
		} else if (command == 'x') {
			set_target(target_points);
		} else if (command == 'w') {
			set_wombat(board, *player_pos, &wombat_count);
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
void set_coin(struct tile board[ROWS][COLS], struct tile coin_board[ROWS][COLS], struct position player_pos) {
	int row;
	int col;
	scanf(" %d %d", &row, &col);
	if (in_bounds(row, col)) {
		if (
			!touching_player(player_pos, row, col) &&
			board[row][col].entity == EMPTY
		) {
			board[row][col].entity = COIN;
			coin_board[row][col].entity = COIN;
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
void set_tree(struct tile board[ROWS][COLS], struct position player_pos) {
	int row;
	int col;
	scanf(" %d %d", &row, &col);
	if (in_bounds(row, col)) {
		if (
			!touching_player(player_pos, row, col) &&
			board[row][col].entity == EMPTY
		) {
			board[row][col].entity = TREE;
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
void set_road(struct tile board[ROWS][COLS], struct position player_pos) {
	int row;
	int col = 0;
	scanf(" %d", &row);
	if (in_bounds(row, 0)) {
		int deforesting = 0;
		int available = 1;
		if (player_pos.row == row) {
			available = 0;
		}
		for (int i = 0; i < COLS; i++) {
			if (
				touching_player(player_pos, row, col) &&
				board[row][i].entity != EMPTY &&
				board[row][i].entity != TREE
			) {
				available = 0;
			} else if (board[row][i].entity == TREE) {
				deforesting = 1;
			}
		}
		if (deforesting == 1 && available == 1) {
			printf("Deforesting.\n");
		}
		if (available == 1) {
			for (int i = 0; i < COLS; i++) {
				board[row][i].entity = ROAD;
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
void set_car(struct tile board[ROWS][COLS], struct position player_pos) {
	int row;
	int col;
	char direction;
	scanf(" %d %d %c", &row, &col, &direction);
	if (in_bounds(row, col)) {
		if (
			!touching_player(player_pos, row, col) &&
			(board[row][col].entity == ROAD ||
			board[row][col].entity == HEADLIGHTS)
		) {
			if (direction == 'r') {
				board[row][col].entity = CAR_FACING_RIGHT;
			} else if (direction == 'l') {
				board[row][col].entity = CAR_FACING_LEFT;
			}
		} else {
			printf("Invalid location: car must be on a road.\n");
		}
	} else {
		printf("Invalid location: position is not on map!\n");
	}
}

void set_wombat(struct tile board[ROWS][COLS], struct position player_pos, int *wombat_count) {
	char t;
	int row1, col1;
	int row2, col2;
	scanf(" %c %d %d %d %d", &t, &row1, &col1, &row2, &col2);

	if (*wombat_count >= MAX_WOMBAT_TUNNELS) {
		printf("Invalid feature: too many tunnels!\n");
		return;
	}

	if (in_bounds(row1, col1) && in_bounds(row2, col2) &&
		!(player_pos.row == row1 && player_pos.col == col1) &&
		!(player_pos.row == row2 && player_pos.col == col2) &&
		!(board[row1][col1].entity == WOMBAT_TUNNEL) &&
		!(board[row2][col2].entity == WOMBAT_TUNNEL) &&
		!(row1 == row2 && col1 == col2)
	) {
		board[row1][col1].entity = WOMBAT_TUNNEL;
		board[row1][col1].wombat_id = *wombat_count;
		board[row2][col2].entity = WOMBAT_TUNNEL;
		board[row2][col2].wombat_id = *wombat_count;
		(*wombat_count)++;
	} else {
		printf("Invalid location: wombat couldn't dig a tunnel here!\n");
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
void gameplay_phase(struct tile board[ROWS][COLS], struct tile coin_board[ROWS][COLS],struct tile wombat_board[ROWS][COLS], struct position *player_pos, int *target_points, char mode, int driving) {

	printf("============ Gameplay Phase =============\n");

	char command;
	int playing = 1;

	int turns_taken = 0;
	int step_count = 0;
	int coins = 0;
	int score = 0;

	while (playing == 1) {
		scanf(" %c", &command);
		int player_moved = 0;
		if (command == 'w' || command == 'a' || command == 's' || command == 'd') {
			player_moved = move_player(board, player_pos, command, &turns_taken, &step_count, mode);
			has_coin(board, player_pos, &score, &coins);
		} else if (command == 'r' || command == 'R') {
			turns_taken += 1;
		} else if (command == 'p') {
			print_game_statistics(turns_taken, step_count, coins, score);
		} else if (command == 'q') {
			playing = 0;
			printf("============= Quitting Game =============\n");
		}

		if (playing == 1 && command != 'q' && command != 'p') {
			if (mode == 'd' && !is_dead(board, player_pos)) {
				move_cars(board);
			} else if (mode == 's' && !is_dead(board, player_pos)) {
				move_cars(board);
				scroll_board(board, coin_board, player_pos, command, &step_count, player_moved);
				has_coin(board, player_pos, &score, &coins);
			}
			print_board(board, player_pos, score, *target_points);
			playing = check_win_loss(board, player_pos, score, *target_points, &playing, turns_taken, step_count, coins);
		}
	}
}

// Check if a tile is valid for a car to move onto (empty road or headlights)
// INPUT: pointer to board, row, col
// OUTPUT: int (1 for true, 0 otherwise)
int is_valid_car_dest(struct tile board[ROWS][COLS], int row, int col) {
	if (!in_bounds(row, col)) {
		return FALSE;
	} else if (board[row][col].entity == ROAD || board[row][col].entity == HEADLIGHTS) {
		return TRUE;
	} else {
		return FALSE;
	}
}

// Handle car movement on car turn
// INPUT: pointer to board
// OUTPUT: void
void move_cars(struct tile board[ROWS][COLS]) {
	struct tile next_board[ROWS][COLS];
	buffer_board_no_cars(board, next_board);

	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			if (board[row][col].entity == CAR_FACING_LEFT) {
				int front_col = col;
				while (front_col > 0 && board[row][front_col - 1].entity == CAR_FACING_LEFT) {
					front_col--;
				}
				int blocked = !is_valid_car_dest(board, row, front_col - 1);
				if (blocked) {
					next_board[row][col].entity = CAR_FACING_RIGHT;
				} else {
					next_board[row][col - 1].entity = CAR_FACING_LEFT;
				}
			} else if (board[row][col].entity == CAR_FACING_RIGHT) {
				int front_col = col;
				while (front_col < COLS - 1 && board[row][front_col + 1].entity == CAR_FACING_RIGHT) {
					front_col++;
				}
				int blocked = !is_valid_car_dest(board, row, front_col + 1);
				if (blocked) {
					next_board[row][col].entity = CAR_FACING_LEFT;
				} else {
					next_board[row][col + 1].entity = CAR_FACING_RIGHT;
				}
			}
		}
	}

	buffer_board(next_board, board);
}

void scroll_board(struct tile board[ROWS][COLS], struct tile coin_board[ROWS][COLS], struct position *player_pos, char command, int *step_count, int player_moved) {

	struct tile temp_row[COLS];
	struct tile coin_temp_row[COLS];

	if (command == 'w' && player_pos->row < 6) {
		if (player_pos->row == 0 && board[ROWS - 1][player_pos->col].entity == TREE) {
			return;
		}
		if (!player_moved) {
			*step_count += 1;
		}
		if (player_pos->row != 0 || player_moved) {
			player_pos->row++;
		}

		for (int col = 0; col < COLS; col++) {
			temp_row[col] = board[ROWS - 1][col];
			coin_temp_row[col] = coin_board[ROWS - 1][col];
		}
		for (int row = ROWS - 1; row > 0; row--) {
			for (int col = 0; col < COLS; col++) {
				board[row][col] = board[row - 1][col];
				coin_board[row][col] = coin_board[row - 1][col];
			}
		}
		for (int col = 0; col < COLS; col++) {
			board[0][col] = temp_row[col];
			if (coin_temp_row[col].entity == COIN) {
				board[0][col].entity = COIN;
			}
			coin_board[0][col] = coin_temp_row[col];
		}
	}
}

void buffer_board(struct tile board[ROWS][COLS], struct tile (temp_board)[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			temp_board[i][j].entity = board[i][j].entity;
		}
	}
}

void buffer_board_no_cars(struct tile board[ROWS][COLS], struct tile next_board[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j].entity != CAR_FACING_LEFT && board[i][j].entity != CAR_FACING_RIGHT && board[i][j].entity != HEADLIGHTS) {
				next_board[i][j].entity = board[i][j].entity;
			} else {
				next_board[i][j].entity = ROAD;
			}
		}
	}
}

void add_headlights(struct tile board[ROWS][COLS]) {
	
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j].entity == CAR_FACING_LEFT) {
				if (in_bounds(i, j-1) && board[i][j-1].entity == ROAD) {
					board[i][j-1].entity = HEADLIGHTS;
				}
			} else if (board[i][j].entity == CAR_FACING_RIGHT) {
				if (in_bounds(i, j+1) && board[i][j+1].entity == ROAD) {
					board[i][j+1].entity = HEADLIGHTS;
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
int check_win_loss(struct tile board[ROWS][COLS], struct position *player_pos, int score, int target_points, int *playing, int turns_taken, int step_count, int coins) {
	
	if (score >= target_points) {
		*playing = 0;
		print_game_statistics(turns_taken, step_count, coins, score);
		print_game_won();
	} else if (is_dead(board, player_pos)) {
		*playing = 0;
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
		return TRUE;
	} else {
		return FALSE;
	}
}


// Check if a given coord contains the player
// INPUT:
// 		pointer to struct player_pos
// 		int row
// 		int col
// OUTPUT:
// 		int (1 for true, 0 for false)
int touching_player(struct position player_pos, int row, int col) {
	if (player_pos.row == row && player_pos.col == col) {
		return TRUE;
	} else {
		return FALSE;
	}
}

// Check if a given coord contains a TREE
// INPUT:
// 		pointer to board
// 		int row
// 		int col
// OUTPUT:
// 		int (1 for true, 0 for false)
int touching_tree(struct tile board[ROWS][COLS], int row, int col) {
	if (board[row][col].entity == TREE) {
		return TRUE;
	} else {
		return FALSE;
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
		return TRUE;
	} else {
		return FALSE;
	}
}

// Check if player is dead
// INPUT:
// 		pointer to board
// 		pointer to struct player_pos
// OUTPUT:
// 		int (enum TRUE or FALSE)
int is_dead(struct tile board[ROWS][COLS], struct position *player_pos) {
	if (
		board[player_pos->row][player_pos->col].entity == CAR_FACING_LEFT ||
		board[player_pos->row][player_pos->col].entity == CAR_FACING_RIGHT
	) {
		return TRUE;
	} else {
		return FALSE;
	}
}

// Check if a tile is a valid moving position for the player
// INPUT:
// 		board
// 		int row
// 		int col
// OUTPUT:
// 		int (enum TRUE or FALSE)
int can_move(struct tile board[ROWS][COLS], int row, int col) {
	if (in_bounds(row, col)) {
		if (!touching_tree(board, row, col)) {
			return TRUE;
		} else {
			return FALSE;
		}
	} else {
		return FALSE;
	}
}

int find_matching_wombat_tunnel(
	struct tile board[ROWS][COLS],
	struct position *destination,
	int tunnel_id,
	int from_row,
	int from_col
) {
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			if (
				board[row][col].entity == WOMBAT_TUNNEL &&
				board[row][col].wombat_id == tunnel_id &&
				!(row == from_row && col == from_col)
			) {
				destination->row = row;
				destination->col = col;
				return TRUE;
			}
		}
	}
	return FALSE;
}

int is_wombat_tunnel(struct tile board[ROWS][COLS], int row, int col) {
	if (!in_bounds(row, col)) {
		return FALSE;
	}
	if (board[row][col].entity == WOMBAT_TUNNEL) {
		return TRUE;
	} else {
		return FALSE;
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
// 		int (1 if player moved, 0 otherwise)
int move_player(struct tile board[ROWS][COLS], struct position *player_pos, char player_input, int *turns_taken, int *step_count, char mode) {
	int target_row = player_pos->row;
	int target_col = player_pos->col;
	int delta_row = 0;
	int delta_col = 0;

	if (player_input == 'w') {
		delta_row = -1;
		if (mode == 's' && player_pos->row == 0 &&
			is_wombat_tunnel(board, ROWS - 1, player_pos->col)
		) {
			target_row = ROWS - 1;
		} else {
			target_row -= 1;
		}
	} else if (player_input == 's') {
		delta_row = 1;
		target_row += 1;
	} else if (player_input == 'a') {
		delta_col = -1;
		target_col -= 1;
	} else if (player_input == 'd') {
		delta_col = 1;
		target_col += 1;
	} else {
		return 0;
	}

	*turns_taken += 1;
	if (!can_move(board, target_row, target_col)) {
		return 0;
	}

	if (is_wombat_tunnel(board, target_row, target_col)) {

		int tunnel_id = board[target_row][target_col].wombat_id;
		struct position destination;

		if (find_matching_wombat_tunnel(
			board,
			&destination,
			tunnel_id,
			target_row,
			target_col
		)) {
			int exit_row = destination.row + delta_row;
			int exit_col = destination.col + delta_col;
			if (!in_bounds(exit_row, exit_col)) {
				return 0;
			}
			if (in_bounds(exit_row, exit_col) && touching_tree(board, exit_row, exit_col)) {
				return 0;
			}
			if (can_move(board, exit_row, exit_col)) {
				player_pos->row = exit_row;
				player_pos->col = exit_col;
			} else {
				player_pos->row = destination.row;
				player_pos->col = destination.col;
			}
		} else {
			player_pos->row = target_row;
			player_pos->col = target_col;
		}
	} else {
		player_pos->row = target_row;
		player_pos->col = target_col;
	}

	*step_count += 1;
	return 1;
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
void has_coin(struct tile board[ROWS][COLS], struct position *player_pos, int *points, int *coins) {
	if (board[player_pos->row][player_pos->col].entity == COIN) {
		board[player_pos->row][player_pos->col].entity = EMPTY;
		*points += 5;
		*coins += 1;
	}
}
