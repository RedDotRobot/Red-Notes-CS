// Assignment 2 26T1 COMP1511: CS Karting
// cs_karting.h
//
// Written by LUCAS CHEUNG, z5763342
// on 23-04-2026
//
// Header file for cs_karting.c

////////////////////////////////////////////////////////////////////////////////
// Provided Constants
////////////////////////////////////////////////////////////////////////////////
#define MAX_SIZE 100

////////////////////////////////////////////////////////////////////////////////
// Your constants
////////////////////////////////////////////////////////////////////////////////
#define MAX_DRIVERS 8
#define MAX_SPEED 3
#define MIN_SPEED 1

#define COMMAND_HELP '?'
#define COMMAND_APPEND 'a'
#define COMMAND_INSERT 'i'
#define COMMAND_RACE 'r'
#define COMMAND_TRACK 't'
#define COMMAND_DRIVER 'd'
#define COMMAND_COPY 'c'
#define COMMAND_FINALS 'f'
#define COMMAND_VALIDATE 'v'
#define COMMAND_START_RACE 's'
#define COMMAND_REMOVE 'r'
#define COMMAND_MOVE 'm'
#define COMMAND_PLAY_TURN 't'
#define COMMAND_END 'e'
#define COMMAND_PRINT_SERIES '*'
#define COMMAND_QUIT 'q'

////////////////////////////////////////////////////////////////////////////////
// Provided Enums
////////////////////////////////////////////////////////////////////////////////
enum mystery_box {
    MUSHROOM,
    BANANA_PEEL,
    STAR,
    LIGHTNING,
    BLUE_SHELL,
    BULLET,
    NO_MYSTERY_BOX
};

enum piece_type {
    START_LINE,
    FINISH_LINE,
    STRAIGHT,
    LEFT_TURN,
    RIGHT_TURN,
    JUMP,
    MYSTERY_BOX,
    INVALID
};

enum location {
    ALBERT_PARK,
    MARINA_BAY,
    MONZA,
    SUZUKA,
    ZANDVOORT
};

enum race_status {
    NOT_STARTED,
    ACTIVE,
    COMPLETED
};

enum points {
    FIRST = 15,
    SECOND = 10,
    THIRD = 7,
    FOURTH = 5,
    FIFTH = 4,
    SIXTH = 3,
    SEVENTH = 2,
    EIGHTH = 1
};

enum boolean {
    FALSE,
    TRUE
};

////////////////////////////////////////////////////////////////////////////////
// Provided Structs
////////////////////////////////////////////////////////////////////////////////

struct driver {
    char name[MAX_SIZE];
    int speed;
    int place;
    int laps_completed;
    enum boolean invincible;
    struct driver *next;
};

struct track_piece {
    enum piece_type type;
    struct driver *drivers;
    struct track_piece *next;
};

struct race {
    char name[MAX_SIZE];
    enum location location;
    enum race_status status;
    enum boolean is_finals;
    enum mystery_box next_mystery_box;
    struct track_piece *track;
    struct driver *drivers;
    struct race *next;
};

struct series {
    char name[MAX_SIZE];
    struct race *races;
};

struct score_node {
    char name[MAX_SIZE];
    int points;
    struct score_node *next;
};

////////////////////////////////////////////////////////////////////////////////
// Function prototypes
////////////////////////////////////////////////////////////////////////////////
struct series *create_series(char name[MAX_SIZE]);
struct race *create_race(char name[MAX_SIZE], enum location location);
struct track_piece *create_track(enum piece_type type);
struct driver *create_driver(char name[MAX_SIZE], int speed);

void command_loop(struct series *series);

void append_race(struct series *series);
void append_track_piece(struct series *series);
int has_driver_name(struct driver *head, char name[MAX_SIZE]);
struct driver *find_driver_tail(struct driver *head);
void print_duplicate_driver_error(char driver_name[MAX_SIZE]);
void append_driver(struct series *series, int *drivers_count);

void print_track_piece_inserted(enum piece_type type);
void insert_track_at_position(
    struct race *race,
    struct track_piece *new_track_piece,
    int index
);
void insert_track_piece(struct series *series);
int can_insert_driver(
    int index,
    int speed,
    int drivers_count,
    struct race *race,
    char driver_name[MAX_SIZE]
);
void insert_driver_at_position(
    struct race *race,
    struct driver *new_driver,
    int index
);
void insert_driver(struct series *series, int *drivers_count);

int race_name_exists(struct series *series, char race_name[MAX_SIZE]);
void copy_track_layout(
    struct race *source,
    struct race *destination,
    int skip_start_finish
);
void append_race_node(struct series *series, struct race *new_race);

void copy_race(struct series *series);
struct race *find_completed_race_for_location(
    struct series *series,
    enum location location
);
int finals_exists_for_location(
    struct series *series,
    enum location location
);
void finals_name_for_location(
    enum location location,
    char finals_name[MAX_SIZE]
);
struct score_node *find_score_node(
    struct score_node *scores,
    char name[MAX_SIZE]
);
void add_completed_race_scores(
    struct score_node **scores,
    struct race *race
);
void append_driver_node(
    struct driver **head,
    struct driver **tail,
    struct driver *node
);
struct score_node *collect_location_scores(
    struct series *series,
    enum location location
);
void build_finals_drivers_from_scores(
    struct race *finals_race,
    struct score_node **scores
);
void free_scores(struct score_node *scores);
struct score_node *pop_best_score(struct score_node **scores);
void play_finals(struct series *series);
void validate_race(struct series *series);
void start_race(struct series *series);
void quit_series(struct series *series);

int remove_driver_from_list(struct driver **head, char *driver_name);
void remove_driver_from_not_started(struct race *race, char *driver_name);
void remove_driver_from_active(struct race *race, char *driver_name);
void check_remove_driver_found(
    struct track_piece *current_track,
    char driver_name[MAX_SIZE],
    int *found
);
void remove_driver(struct series *series);
struct driver *detach_named_driver(
    struct driver **head,
    char driver_name[MAX_SIZE]
);
int count_and_check_driver_name(
    struct driver *head,
    char driver_name[MAX_SIZE]
);
struct race *get_ready_race(
    struct series *series,
    char race_name[MAX_SIZE]
);
void restore_driver_to_race(struct race *race, struct driver *driver);
int can_receive_driver(
    struct race *new_race,
    char driver_name[MAX_SIZE],
    char new_race_name[MAX_SIZE],
    struct race *old_race,
    struct driver *driver
);
void move_driver(struct series *series);

void play_turn(struct series *series);
struct track_piece *find_finish_line(struct race *race);
struct track_piece *find_prev_track(
    struct track_piece *start_line,
    struct track_piece *current_track
);
void append_driver_to_piece(
    struct track_piece *piece,
    struct driver *driver
);
struct track_piece *move_driver_steps(
    struct track_piece *start,
    int steps
);
int keep_finals_finisher(
    struct race *race,
    struct track_piece *current_track,
    struct track_piece *finish_line,
    struct driver *current_driver
);
int handle_finals_wrap(
    struct race *race,
    struct track_piece *target_track,
    struct driver *current_driver,
    struct driver **wrapped_to_start,
    struct driver **wrapped_tail
);
void driver_turn(struct race *race);

void end_race(struct series *series);
void check_completion(struct race *current_race);

int driver_is_before_on_piece(
    struct track_piece *piece,
    struct driver *first,
    struct driver *second
);
int is_driver_ahead_in_finals(
    struct track_piece *piece_a,
    int piece_a_index,
    struct driver *driver_a,
    int piece_b_index,
    struct driver *driver_b
);
int count_drivers_ahead_in_finals(
    struct race *race,
    struct track_piece *piece_a,
    int piece_a_index,
    struct driver *driver_a
);
void update_finals_places(struct race *race);
void update_non_finals_places(struct race *race);
void update_places(struct race *race);

void check_mystery_boxes(struct race *race);
void apply_mystery_boxes(struct race *race, int mb_driver_place);
int count_active_drivers(struct race *race);
int active_rank_to_overall_place(struct race *race, int active_rank);
int overall_place_to_active_rank(struct race *race, int overall_place);

int mb_apply_mushroom(struct race *race, struct driver *mb_driver);
int mb_apply_banana(struct race *race, struct driver *mb_driver);
int mb_apply_star(struct race *race, struct driver *mb_driver);
void check_star_and_speed(
    struct driver *current_driver,
    struct driver *mb_driver
);
int mb_apply_lightning(struct race *race, struct driver *mb_driver);
struct driver *find_prev_driver_on_piece(
    struct track_piece *piece,
    struct driver *target
);
void replace_driver_reference(
    struct track_piece *piece,
    struct driver *prev,
    struct driver *replacement
);
void swap_blue_shell_targets(
    struct track_piece *first_piece,
    struct track_piece *second_piece,
    struct driver *first_place,
    struct driver *second_place
);
int mb_apply_blue_shell(struct race *race, struct driver *mb_driver);
void insert_driver_before_target(
    struct track_piece *piece,
    struct driver *target,
    struct driver *driver_to_insert
);
int mb_apply_bullet(struct race *race, struct driver *mb_driver);

struct race *find_race_by_name(
    struct series *series, char race_name[MAX_SIZE]);
struct driver *find_driver_by_name(
    struct race *race, char driver_name[MAX_SIZE]);
struct driver *find_driver_by_place(struct race *race, int place);
struct track_piece *find_track_by_place(struct race *race, int place);
int is_race_not_started(struct race *race);
int is_race_completed(struct race *race);
int count_drivers(struct race *race);
int first_active_place(struct race *race);

////////////////////////////////////////////////////////////////////////////////
// Helper function prototypes
////////////////////////////////////////////////////////////////////////////////
void print_usage();
void print_welcome_banner();
void print_series(struct series *series);
void print_track(struct track_piece *track, int *driver_place);
void print_drivers(struct race *race);

void scan_name(char name[MAX_SIZE]);
enum location scan_location(void);
enum piece_type scan_piece_type(void);

enum location string_to_location(char *type_str);
char *location_to_string(enum location location);
enum piece_type string_to_type(char *type_str);
char *type_to_string(enum piece_type type);
enum points place_to_points(int place);
char *status_to_string(enum race_status status);
int scan_token(char *buffer, int buffer_size);
