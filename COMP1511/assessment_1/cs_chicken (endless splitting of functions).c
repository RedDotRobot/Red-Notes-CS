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

// Packages
#include <stdio.h>

// Constants
#define COLS 10
#define ROWS 10
#define INITIAL_POINTS 0
#define DEFAULT_POINT_TARGET 20
#define MAX_WOMBAT_TUNNELS 10
#define MAX_BABY_CHICKENS 4

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
    int coin;
    int roo_jump_length;
    enum entity roo_base_entity;
    int baby_chicken;
};

struct position {
    int row;
    int col;
};

//	░█▀█░█▀▄░█▀█░▀█▀░█▀█░█░█░█▀█░█▀▀░█▀▀  //
//	░█▀▀░█▀▄░█░█░░█░░█░█░░█░░█▀▀░█▀▀░▀▀█  //
//	░▀░░░▀░▀░▀▀▀░░▀░░▀▀▀░░▀░░▀░░░▀▀▀░▀▀▀  //

// Helpers
void print_welcome(void);
void initialise_board(struct tile board[ROWS][COLS]);
void print_board(
    struct tile board[ROWS][COLS],
    struct position *player,
    int curr_score,
    int target_score,
    int baby_chicken_count
);
void print_board_line(void);
void print_board_footer(int curr_score, int target_score);
void print_game_statistics(
    int turns_taken, 
    int step_count, 
    int coins, 
    int score
);
void print_game_won(void);
void print_game_lost(void);

// Setup phase
char setup_phase(struct tile board[ROWS][COLS], struct position *player, int *target_points, int *baby_chicken_total);
void set_coin(struct tile board[ROWS][COLS], struct position player);
void set_tree(struct tile board[ROWS][COLS], struct position player);
void set_road(struct tile board[ROWS][COLS], struct position player);
void set_car(struct tile board[ROWS][COLS], struct position player);
void set_wombat(struct tile board[ROWS][COLS], struct position player, int *wombat_count);
void set_kangaroo(struct tile board[ROWS][COLS], struct position player);
void set_baby_chicken(int *baby_chicken_total);
void set_target(int *target_points);

// Gameplay phase
void gameplay_phase(struct tile board[ROWS][COLS], struct position *player, int *target_points, char mode, int baby_chicken_total);
int move_player(
    struct tile board[ROWS][COLS],
    struct position *player,
    char player_input,
    int *turns_taken,
    int *step_count,
    char mode,
    int *jump_distance,
    int *baby_chicken_count,
    int baby_chicken_total
);
void move_kangaroo(struct tile board[ROWS][COLS], struct position *player, struct position target);
void move_baby_chickens(struct tile board[ROWS][COLS]);
void has_coin(struct tile board[ROWS][COLS], struct position *player, int *points, int *coins);
void buffer_board(struct tile board[ROWS][COLS], struct tile (temp_board)[ROWS][COLS]);
void buffer_board_no_cars(struct tile board[ROWS][COLS], struct tile next_board[ROWS][COLS]);
int is_valid_car_dest(struct tile board[ROWS][COLS], int row, int col);
void move_cars(struct tile board[ROWS][COLS]);
void add_headlights(struct tile board[ROWS][COLS]);
void scroll_board(struct tile board[ROWS][COLS], struct position *player, char command, int *step_count, int player_moved, int jump_distance);
int find_matching_wombat_tunnel(
    struct tile board[ROWS][COLS],
    struct position *destination,
    int tunnel_id,
    struct position target
);
void reset_baby_chickens(struct tile board[ROWS][COLS], int *baby_chicken_count, int baby_chicken_total);

// Game checks
int check_can_move(struct tile board[ROWS][COLS], struct position position);
int check_in_bounds(struct position position);
int check_touching_player(struct position player, struct position position);
int check_is_empty(struct tile board[ROWS][COLS], struct position position);
int check_is_shocked(struct tile board[ROWS][COLS], struct position player);
int check_is_dead(struct tile board[ROWS][COLS], struct position player);
int check_is_kangaroo(struct tile board[ROWS][COLS], struct position position);
int check_is_baby_chicken(struct tile board[ROWS][COLS], struct position position);
int check_is_car(struct tile board[ROWS][COLS], struct position position);
int check_win_loss(struct tile board[ROWS][COLS], struct position *player, int score, int target_points, int *playing, int turns_taken, int step_count, int coins);
int check_baby_chicken_connected(struct tile board[ROWS][COLS], struct position chicken, struct position player);



//	░█▄█░█▀█░▀█▀░█▀█  //
//	░█░█░█▀█░░█░░█░█  //
//	░▀░▀░▀░▀░▀▀▀░▀░▀  //

int main(void) {

    print_welcome();

    struct tile board[ROWS][COLS];
    initialise_board(board);

    struct position player;

    int target_points = DEFAULT_POINT_TARGET;
    int baby_chicken_total = 0;

    char mode = setup_phase(
        board,
        &player,
        &target_points,
        &baby_chicken_total
    );

    print_board(
        board,
        &player,
        0,
        target_points,
        baby_chicken_total
    );

    gameplay_phase(board, &player, &target_points, mode, baby_chicken_total);

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
            board[row][col].coin = 0;
            board[row][col].wombat_id = -1;
            board[row][col].roo_jump_length = 0;
            board[row][col].baby_chicken = 0;
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
// 		int check_is_shocked
// OUTPUT:
// 		void
void print_board(
    struct tile board[ROWS][COLS],
    struct position *player,
    int curr_score,
    int target_score,
    int baby_chicken_count
) {
    add_headlights(board);
    print_board_line();
    printf("|          C S   C H I C K E N          |\n");
    print_board_line();
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            struct position baby_chicken = {row, col};
            printf("|");
            if (
                row == player->row && col == player->col &&
                !(board[row][col].entity == KANGAROO)
            ) {
                if (check_is_shocked(board, *player)) {
                    printf("0_0");
                } else if (baby_chicken_count > 0) {
                    printf("^%d^", baby_chicken_count);
                } else {
                    printf("^_^");
                }
            } else if (
                board[row][col].baby_chicken > 0 &&
                check_baby_chicken_connected(board, baby_chicken, *player) &&
                !(board[row][col].entity == KANGAROO)
            ) {
                if (check_is_shocked(board, baby_chicken)) {
                    printf("o.o");
                } else {
                    printf("^.^");
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
            } else if (
                board[row][col].entity == KANGAROO &&
                row == player->row && col == player->col
            ) {
                printf("_B^");
            } else if (board[row][col].entity == KANGAROO) {
                printf("_b^");
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
// 		pointer to struct player
// 		pointer to int target_points
// OUTPUT:
// 		char
char setup_phase(
    struct tile board[ROWS][COLS],
    struct position *player,
    int *target_points,
    int *baby_chicken_total
) {
    printf("============== Setup Phase ==============\n");

    int valid_pos = 0;
    int wombat_count = 0;
    struct position validation;
    while (valid_pos == 0) {
        printf("Enter the starting position: ");
        scanf("%d %d", &validation.row, &validation.col);
        // Validate user input
        if (check_in_bounds(validation)) {
            player->row = validation.row;
            player->col = validation.col;
            valid_pos = 1;
        } else {
            printf("Penny the Chicken cannot start here!\n");
        }
    }
    print_board(
        board,
        player,
        INITIAL_POINTS, 
        DEFAULT_POINT_TARGET,
        0
    );
    char command;
    // Setup commands
    printf("Enter setup commands: \n");
    scanf(" %c", &command);
    while (command != 'e' && command != 'd' && command != 's') {
        if (command == 'c') {
            set_coin(board, *player);
        } else if (command == 't') {
            set_tree(board, *player);
        } else if (command == 'r') {
            set_road(board, *player);
        } else if (command == 'v') {
            set_car(board, *player);
        } else if (command == 'w') {
            set_wombat(board, *player, &wombat_count);
        } else if (command == 'k') {
            set_kangaroo(board, *player);
        } else if (command == 'b') {
            set_baby_chicken(baby_chicken_total);
        } else if (command == 'x') {
            set_target(target_points);
        }
        scanf(" %c", &command);
    }
    return command;
}

// Prompt user to create COIN feature, modify board if allowed
// INPUT:
// 		board
// 		pointer to player position
// OUTPUT:
// 		void
void set_coin(struct tile board[ROWS][COLS], struct position player) {
    struct position coin;
    scanf(" %d %d", &coin.row, &coin.col);
    if (check_in_bounds(coin)) {
        if (
            !check_touching_player(player, coin) &&
            board[coin.row][coin.col].entity == EMPTY
        ) {
            board[coin.row][coin.col].entity = COIN;
            board[coin.row][coin.col].coin = 1;
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
// 		pointer to struct player
// OUTPUT:
// 		void
void set_tree(struct tile board[ROWS][COLS], struct position player) {
    struct position tree;
    scanf(" %d %d", &tree.row, &tree.col);
    if (check_in_bounds(tree)) {
        if (
            !check_touching_player(player, tree) &&
            board[tree.row][tree.col].entity == EMPTY
        ) {
            board[tree.row][tree.col].entity = TREE;
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
// 		pointer to struct player
// OUTPUT:
// 		void
void set_road(struct tile board[ROWS][COLS], struct position player) {
    struct position road;
    road.col = 0;
    scanf(" %d", &road.row);
    if (check_in_bounds(road)) {
        int deforesting = 0;
        int available = 1;
        if (player.row == road.row) {
            available = 0;
        }
        for (int col = 0; col < COLS; col++) {
            if (
                check_touching_player(player, road) &&
                board[road.row][col].entity != EMPTY &&
                board[road.row][col].entity != TREE
            ) {
                available = 0;
            } else if (board[road.row][col].entity == TREE) {
                deforesting = 1;
            }
        }
        if (deforesting == 1 && available == 1) {
            printf("Deforesting.\n");
        }
        if (available == 1) {
            for (int col = 0; col < COLS; col++) {
                board[road.row][col].entity = ROAD;
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
// 		pointer to struct player
// OUTPUT:
// 		void
void set_car(struct tile board[ROWS][COLS], struct position player) {
    struct position car;
    char direction;
    scanf(" %d %d %c", &car.row, &car.col, &direction);
    if (check_in_bounds(car)) {
        if (
            !check_touching_player(player, car) &&
            (board[car.row][car.col].entity == ROAD ||
            board[car.row][car.col].entity == HEADLIGHTS)
        ) {
            if (direction == 'r') {
                board[car.row][car.col].entity = CAR_FACING_RIGHT;
            } else if (direction == 'l') {
                board[car.row][car.col].entity = CAR_FACING_LEFT;
            }
        } else {
            printf("Invalid location: car must be on a road.\n");
        }
    } else {
        printf("Invalid location: position is not on map!\n");
    }
}

void set_wombat(
    struct tile board[ROWS][COLS],
    struct position player,
    int *wombat_count
) {
    char the_letter_t;
    struct position tunnel_one;
    struct position tunnel_two;
    scanf(
        " %c %d %d %d %d",
        &the_letter_t,
        &tunnel_one.row,
        &tunnel_one.col,
        &tunnel_two.row,
        &tunnel_two.col
    );

    if (*wombat_count >= MAX_WOMBAT_TUNNELS) {
        printf("Invalid feature: too many tunnels!\n");
        return;
    }

    if (check_in_bounds(tunnel_one) && check_in_bounds(tunnel_two) &&
        !(check_touching_player(player, tunnel_one)) &&
        !(check_touching_player(player, tunnel_two)) &&
        !(board[tunnel_one.row][tunnel_one.col].entity == WOMBAT_TUNNEL) &&
        !(board[tunnel_two.row][tunnel_two.col].entity == WOMBAT_TUNNEL) &&
        !(tunnel_one.row == tunnel_two.row && tunnel_one.col == tunnel_two.col)
    ) {
        board[tunnel_one.row][tunnel_one.col].entity = WOMBAT_TUNNEL;
        board[tunnel_one.row][tunnel_one.col].wombat_id = *wombat_count;
        board[tunnel_two.row][tunnel_two.col].entity = WOMBAT_TUNNEL;
        board[tunnel_two.row][tunnel_two.col].wombat_id = *wombat_count;
        (*wombat_count)++;
    } else {
        printf("Invalid location: wombat couldn't dig a tunnel here!\n");
    }
}

void set_kangaroo(struct tile board[ROWS][COLS], struct position player) {

    struct position kangaroo;
    scanf(" %d %d", &kangaroo.row, &kangaroo.col);
    if (
        check_in_bounds(kangaroo) &&
        !check_touching_player(player, kangaroo) &&
        check_is_empty(board, kangaroo)
    ) {
        board[kangaroo.row][kangaroo.col].entity = KANGAROO;
        board[kangaroo.row][kangaroo.col].roo_jump_length = 2;
        board[kangaroo.row][kangaroo.col].roo_base_entity = EMPTY;
    } else {
        printf("Invalid location: kangaroos can't be here!\n");
    }

}

void set_baby_chicken(int *baby_chicken_total) {
    if (*baby_chicken_total < MAX_BABY_CHICKENS) {
        *baby_chicken_total += 1;
    } else {
        printf("Invalid command: ");
        printf("there can be at most 4 baby chickens at a time.\n");
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
// 		board
// 		pointer player position
// 		pointer to int target_points
// OUTPUT:
// 		void
void gameplay_phase(
    struct tile board[ROWS][COLS],
    struct position *player,
    int *target_points,
    char mode,
    int baby_chicken_total
) {
    printf("============ Gameplay Phase =============\n");
    char command;
    int playing = 1;
    int baby_chicken_count = baby_chicken_total;
    int turns_taken = 0;
    int step_count = 0;
    int coins = 0;
    int score = 0;
    int jump_distance;
    while (playing == 1) {
        scanf(" %c", &command);
        int player_moved = 0;
        if (
            command == 'w' || command == 'a' ||
            command == 's' || command == 'd'
        ) {
            player_moved = move_player(
                board, player,
                command,
                &turns_taken,
                &step_count,
                mode,
                &jump_distance,
                &baby_chicken_count,
                baby_chicken_total
            );
            has_coin(board, player, &score, &coins);
        } else if (command == 'r' || command == 'R') {
            turns_taken += 1;
        } else if (command == 'p') {
            print_game_statistics(turns_taken, step_count, coins, score);
        } else if (command == 'q') {
            playing = 0;
            printf("============= Quitting Game =============\n");
        }
        if (playing == 1 && command != 'q' && command != 'p') {
            if (mode == 'd' && !check_is_dead(board, *player)) {
                move_cars(board);
            } else if (mode == 's' && !check_is_dead(board, *player)) {
                move_cars(board);
                if (!check_is_dead(board, *player)) {
                    scroll_board(
                        board, player,
                        command,
                        &step_count,
                        player_moved,
                        jump_distance
                    );
                    has_coin(board, player, &score, &coins);
                }
            }
            print_board(
                board, player,
                score,
                *target_points,
                baby_chicken_count
            );
            playing = check_win_loss(
                board, player,
                score,
                *target_points,
                &playing,
                turns_taken,
                step_count,
                coins
            );
        }
    }
}

// Check if a tile is valid for a car to move onto (empty road or headlights)
// INPUT: pointer to board, row, col
// OUTPUT: int (1 for true, 0 otherwise)
int is_valid_car_dest(struct tile board[ROWS][COLS], int row, int col) {
    struct position destination;
    destination.row = row;
    destination.col = col;

    if (!check_in_bounds(destination)) {
        return FALSE;
    } else if (
        board[row][col].entity == ROAD ||
        board[row][col].entity == HEADLIGHTS
    ) {
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

                while (
                    front_col > 0
                    && board[row][front_col - 1].entity == CAR_FACING_LEFT
                ) {
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
                while (
                    front_col < COLS - 1 &&
                    board[row][front_col + 1].entity == CAR_FACING_RIGHT
                ) {
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

void scroll_board(
    struct tile board[ROWS][COLS],
    struct position *player,
    char command,
    int *step_count,
    int player_moved,
    int jump_distance
) {
    struct tile temp_row[COLS];

    if (command == 'w' && player->row < 6) {
        if (player->row == 0 && board[ROWS - 1][player->col].entity == TREE) {
            return;
        }

        if (!player_moved) {
            *step_count += 1;
        }
        if (player->row != 0 || player_moved) {
            player->row += jump_distance;
        }

        for (int scroll = 0; scroll < jump_distance; scroll++) {
            // Store bottom row into temp
            for (int col = 0; col < COLS; col++) {
                temp_row[col] = board[ROWS - 1][col];
            }
            for (int row = ROWS - 1; row > 0; row--) {
                for (int col = 0; col < COLS; col++) {
                    board[row][col] = board[row - 1][col];
                }
            }
            for (int col = 0; col < COLS; col++) {
                board[0][col] = temp_row[col];
                if (temp_row[col].coin == 1) {
                    board[0][col].entity = COIN;
                }
            }
        }
    }
}

void buffer_board(
    struct tile board[ROWS][COLS],
    struct tile (temp_board)[ROWS][COLS]
) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            temp_board[i][j].entity = board[i][j].entity;
        }
    }
}

void buffer_board_no_cars(
    struct tile board[ROWS][COLS],
    struct tile next_board[ROWS][COLS]
) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].entity != CAR_FACING_LEFT &&
                board[i][j].entity != CAR_FACING_RIGHT &&
                board[i][j].entity != HEADLIGHTS
            ) {
                next_board[i][j].entity = board[i][j].entity;
            } else {
                next_board[i][j].entity = ROAD;
            }
        }
    }
}

// Called at print board to add headlights to the board
void add_headlights(struct tile board[ROWS][COLS]) {

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            
            // Initialise headlights position out of bounds
            struct position headlights;
            headlights.row = -1;
            headlights.col = -1;

            if (board[row][col].entity == CAR_FACING_LEFT) {
                headlights.row = row;
                headlights.col = col - 1;
            } else if (board[row][col].entity == CAR_FACING_RIGHT) {
                headlights.row = row;
                headlights.col = col + 1;
            }

            if (
                check_in_bounds(headlights) &&
                board[headlights.row][headlights.col].entity == ROAD
            ) {
                board[headlights.row][headlights.col].entity = HEADLIGHTS;
            }
        }
    }
}

// Check if the player has won or lost the game
// INPUT:
// 		pointer to board
// 		pointer to player
// 		int score
// 		int target_points
// 		int turns_taken
// 		int step_count
// 		int coins
// OUTPUT:
// 		int (0 for game end, 1 for still playing)
int check_win_loss(
    struct tile board[ROWS][COLS],
    struct position *player,
    int score,
    int target_points,
    int *playing,
    int turns_taken,
    int step_count,
    int coins
) {
    if (score >= target_points) {
        *playing = 0;
        print_game_statistics(turns_taken, step_count, coins, score);
        print_game_won();
    } else if (check_is_dead(board, *player)) {
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
int check_in_bounds(struct position position) {
    if ((0 <= position.row) && (position.row < ROWS) &&
        (0 <= position.col) && (position.col < COLS)) {
        return TRUE;
    } else {
        return FALSE;
    }
}


// Check if a given coord contains the player
// INPUT:
// 		pointer to struct player
// 		int row
// 		int col
// OUTPUT:
// 		int (1 for true, 0 for false)
int check_touching_player(struct position player, struct position position) {
    if (player.row == position.row && player.col == position.col) {
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
int check_touching_tree(
    struct tile board[ROWS][COLS],
    struct position position
) {
    if (board[position.row][position.col].entity == TREE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int check_is_empty(struct tile board[ROWS][COLS], struct position position) {
    if (board[position.row][position.col].entity == EMPTY) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Check if player is in HEADLIGHTS or a CAR
// INPUT:
// 		pointer to board
// 		pointer to struct player
// OUTPUT:
// 		int (1 for true, 0 for false)
int check_is_shocked(struct tile board[ROWS][COLS], struct position player) {
    if (board[player.row][player.col].entity == HEADLIGHTS ||
        board[player.row][player.col].entity == CAR_FACING_LEFT ||
        board[player.row][player.col].entity == CAR_FACING_RIGHT
    ) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Check if player is dead
// INPUT:
// 		board
// 		player position
// OUTPUT:
// 		int (enum TRUE or FALSE)
int check_is_dead(struct tile board[ROWS][COLS], struct position player) {
    if (
        board[player.row][player.col].entity == CAR_FACING_LEFT ||
        board[player.row][player.col].entity == CAR_FACING_RIGHT
    ) {
        return TRUE;
    }

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (
                board[row][col].baby_chicken > 0 &&
                (board[row][col].entity == CAR_FACING_LEFT ||
                 board[row][col].entity == CAR_FACING_RIGHT)
            ) {
                return TRUE;
            }
        }
    }

    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (
                !(row == player.row && col == player.col) &&
                board[row][col].baby_chicken > 0
            ) {
                struct position chicken = {row, col};
                if (!check_baby_chicken_connected(board, chicken, player)) {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}

int check_is_baby_chicken(
    struct tile board[ROWS][COLS],
    struct position position
) {
    if (board[position.row][position.col].baby_chicken > 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

// Check if a tile is a valid moving position for the player
// INPUT:
// 		board
// 		position 
// OUTPUT:
// 		int (enum TRUE or FALSE)
int check_can_move(struct tile board[ROWS][COLS], struct position position) {
    if (
        check_in_bounds(position) &&
        !check_touching_tree(board, position) &&
        !check_is_baby_chicken(board, position)
    ) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int find_matching_wombat_tunnel(
    struct tile board[ROWS][COLS],
    struct position *destination,
    int tunnel_id,
    struct position target
) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (
                board[row][col].entity == WOMBAT_TUNNEL &&
                board[row][col].wombat_id == tunnel_id &&
                !(row == target.row && col == target.col)
            ) {
                destination->row = row;
                destination->col = col;
                return TRUE;
            }
        }
    }
    return FALSE;
}

int check_is_wombat_tunnel(
    struct tile board[ROWS][COLS],
    struct position position
) {
    if (
        check_in_bounds(position) && 
        board[position.row][position.col].entity == WOMBAT_TUNNEL
    ) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int check_is_kangaroo(struct tile board[ROWS][COLS], struct position position) {
    if (board[position.row][position.col].entity == KANGAROO) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int check_is_car(struct tile board[ROWS][COLS], struct position position) {
    if (
        board[position.row][position.col].entity == CAR_FACING_LEFT ||
        board[position.row][position.col].entity == CAR_FACING_RIGHT
    ) {
        return TRUE;
    } else {
        return FALSE;
    }
}

int check_baby_chicken_connected(
    struct tile board[ROWS][COLS],
    struct position chicken,
    struct position player
) {

    struct position neighours[4] = {
        {chicken.row - 1, chicken.col},
        {chicken.row + 1, chicken.col},
        {chicken.row, chicken.col - 1},
        {chicken.row, chicken.col + 1}
    };

    for (int pos = 0; pos < 4; pos++) {
        if (
            check_in_bounds(neighours[pos]) &&
            check_touching_player(player, neighours[pos])
        ) {
            return TRUE;
        }

        if (
            check_in_bounds(neighours[pos]) &&
            board[neighours[pos].row][neighours[pos].col].baby_chicken > 0
        ) {
            return TRUE;
        }
    }
    return FALSE;
}

// Handle player movements when given a command
// Increment turns_taken and step_count for statistics
// INPUT:
// 		pointer to board
// 		pointer to struct player
// 		char player_input
// 		pointer to int turns_taken
// 		pointer to int step_count
// OUTPUT:
// 		int (1 if player moved, 0 otherwise)
int handle_wombat_tunnel_teleport(
    struct tile board[ROWS][COLS],
    struct position *player,
    struct position target,
    struct position wombat_offset,
    int *step_count,
    int riding_kangaroo,
    int *baby_chicken_count,
    int baby_chicken_total
) {
    int tunnel_id = board[target.row][target.col].wombat_id;
    struct position destination;

    if (find_matching_wombat_tunnel(board, &destination, tunnel_id, target)) {
        struct position exit;
        exit.row = destination.row + wombat_offset.row;
        exit.col = destination.col + wombat_offset.col;

        if (!check_in_bounds(exit) || check_touching_tree(board, exit)) {
            return 0;
        }

        if (check_can_move(board, exit)) {
            player->row = exit.row;
            player->col = exit.col;
            (*step_count)++;
            reset_baby_chickens(board, baby_chicken_count, baby_chicken_total);
        } else {
            player->row = destination.row;
            player->col = destination.col;
        }
    } else {
        player->row = target.row;
        player->col = target.col;
        if (!riding_kangaroo) {
            board[player->row][player->col].baby_chicken =
                baby_chicken_total + 1;
            *baby_chicken_count -= 1;
            move_baby_chickens(board);
        }
    }
    return 1;
}

int handle_kangaroo_ride(
    struct tile board[ROWS][COLS],
    struct position *player,
    char player_input,
    struct position target,
    int *jump_distance,
    int *baby_chicken_count,
    int baby_chicken_total
) {
    int riding_kangaroo = check_is_kangaroo(board, *player);
    *jump_distance = 1;
    
    if (riding_kangaroo) {
        *jump_distance = board[player->row][player->col].roo_jump_length;
        reset_baby_chickens(board, baby_chicken_count, baby_chicken_total);
    }
    
    return riding_kangaroo;
}

struct position calculate_target_position(
    struct tile board[ROWS][COLS],
    struct position player,
    char player_input,
    int jump_distance,
    int riding_kangaroo,
    char mode,
    struct position *wombat_offset
) {
    struct position target = {player.row, player.col};
    
    if (player_input == 'w') {
        struct position wombat_check;
        wombat_check.row = ROWS - 1;
        wombat_check.col = player.col;
        wombat_offset->row = -1;
        
        if (
            !riding_kangaroo &&
            mode == 's' &&
            player.row == 0 &&
            check_is_wombat_tunnel(board, wombat_check)
        ) {
            target.row = ROWS - 1;
        } else {
            target.row -= jump_distance;
        }
    } else if (player_input == 's') {
        wombat_offset->row = 1;
        target.row += jump_distance;
    } else if (player_input == 'a') {
        wombat_offset->col = -1;
        target.col -= jump_distance;
    } else if (player_input == 'd') {
        wombat_offset->col = 1;
        target.col += jump_distance;
    }

    return target;
}

int validate_kangaroo_move(
    struct tile board[ROWS][COLS],
    struct position player,
    struct position target,
    int *baby_chicken_count,
    int baby_chicken_total
) {
    if (check_is_kangaroo(board, player) &&
        (!check_in_bounds(target) || check_touching_tree(board, target))) {
        board[player.row][player.col].entity = 
            board[player.row][player.col].roo_base_entity;
        board[player.row][player.col].roo_jump_length = 0;
        board[player.row][player.col].roo_base_entity = EMPTY;
        reset_baby_chickens(board, baby_chicken_count, baby_chicken_total);
        return 0;
    }
    return 1;
}

int validate_move_and_cleanup(
    struct tile board[ROWS][COLS],
    struct position player,
    struct position target,
    int riding_kangaroo,
    int *baby_chicken_count,
    int baby_chicken_total
) {
    if (!check_can_move(board, target)) {
        if (riding_kangaroo) {
            reset_baby_chickens(board, baby_chicken_count, baby_chicken_total);
        }
        return 0;
    } else {
        board[player.row][player.col].baby_chicken = baby_chicken_total + 1;
        if (riding_kangaroo) {
            reset_baby_chickens(board, baby_chicken_count, baby_chicken_total);
        }
    }
    return 1;
}

int execute_move(
    struct tile board[ROWS][COLS],
    struct position *player,
    struct position target,
    struct position wombat_offset,
    int riding_kangaroo,
    int *step_count,
    int *baby_chicken_count,
    int baby_chicken_total
) {
    if (check_is_wombat_tunnel(board, target)) {
        return handle_wombat_tunnel_teleport(
            board, player, target, 
            wombat_offset,
            step_count,
            riding_kangaroo,
            baby_chicken_count,
            baby_chicken_total
        );
    } else if (riding_kangaroo) {
        move_kangaroo(board, player, target);
        reset_baby_chickens(board, baby_chicken_count, baby_chicken_total);
    } else {
        board[player->row][player->col].baby_chicken = baby_chicken_total + 1;
        player->row = target.row;
        player->col = target.col;
        
        if (check_is_kangaroo(board, *player)) {
            reset_baby_chickens(board, baby_chicken_count, baby_chicken_total);
        }
        
        board[player->row][player->col].baby_chicken = baby_chicken_total + 1;
        *baby_chicken_count -= 1;
        move_baby_chickens(board);
    }
    
    *step_count += 1;
    return 1;
}

int move_player(
    struct tile board[ROWS][COLS],
    struct position *player,
    char player_input,
    int *turns_taken,
    int *step_count,
    char mode,
    int *jump_distance,
    int *baby_chicken_count,
    int baby_chicken_total
) {
    int riding_kangaroo = handle_kangaroo_ride(board, player, player_input,
        *player, jump_distance, baby_chicken_count, baby_chicken_total);
    
    struct position wombat_offset = {0, 0};
    struct position target = calculate_target_position(board, *player,
        player_input, *jump_distance, riding_kangaroo, mode, &wombat_offset);
    
    *turns_taken += 1;
    
    if (!validate_kangaroo_move(board, *player, target,
        baby_chicken_count, baby_chicken_total)) {
        return 0;
    }
    
    if (!validate_move_and_cleanup(board, *player, target, riding_kangaroo,
        baby_chicken_count, baby_chicken_total)) {
        return 0;
    }
    
    return execute_move(board, player, target, wombat_offset, riding_kangaroo,
        step_count, baby_chicken_count, baby_chicken_total);
}

void reset_baby_chickens(
    struct tile board[ROWS][COLS],
    int *baby_chicken_count,
    int baby_chicken_total
) {
    *baby_chicken_count = baby_chicken_total;
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].baby_chicken = 0;
        }
    }
}

void move_kangaroo(
    struct tile board[ROWS][COLS],
    struct position *player,
    struct position target
) {

    // Set current jump length
    int current_jump_length = board[player->row][player->col].roo_jump_length;

    // Set previous position to base entity
    board[player->row][player->col].entity =
        board[player->row][player->col].roo_base_entity;
    if (!check_is_car(board, target)) {

        // Alternate jump lengths
        if (current_jump_length == 2) {
            board[target.row][target.col].roo_jump_length = 3;
        } else if (current_jump_length == 3) {
            board[target.row][target.col].roo_jump_length = 2;
        }

        board[target.row][target.col].roo_base_entity =
            board[target.row][target.col].entity;
        board[target.row][target.col].entity = KANGAROO;
    }

    // Reset old position
    board[player->row][player->col].roo_jump_length = 0;
    board[player->row][player->col].roo_base_entity = EMPTY;

    // Move player
    player->row = target.row;
    player->col = target.col;
}

void move_baby_chickens(struct tile board[ROWS][COLS]) {
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            board[row][col].baby_chicken -= 1;
        }
    }
}

// Check if a tile has a coin
// Collect the coin and increment score and coins for statistics
// INPUT:
// 		pointer to board
// 		pointer to struct player
// 		pointer to int points
// 		pointer to int coins
// OUTPUT:
// 		void
void has_coin(
    struct tile board[ROWS][COLS],
    struct position *player,
    int *points,
    int *coins
) {
    if (board[player->row][player->col].entity == COIN) {
        board[player->row][player->col].entity = EMPTY;
        *points += 5;
        *coins += 1;
    }
}
