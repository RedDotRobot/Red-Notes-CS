// Assignment 2 26T1 COMP1511: CS Karting
// cs_karting.h
//
// Written by LUCAS CHEUNG, z5763342
// on 23-04-2026
//
// Primary program called in main

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "cs_karting.h"


// Stage 1.1
// Function to create the Racing Series
// Params:
//      name - the name of the series
// Returns: a pointer to the series
struct series *create_series(char name[MAX_SIZE]) {

    struct series *series = malloc(sizeof(struct series));

    strcpy(series->name, name);
    series->races = NULL;

    return series;
}

// Stage 1.1
// Function to create a race
// Params:
//      name - the name of the race
//      location - the location of the race
// Returns: a pointer to the race
struct race *create_race(char name[MAX_SIZE], enum location location) {

    struct race *race = malloc(sizeof(struct race));

    strcpy(race->name, name);
    race->location = location;
    race->status = NOT_STARTED;
    race->is_finals = FALSE;
    race->next_mystery_box = MUSHROOM;
    race->track = NULL;
    race->drivers = NULL;
    race->next = NULL;

    return race;
}

// Stage 1.1
// Function to create a track piece
// Params:
//      type - the type of track piece
// Returns: a pointer to the track piece
struct track_piece *create_track(enum piece_type type) {

    struct track_piece *track_piece = malloc(sizeof(struct track_piece));
    
    track_piece->type = type;
    track_piece->drivers = NULL;
    track_piece->next = NULL;

    return track_piece;
}

// Stage 1.1
// Function to create a driver
// Params:
//      name - the name of the driver
//      speed - the speed of the driver
// Returns: a pointer to the driver
struct driver *create_driver(char name[MAX_SIZE], int speed) {

    struct driver *driver = malloc(sizeof(struct driver));
    strcpy(driver->name, name);
    driver->speed = speed;
    driver->place = 0;
    driver->laps_completed = 0;
    driver->invincible = FALSE;
    driver->next = NULL;

    return driver;
}

// Stage 1.2
// Function to run the main command loop for the program
// Params:
//      series - a pointer to the racing series
// Returns: None
void command_loop(struct series *series) {
    int drivers_count = 0;
    char command;
    printf("Enter command: ");
    while (scanf(" %c", &command) == 1) {
        if (command == COMMAND_HELP) {
            print_usage();
        } else if (command == COMMAND_APPEND) {
            char append_command;
            scanf(" %c", &append_command);
            if (append_command == COMMAND_RACE) {
                append_race(series);
            } else if (append_command == COMMAND_TRACK) {
                append_track_piece(series);
            } else if (append_command == COMMAND_DRIVER) {
                append_driver(series, &drivers_count);
            }
        } else if (command == COMMAND_INSERT) {
            char insert_command;
            scanf(" %c", &insert_command);
            if (insert_command == COMMAND_TRACK) {
                insert_track_piece(series);
            } else if (insert_command == COMMAND_DRIVER) {
                insert_driver(series, &drivers_count);
            }
        } else if (command == COMMAND_COPY) {
            copy_race(series);
        } else if (command == COMMAND_FINALS) {
            play_finals(series);
        } else if (command == COMMAND_VALIDATE) {
            validate_race(series);
        } else if (command == COMMAND_START_RACE) {
            start_race(series);
        } else if (command == COMMAND_REMOVE) {
            remove_driver(series);
        } else if (command == COMMAND_MOVE) {
            move_driver(series);
        } else if (command == COMMAND_PLAY_TURN) {
            play_turn(series);
        } else if (command == COMMAND_END) {
            end_race(series);
        } else if (command == COMMAND_PRINT_SERIES) {
            print_series(series);
        } else if (command == COMMAND_QUIT) {
            return;
        } else {
            printf("ERROR: Invalid command.\n");
        }
        printf("Enter command: ");
    }
    return;
}

// Stage 1.3
// Function to append a race
// Params:
//      series - a pointer to the racing series
// Returns: None
void append_race(struct series *series) {

    // Scan race name and race location
    char race_name[MAX_SIZE];
    scan_name(race_name);
    enum location location = scan_location();

    struct race *new_race = create_race(race_name, location);

    if (series->races == NULL) {
        series->races = new_race;
    } else {

        struct race *current_race = series->races;
        
        // Navigate to end of linked list
        while (current_race->next != NULL) {
            // Error handling for duplicate race name
            if (strcmp(current_race->name, race_name) == 0) {
                printf("ERROR: Race %s already exists.\n", race_name);
                return;
            }
            current_race = current_race->next;
        }

        // Error check the last node too
        if (strcmp(current_race->name, race_name) == 0) {
            printf("ERROR: Race %s already exists.\n", race_name);
            return;
        }

        // Append new race to end of list
        current_race->next = new_race;
    }

    printf("Race: '%s' added!\n", race_name);

    return;
}

// Stage 1.3
// Function to append a track piece
// Params:
//      series - a pointer to the racing series
// Returns: None
void append_track_piece(struct series *series) {

    // Scan race name
    char race_name[MAX_SIZE];
    scan_name(race_name);

    // Initialise and declare track piece and its type
    enum piece_type type = scan_piece_type();

    // Error handling for INVALID type
    if (type == -1) {
        printf("ERROR: Invalid track piece type.\n");
        return;
    }

    struct track_piece *new_track_piece = create_track(type);
    
    // Search for race
    struct race *current_race = find_race_by_name(series, race_name);

    if (current_race == NULL) {
        return;
    }

    // Error handling for already active race
    if (current_race->status != NOT_STARTED) {
        printf("ERROR: Race %s has already started.\n", race_name);
        return;
    }

    if (current_race->track == NULL) {
        current_race->track = new_track_piece;
        printf("Track Piece: '%s' added!\n",
                type_to_string(new_track_piece->type));
        return;
    } else {
        // Navigate to end of track piece list
        struct track_piece *current_piece = current_race->track;
        while (current_piece->next != NULL) {
            current_piece = current_piece->next;
        }

        // Append new track piece to end of list
        current_piece->next = new_track_piece;
    }

    printf("Track Piece: '%s' added!\n", type_to_string(new_track_piece->type));
    return;
}

// Check if a driver name already exists
// Params:
//      *head - pointer to head of driver list
//      name - string to search for
// Returns:
//      int - TRUE if driver name exists, FALSE otherwise
int has_driver_name(struct driver *head, char name[MAX_SIZE]) {
    struct driver *current_driver = head;
    while (current_driver != NULL) {
        if (strcmp(current_driver->name, name) == 0) {
            return TRUE;
        }
        current_driver = current_driver->next;
    }
    return FALSE;
}

// Navigate to end of driver list
// Params:
//      *head - pointer to head of driver list
// Returns:
//      driver - pointer to driver at end of list
struct driver *find_driver_tail(struct driver *head) {
    struct driver *tail = head;
    while (tail != NULL && tail->next != NULL) {
        tail = tail->next;
    }
    return tail;
}

// Prints error message for duplicate driver
// Params: driver_name - name of duplicate driver
// Returns: none
void print_duplicate_driver_error(char driver_name[MAX_SIZE]) {
    printf("ERROR: Driver with name %s already exists in race.\n", driver_name);
}

// Stage 1.3
// Function to append a driver
// Params:
//      series - a pointer to the racing series
// Returns: None
void append_driver(struct series *series, int *drivers_count) {

    char race_name[MAX_SIZE];
    char driver_name[MAX_SIZE];
    int speed;

    scan_name(race_name);
    scan_name(driver_name);
    scanf(" %d", &speed);

    struct race *current_race = find_race_by_name(series, race_name);
    if (current_race == NULL) {
        return;
    }
    // Error handling for already active race
    if (is_race_not_started(current_race)) {
        return;
    }
    // Error handling for driver count exceeds MAX_DRIVERS
    if (*drivers_count >= MAX_DRIVERS-1) {
        printf("ERROR: Maximum of %d drivers per race.\n", MAX_DRIVERS);
        return;
    }
    if (current_race->drivers == NULL) {
        struct driver *new_driver = create_driver(driver_name, speed);
        current_race->drivers = new_driver;
        printf("Driver: '%s' added!\n", new_driver->name);
        return;
    }

    if (has_driver_name(current_race->drivers, driver_name)) {
        print_duplicate_driver_error(driver_name);
        return;
    }
    if (!(speed >= MIN_SPEED && speed <= MAX_SPEED)) {
        printf("ERROR: Driver speed must be within %d and %d.\n",
                MIN_SPEED, MAX_SPEED);
        return;
    }

    struct driver *new_driver = create_driver(driver_name, speed);
    struct driver *tail = find_driver_tail(current_race->drivers);
    tail->next = new_driver;
    (*drivers_count)++;
    printf("Driver: '%s' added!\n", new_driver->name);
    return;
}

// Prints message when track piece is inserted
// Params: type - the type of the track piece inserted
// Returns: none
void print_track_piece_inserted(enum piece_type type) {
    printf("Track Piece: '%s' inserted!\n", type_to_string(type));
}

// Inserts a track at a given position
// Params:
//      *race - pointer to race to insert to
//      *new_track_piece - pointer to track piece to insert
//      index - int of where to insert
// Returns:
//      none
void insert_track_at_position(
    struct race *race,
    struct track_piece *new_track_piece,
    int index
) {
    if (race->track == NULL) {
        race->track = new_track_piece;
        return;
    }
    if (index == 1) {
        new_track_piece->next = race->track;
        race->track = new_track_piece;
        return;
    }

    struct track_piece *current_piece = race->track;
    for (int track = 0; track < index - 2; track++) {
        if (current_piece->next == NULL) {
            current_piece->next = new_track_piece;
            return;
        }
        current_piece = current_piece->next;
    }
    new_track_piece->next = current_piece->next;
    current_piece->next = new_track_piece;
}

// Main handler for inserting track piece
// Params: *series - pointer to racing series
// Returns: none
void insert_track_piece(struct series *series) {

    // Scan index to insert to
    int index;
    scanf(" %d", &index);

    // Scan race name
    char race_name[MAX_SIZE];
    scan_name(race_name);

    // Initialise and declare track piece and its type
    enum piece_type type = scan_piece_type();

    // Error handling for INVALID type
    if (type == -1) {
        printf("ERROR: Invalid track piece type.\n");
        return;
    }

    struct track_piece *new_track_piece = create_track(type);

    // Search for race
    struct race *current_race = find_race_by_name(series, race_name);

    if (current_race == NULL) {
        return;
    }

    // Error handling for already active race
    if (is_race_not_started(current_race)) {
        return;
    }

    // Error handling for negative index
    if (index < 1) {
        printf("ERROR: Position must be at least 1.\n");
        return;
    }

    insert_track_at_position(current_race, new_track_piece, index);
    print_track_piece_inserted(new_track_piece->type);
    return;
}

// Handles errors if driver cannot be inserted
// Params:
//      index - where to insert
//      speed - speed of driver
//      drivers_count - number of drivers already placed
//      *race - pointer to race to insert to
//      driver_name - string of driver's name
// Returns:
//      int - TRUE if driver can be inserted, FALSE otherwise
int can_insert_driver(
    int index,
    int speed,
    int drivers_count,
    struct race *race,
    char driver_name[MAX_SIZE]
) {
    if (index < 1) {
        printf("ERROR: Position must be at least 1.\n");
        return FALSE;
    }
    if (has_driver_name(race->drivers, driver_name)) {
        print_duplicate_driver_error(driver_name);
        return FALSE;
    }
    if (!(speed >= MIN_SPEED && speed <= MAX_SPEED)) {
        printf("ERROR: Driver speed must be within %d and %d.\n",
                MIN_SPEED, MAX_SPEED);
        return FALSE;
    }
    if (drivers_count >= MAX_DRIVERS) {
        printf("ERROR: Maximum of %d drivers per race.\n", MAX_DRIVERS);
        return FALSE;
    }
    return TRUE;
}

// Inserts a driver at a position
// Params:
//      *race - pointer to race to insert to
//      *new_driver - pointer to driver to insert
//      index - where to insert to
// Returns:
//      none
void insert_driver_at_position(
    struct race *race,
    struct driver *new_driver,
    int index
) {
    if (race->drivers == NULL) {
        race->drivers = new_driver;
        return;
    }
    if (index == 1) {
        new_driver->next = race->drivers;
        race->drivers = new_driver;
        return;
    }

    struct driver *current_driver = race->drivers;
    for (int i = 0; i < index - 2; i++) {
        if (current_driver->next == NULL) {
            current_driver->next = new_driver;
            return;
        }
        current_driver = current_driver->next;
    }
    new_driver->next = current_driver->next;
    current_driver->next = new_driver;
}

// Handler for inserting a driver at an index
// Params:
//      *series - pointer to racing series
//      *drivers_count - pointer to number of total drivers
// Returns:
//      none
void insert_driver(struct series *series, int *drivers_count) {

    // Scan index to insert to
    int index;
    scanf(" %d", &index);

    // Scan race name
    char race_name[MAX_SIZE];
    scan_name(race_name);

    // Initialise and declare driver name and speed
    char driver_name[MAX_SIZE];
    int speed;
    scan_name(driver_name);
    scanf(" %d", &speed);

    // Search for race
    struct race *current_race = find_race_by_name(series, race_name);

    if (current_race == NULL) {
        return;
    }
    
    if (
        can_insert_driver(index, speed,
            *drivers_count, current_race, driver_name) == FALSE) {
        return;
    }

    if (current_race->drivers == NULL) {
        struct driver *new_driver = create_driver(driver_name, speed);
        current_race->drivers = new_driver;
        printf("Driver: '%s' inserted!\n", new_driver->name);
        return;
    }

    struct driver *new_driver = create_driver(driver_name, speed);
    insert_driver_at_position(current_race, new_driver, index);
    printf("Driver: '%s' inserted!\n", new_driver->name);
    (*drivers_count)++;
}

// Check if a race name exists
// Params:
//      *series - pointer to racing series
//      race_name - string of race name to check
// Returns:
//      int - TRUE if race name exists, FALSE otherwise
int race_name_exists(struct series *series, char race_name[MAX_SIZE]) {
    struct race *current = series->races;
    while (current != NULL) {
        if (strcmp(current->name, race_name) == 0) {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}

// Copies the layout of a track
// Params:
//      *source - pointer of what to copy
//      *destination - pointer of where to copy to
//      skip_start_finish - placeholder to choose to skip start or finish
//                          (this was never used...)
// Returns:
//      none
void copy_track_layout(
    struct race *source,
    struct race *destination,
    int skip_start_finish
) {
    struct track_piece *src_piece = source->track;
    struct track_piece *dst_tail = NULL;
    while (src_piece != NULL) {
        if (
            skip_start_finish == FALSE ||
            (src_piece->type != START_LINE && src_piece->type != FINISH_LINE)
        ) {
            struct track_piece *new_piece = create_track(src_piece->type);
            if (destination->track == NULL) {
                destination->track = new_piece;
            } else {
                dst_tail->next = new_piece;
            }
            dst_tail = new_piece;
        }
        src_piece = src_piece->next;
    }
}

// Appends a race to the series
// Params:
//      *series - pointer to racing series
//      *new_race - pointer to race to append
// Returns:
//      none
void append_race_node(struct series *series, struct race *new_race) {
    if (series->races == NULL) {
        series->races = new_race;
        return;
    }
    struct race *tail = series->races;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = new_race;
}

// Handler for copying a race
// Params: *series - pointer to racing series
// Returns: none
void copy_race(struct series *series) {

    char existing_race_name[MAX_SIZE];
    char new_race_name[MAX_SIZE];
    scan_name(existing_race_name);
    scan_name(new_race_name);

    // Search for existing race
    struct race *existing_race = find_race_by_name(series, existing_race_name);

    if (existing_race == NULL) {
        return;
    }

    // Error handling if new race name already exists
    if (race_name_exists(series, new_race_name)) {
        printf("ERROR: Race %s already exists.\n", new_race_name);
        return;
    }

    // Error handling for no track pieces to copy
    if (existing_race->track == NULL) {
        printf("ERROR: No track pieces in race to be copied.\n");
        return;
    }

    // Create new race with same location
    struct race *new_race = create_race(new_race_name, existing_race->location);

    // Duplicate track pieces
    copy_track_layout(existing_race, new_race, FALSE);
    append_race_node(series, new_race);

    return;
}

// Finds the first completed race at a given location
// Params:
//      *series - pointer to racing series
//      location - enum of location to search for
// Returns:
//      *race - pointer to race that is completed and has location,
//              returns NULL otherwise
struct race *find_completed_race_for_location(
    struct series *series,
    enum location location
) {
    struct race *current = series->races;
    while (current != NULL) {
        if (current->location == location && current->status == COMPLETED) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Checks if there is a final for a given location
// Params:
//      *series - pointer to racing series
//      location - enum of location to check
// Returns:
//      int - TRUE if location has final, FALSE otherwise
int finals_exists_for_location(
    struct series *series,
    enum location location
) {
    struct race *current = series->races;
    while (current != NULL) {
        if (current->location == location && current->is_finals == TRUE) {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}

// Appends _FINALS to name when generating a final
// Params:
//      location - enum of location to append to
//      finals_name - string of modified name
// Returns:
//      none
void finals_name_for_location(
    enum location location,
    char finals_name[MAX_SIZE]
) {
    if (location == ALBERT_PARK) {
        strcpy(finals_name, "ALBERT_PARK_FINALS");
    } else if (location == MARINA_BAY) {
        strcpy(finals_name, "MARINA_BAY_FINALS");
    } else if (location == MONZA) {
        strcpy(finals_name, "MONZA_FINALS");
    } else if (location == SUZUKA) {
        strcpy(finals_name, "SUZUKA_FINALS");
    } else {
        strcpy(finals_name, "ZANDVOORT_FINALS");
    }
}

// Finds a score node given a name
// Params:
//      *scores - pointer to head of scores
//      name - string to search for
// Returns:
//      score_node - score node with name
struct score_node *find_score_node(
    struct score_node *scores,
    char name[MAX_SIZE]
) {
    struct score_node *entry = scores;
    while (entry != NULL && strcmp(entry->name, name) != 0) {
        entry = entry->next;
    }
    return entry;
}

// Adds completed race scores
// Params:
//      **scores - double pointer to head of scores
//      *race - race add scores
// Returns:
//      none
void add_completed_race_scores(
    struct score_node **scores,
    struct race *race
) {
    int place = 1;
    struct driver *driver = race->drivers;
    while (driver != NULL) {
        struct score_node *entry = find_score_node(*scores, driver->name);
        if (entry == NULL) {
            struct score_node *new_entry = malloc(sizeof(struct score_node));
            strcpy(new_entry->name, driver->name);
            new_entry->points = place_to_points(place);
            new_entry->next = *scores;
            *scores = new_entry;
        } else {
            entry->points += place_to_points(place);
        }
        place++;
        driver = driver->next;
    }
}

// Gets best score
// Params: **scores - double pointer to head of scores
// Returns: score_node - best score
struct score_node *pop_best_score(struct score_node **scores) {
    struct score_node *best = *scores;
    struct score_node *best_prev = NULL;
    struct score_node *prev = NULL;
    struct score_node *scan = *scores;
    while (scan != NULL) {
        if (scan->points > best->points ||
            (scan->points == best->points &&
             strcmp(scan->name, best->name) < 0)) {
            best = scan;
            best_prev = prev;
        }
        prev = scan;
        scan = scan->next;
    }
    if (best_prev == NULL) {
        *scores = best->next;
    } else {
        best_prev->next = best->next;
    }
    return best;
}

// Appends a driver node
// Params:
//      **head - double pointer to head of drivers
//      **tail - double pointer to tail of drivers
//      *node - driver node to append
// Returns:
//      none
void append_driver_node(
    struct driver **head,
    struct driver **tail,
    struct driver *node
) {
    if (*head == NULL) {
        *head = node;
        *tail = node;
        return;
    }
    (*tail)->next = node;
    *tail = node;
}

// Handler for adding completed race scores
// Params:
//      *series - pointer to racing series
//      location - location enum to add scores
// Returns:
//      *score_node - pointer to scores
struct score_node *collect_location_scores(
    struct series *series,
    enum location location
) {
    struct score_node *scores = NULL;
    struct race *current = series->races;
    while (current != NULL) {
        if (current->location == location && current->status == COMPLETED) {
            add_completed_race_scores(&scores, current);
        }
        current = current->next;
    }
    return scores;
}

// Builds list of final drivers
// Params:
//      *finals_race - pointer to finals race for drivers
//      **scores - double pointer to scores head
// Returns:
//      none
void build_finals_drivers_from_scores(
    struct race *finals_race,
    struct score_node **scores
) {
    struct driver *finals_tail = NULL;
    int selected = 0;
    while (*scores != NULL && selected < MAX_DRIVERS) {
        struct score_node *best = pop_best_score(scores);
        struct driver *new_driver = create_driver(best->name, MIN_SPEED);
        append_driver_node(&(finals_race->drivers), &finals_tail, new_driver);
        selected++;
        free(best);
    }
}

// Free all scores
// Params: *scores - pointer to head of scores to free
// Returns: none
void free_scores(struct score_node *scores) {
    while (scores != NULL) {
        struct score_node *next = scores->next;
        free(scores);
        scores = next;
    }
}

// Main command for playing the finals
// Params: *series - pointer to racing series
// Returns: none
void play_finals(struct series *series) {
    enum location location = scan_location();
    char location_name[MAX_SIZE];
    strcpy(location_name, location_to_string(location));

    struct race *template_race =
        find_completed_race_for_location(series, location);

    if (template_race == NULL) {
        printf("ERROR: No completed races with location %s.\n", location_name);
        return;
    }

    if (finals_exists_for_location(series, location)) {
        printf("ERROR: Finals race for location %s already exists.\n",
                location_name);
        return;
    }

    char finals_name[MAX_SIZE];
    finals_name_for_location(location, finals_name);
    struct race *finals_race = create_race(finals_name, location);
    finals_race->is_finals = TRUE;
    copy_track_layout(template_race, finals_race, TRUE);

    struct score_node *scores = collect_location_scores(series, location);
    build_finals_drivers_from_scores(finals_race, &scores);
    free_scores(scores);
    append_race_node(series, finals_race);
}

// Validates race by inserting a STRAIGHT between two of same
// turns, and after jump
// Params: *series - pointer to racing series
// Returns: none
void validate_race(struct series *series) {

    char race_name[MAX_SIZE];
    scan_name(race_name);

    struct race *current_race = find_race_by_name(series, race_name);

    if (current_race == NULL) {
        return;
    }
    
    // Error handling for race already started
    if (is_race_not_started(current_race)) {
        return;
    }

    struct track_piece *current_track = current_race->track;
    while (current_track->next != NULL) {
        if (
            (current_track->type == RIGHT_TURN &&
            current_track->next->type == RIGHT_TURN) ||
            (current_track->type == LEFT_TURN &&
            current_track->next->type == LEFT_TURN)
        ) {
            struct track_piece *new_track_piece = create_track(STRAIGHT);
            new_track_piece->next = current_track->next;
            current_track->next = new_track_piece;
        } else if (
            current_track->type == JUMP &&
            current_track->next->type != STRAIGHT
        ) {
            struct track_piece *new_track_piece = create_track(STRAIGHT);
            new_track_piece->next = current_track->next;
            current_track->next = new_track_piece;
        }

        current_track = current_track->next;
    }

    printf("Race %s validated!\n", race_name);
    return;
}

// Starts a race
// Params: *series - pointer to racing series
// Returns: none
void start_race(struct series *series) {

    char race_name[MAX_SIZE];
    scan_name(race_name);

    struct race *current_race = find_race_by_name(series, race_name);
    if (current_race == NULL) {
        return;
    }

    // Error handling for race already started
    if (is_race_not_started(current_race)) {
        return;
    }

    // Error handling for race has no track
    if (current_race->track == NULL) {
        printf("ERROR: No track pieces in race %s.\n", race_name);
        return;
    }

    // Error handling for no drivers
    if (current_race->drivers == NULL) {
        printf("ERROR: No drivers in race %s.\n", race_name);
        return;
    }

    // Add start line
    struct track_piece *start_piece = create_track(START_LINE);
    start_piece->next = current_race->track;
    current_race->track = start_piece;

    // Move drivers to start line
    start_piece->drivers = current_race->drivers;
    current_race->drivers = NULL;

    // Add finish line
    struct track_piece *current_track = current_race->track;
    while (current_track->next != NULL) {
        current_track = current_track->next;
    }
    struct track_piece *end_piece = create_track(FINISH_LINE);
    current_track->next = end_piece;
    end_piece->next = NULL;

    current_race->status = ACTIVE;

    update_places(current_race);
    printf("Race %s started!\n", race_name);
    return;
}

// Command to quit the series
// Params: *series - pointer to racing series
// Returns: none
void quit_series(struct series *series) {

    if (series == NULL) {
        return;
    }

    struct race *current_race = series->races;
    while (current_race != NULL) {
        struct race *next_race = current_race->next;

        struct track_piece *current_track = current_race->track;
        while (current_track != NULL) {
            struct track_piece *next_track = current_track->next;

            struct driver *current_driver = current_track->drivers;
            while (current_driver != NULL) {
                struct driver *next_driver = current_driver->next;
                free(current_driver);
                current_driver = next_driver;
            }

            free(current_track);
            current_track = next_track;
        }
        struct driver *current_driver = current_race->drivers;
        while (current_driver != NULL) {
            struct driver *next_driver = current_driver->next;
            free(current_driver);
            current_driver = next_driver;
        }
        free(current_race);
        current_race = next_race;
    }
    free(series);
}

// Removes a driver from a list
// Params:
//      **head - double pointer to head of driver list
//      *driver_name - driver's name to remove
// Returns:
//      int - TRUE if driver was found and removed, FALSE otherwise
int remove_driver_from_list(struct driver **head, char *driver_name) {
    struct driver *prev = NULL;
    struct driver *current = *head;
    
    while (current != NULL) {
        if (strcmp(current->name, driver_name) == 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return TRUE;
        }
        prev = current;
        current = current->next;
    }
    return FALSE;
}

// Helper function to remove driver from NOT_STARTED race
// Params:
//      *race - pointer to race to remove from
//      *driver_name - name of driver to remove
// Returns:
//      none
void remove_driver_from_not_started(struct race *race, char *driver_name) {
    remove_driver_from_list(&(race->drivers), driver_name);
}


// Check if driver was removed
// Params:
//      *current_track - pointer to track piece to remove from
//      driver_name - name of driver to remove
//      *found - pointer to variable that states if driver was removed
// Returns:
//      none
void check_remove_driver_found(
    struct track_piece *current_track,
    char driver_name[MAX_SIZE],
    int *found
) {
    if (
        remove_driver_from_list(
            &(current_track->drivers),
            driver_name
        )
    ) {
        *found = TRUE;
    }
}

// Command to remove driver
// Params: *series - pointer to racing series
// Returns: none
void remove_driver(struct series *series) {

    char driver_name[MAX_SIZE];
    scan_name(driver_name);
    
    int found = FALSE;
    
    struct race *current_race = series->races;
    while (current_race != NULL) {
        if (current_race->status == NOT_STARTED) {
            if (
                remove_driver_from_list(
                    &(current_race->drivers),
                    driver_name
                )
            ) {
                found = TRUE;
            }
        } else if (current_race->status == ACTIVE) {
            struct track_piece *current_track = current_race->track;
            while (current_track != NULL) {
                check_remove_driver_found(current_track, driver_name, &found);
                current_track = current_track->next;
            }
        }
        current_race = current_race->next;
    }
    
    if (found) {
        printf("Driver %s removed from the racing series!\n", driver_name);
    } else {
        printf("ERROR: Driver %s not found in the series.\n", driver_name);
    }
}

// Detaches driver by name from list
// Params:
//      **head - double pointer to head of driver list
//      driver_name - name of driver to detach
// Returns:
//      *driver - pointer to detach driver
struct driver *detach_named_driver(
    struct driver **head,
    char driver_name[MAX_SIZE]
) {
    struct driver *current = *head;
    struct driver *prev = NULL;
    while (current != NULL && strcmp(current->name, driver_name) != 0) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return NULL;
    }
    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }
    current->next = NULL;
    return current;
}

// Counts and checks driver name
// Params:
//      *head - pointer to head of driver list
//      driver_name - name of driver to check
// Returns:
//      int - count
int count_and_check_driver_name(
    struct driver *head,
    char driver_name[MAX_SIZE]
) {
    int count = 0;
    while (head != NULL) {
        if (strcmp(head->name, driver_name) == 0) {
            return -1;
        }
        count++;
        head = head->next;
    }
    return count;
}

// Prepare race
// Params:
//      *series - pointer to racing series
//      race_name - name of race to prepare
// Returns:
//      *race - pointer to prepared race
struct race *get_ready_race(
    struct series *series,
    char race_name[MAX_SIZE]
) {
    struct race *race = find_race_by_name(series, race_name);
    if (race == NULL) {
        return NULL;
    }
    if (is_race_not_started(race)) {
        return NULL;
    }
    return race;
}

// Restores a driver to the race
// Params:
//      *race - pointer to race
//      *driver - pointer to driver to restore
// Returns:
//      none
void restore_driver_to_race(struct race *race, struct driver *driver) {
    driver->next = race->drivers;
    race->drivers = driver;
}

// Checks if a race can receive a new driver for moving drivers
// Params:
//      *new_race - race to check
//      driver_name - name of driver to check
//      new_race_name - name of race (for error messages)
//      *old_race - pointer to original race
//      *driver - pointer to driver to move
// Returns:
//      int - TRUE if can move driver, FALSE otherwise
int can_receive_driver(
    struct race *new_race,
    char driver_name[MAX_SIZE],
    char new_race_name[MAX_SIZE],
    struct race *old_race,
    struct driver *driver
) {
    int new_race_count =
        count_and_check_driver_name(new_race->drivers, driver_name);
    if (new_race_count == -1) {
        printf("ERROR: Driver %s already in race %s.\n",
                driver_name, new_race_name);
        restore_driver_to_race(old_race, driver);
        return FALSE;
    }
    if (new_race_count >= MAX_DRIVERS) {
        printf("ERROR: Race %s already at maximum driver limit.\n",
                new_race_name);
        restore_driver_to_race(old_race, driver);
        return FALSE;
    }
    return TRUE;
}

// Command to move a driver from one race to another
// Params: *series - pointer to racing series
// Returns: none
void move_driver(struct series *series) {
    char driver_name[MAX_SIZE];
    scan_name(driver_name);

    char current_race_name[MAX_SIZE];
    scan_name(current_race_name);

    char new_race_name[MAX_SIZE];
    scan_name(new_race_name);

    struct race *current_race = get_ready_race(series, current_race_name);
    if (current_race == NULL) {
        return;
    }
    struct race *new_race = get_ready_race(series, new_race_name);
    if (new_race == NULL) {
        return;
    }

    struct driver *current_driver =
        detach_named_driver(&(current_race->drivers), driver_name);
    if (current_driver == NULL) {
        printf("ERROR: Driver %s not found in race %s.\n",
                driver_name,
                current_race_name
        );
        return;
    }

    if (
        can_receive_driver(
            new_race, driver_name, new_race_name, current_race, current_driver
        ) == FALSE
    ) {
        return;
    }

    if (new_race->drivers == NULL) {
        new_race->drivers = current_driver;
    } else {
        struct driver *tail = new_race->drivers;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = current_driver;
    }

}

// Command to play a given number of turns of the race
// Params: *series - pointer to racing series
// Returns: none
void play_turn(struct series *series) {

    char race_name[MAX_SIZE];
    scan_name(race_name);

    int turns;
    scanf(" %d", &turns);

    struct race *current_race = find_race_by_name(series, race_name);
    if (current_race == NULL) {
        return;
    }

    if (current_race->status != ACTIVE) {
        printf("ERROR: Race %s is not active.\n", race_name);
        return;
    }

    if (turns < 1) {
        printf("ERROR: Turns must be a positive integer.\n");
        return;
    }

    update_places(current_race);
    for (int i = 0; i < turns; i++) {
        driver_turn(current_race);
        check_mystery_boxes(current_race);
    }
    update_places(current_race);
    check_completion(current_race);
    
}

// Finds the finish line of a race
// Params: *race - pointer of race to find finish line
// Returns: *track_piece - pointer to finish line
struct track_piece *find_finish_line(struct race *race) {
    struct track_piece *finish = race->track;
    while (finish->next != NULL) {
        finish = finish->next;
    }
    return finish;
}

// Finds the previous track
// Params:
//      *start_line - pointer to start of track
//      *current_track - pointer of track to find previous of
// Returns:
//      *track_piece - pointer to previous track piece, NULL if doesn't exist
struct track_piece *find_prev_track(
    struct track_piece *start_line,
    struct track_piece *current_track
) {
    struct track_piece *prev_track = NULL;
    struct track_piece *scan_track = start_line;
    while (scan_track != NULL && scan_track != current_track) {
        prev_track = scan_track;
        scan_track = scan_track->next;
    }
    return prev_track;
}

// Appends a driver to a track piece
// Params:
//      *piece - pointer to track piece to append driver to
//      *driver - pointer to driver to append
// Returns:
//      none
void append_driver_to_piece(
    struct track_piece *piece,
    struct driver *driver
) {
    if (piece->drivers == NULL) {
        piece->drivers = driver;
        return;
    }
    struct driver *tail = piece->drivers;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = driver;
}

// Iterate a target track piece a number of steps
// Params:
//      *start - pointer to start of where to 'step' from
//      steps - number of steps to take
// Returns:
//      *track_piece - pointer to track piece 'steps' away from *start
struct track_piece *move_driver_steps(
    struct track_piece *start,
    int steps
) {
    struct track_piece *target = start;
    while (steps > 0 && target->next != NULL) {
        target = target->next;
        steps--;
    }
    return target;
}

// Save finals finisher
// Params:
//      *race - pointer to race to save drivers
//      *current_track - pointer to checking track
//      *finish_line - pointer to finish line of the race
//      *current_driver - pointer to driver
// Returns:
//      int - TRUE if driver finished, FALSE otherwise
int keep_finals_finisher(
    struct race *race,
    struct track_piece *current_track,
    struct track_piece *finish_line,
    struct driver *current_driver
) {
    if (
        race->is_finals == TRUE &&
        current_track->type == FINISH_LINE &&
        current_driver->laps_completed >= 3
    ) {
        append_driver_to_piece(finish_line, current_driver);
        return TRUE;
    }
    return FALSE;
}

// Handle the looping for multiple laps in finals races
// Params:
//      *race - pointer to finals race
//      *target_track - pointer to target track
//      *current_driver - driver to calculate target track
//      **wrapped_to_start - double pointer to handler driver for wrapping
//      **wrapped_tail - double pointer to handler driver for wrapping
// Returns:
//      TRUE if wrapped, FALSE otherwise
int handle_finals_wrap(
    struct race *race,
    struct track_piece *target_track,
    struct driver *current_driver,
    struct driver **wrapped_to_start,
    struct driver **wrapped_tail
) {
    if (!(race->is_finals == TRUE && target_track->type == FINISH_LINE)) {
        return FALSE;
    }
    current_driver->laps_completed++;
    if (current_driver->laps_completed >= 3) {
        return FALSE;
    }
    append_driver_node(wrapped_to_start, wrapped_tail, current_driver);
    return TRUE;
}

// Handles one player turn in play_turn
// Params: *race - pointer to race to make a turn
// Returns: none
void driver_turn(struct race *race) {
    struct track_piece *start_line = race->track;
    struct track_piece *finish_line = find_finish_line(race);
    struct driver *wrapped_to_start = NULL;
    struct driver *wrapped_tail = NULL;

    struct track_piece *current_track = finish_line;
    while (current_track != NULL) {
        struct track_piece *prev_track =
            find_prev_track(start_line, current_track);
        struct driver *current_driver = current_track->drivers;
        current_track->drivers = NULL;

        while (current_driver != NULL) {
            struct driver *next_driver = current_driver->next;
            current_driver->next = NULL;
            if (
                keep_finals_finisher(race, current_track,
                    finish_line, current_driver)
            ) {
                current_driver = next_driver;
                continue;
            }
            struct track_piece *target_track =
                move_driver_steps(current_track, current_driver->speed);
            if (handle_finals_wrap(race, target_track, current_driver,
                &wrapped_to_start, &wrapped_tail)) {
                current_driver = next_driver;
                continue;
            }
            append_driver_to_piece(target_track, current_driver);
            current_driver = next_driver;
        }
        current_track = prev_track;
    }
    if (wrapped_to_start != NULL) {
        struct driver *tail = find_driver_tail(start_line->drivers);
        if (tail == NULL) {
            start_line->drivers = wrapped_to_start;
        } else {
            tail->next = wrapped_to_start;
        }
    }
}

// Command to end a race
// Params: *series - pointer to racing series
// Returns: none
void end_race(struct series *series) {

    char race_name[MAX_SIZE];
    scan_name(race_name);

    struct race *current_race = find_race_by_name(series, race_name);
    if (current_race == NULL) {
        return;
    }
    if (current_race->status != ACTIVE) {
        printf("ERROR: Race %s is not active.\n", current_race->name);
        return;
    }

    while (current_race->status == ACTIVE) {
        driver_turn(current_race);
        check_mystery_boxes(current_race);
        update_places(current_race);
        check_completion(current_race);
    }
    
}

// Checks if a race should be completed, handles race ends
// Params: *current_race - pointer to race to check
// Returns: none
void check_completion(struct race *current_race) {
    if (is_race_completed(current_race) == TRUE) {

        current_race->status = COMPLETED;

        // Move drivers from track to race
        struct track_piece *current_track = current_race->track;
        while (current_track->type != FINISH_LINE) {
            current_track = current_track->next;
        }

        current_race->drivers = current_track->drivers;
        current_track->drivers = NULL;

        printf("Race %s has finished!\n", current_race->name);

        printf("Final positions:\n");
        struct driver *current_driver = current_race->drivers;
        for (int i = 1; current_driver != NULL; i++) {
            printf(
                "    %d. %s (%d points)\n", i,
                current_driver->name,
                place_to_points(i)
            );
            current_driver = current_driver->next;
        }
    }
}

// Compares the position of two drivers on same track piece
// Params:
//      *piece - pointer of track piece to check
//      *first - pointer to first driver to check
//      *second - pointer to second driver to check
// Returns:
//      int - TRUE if first driver is first, FALSE otherwise
int driver_is_before_on_piece(
    struct track_piece *piece,
    struct driver *first,
    struct driver *second
) {
    struct driver *current = piece->drivers;
    while (current != NULL) {
        if (current == first) {
            return TRUE;
        }
        if (current == second) {
            return FALSE;
        }
        current = current->next;
    }
    return FALSE;
}

// Checks which driver is ahead in a finals race (since multiple laps)
// Params:
//      *piece_a - pointer to track piece to check
//      piece_a_index - the index of piece of driver a
//      *driver_a - pointer to driver a
//      piece_b_index - the index of piece of driver b
//      *driver_b - pointer to driver b
// Returns:
//      TRUE if ahead, FALSE otherwise
int is_driver_ahead_in_finals(
    struct track_piece *piece_a,
    int piece_a_index,
    struct driver *driver_a,
    int piece_b_index,
    struct driver *driver_b
) {
    if (driver_b->laps_completed > driver_a->laps_completed) {
        return TRUE;
    }
    if (driver_b->laps_completed < driver_a->laps_completed) {
        return FALSE;
    }
    if (piece_b_index > piece_a_index) {
        return TRUE;
    }
    if (piece_b_index < piece_a_index) {
        return FALSE;
    }
    return driver_is_before_on_piece(piece_a, driver_b, driver_a);
}

// Counts the number of drivers ahead in a finals race
// Params:
//      *race - pointer to race to check
//      *piece_a - track piece to check
//      piece_a_index - the index of piece of driver a
//      *driver_a - pointer to driver a
// Returns:
//      int - the number of drivers ahead
int count_drivers_ahead_in_finals(
    struct race *race,
    struct track_piece *piece_a,
    int piece_a_index,
    struct driver *driver_a
) {
    int drivers_ahead = 0;
    struct track_piece *piece_b = race->track;
    int piece_b_index = 0;
    while (piece_b != NULL) {
        struct driver *driver_b = piece_b->drivers;
        while (driver_b != NULL) {
            if (
                driver_b != driver_a &&
                is_driver_ahead_in_finals(
                    piece_a,
                    piece_a_index,
                    driver_a,
                    piece_b_index,
                    driver_b
                )
            ) {
                drivers_ahead++;
            }
            driver_b = driver_b->next;
        }
        piece_b = piece_b->next;
        piece_b_index++;
    }
    return drivers_ahead;
}

// Updates the places for finals races
// Params: *race - pointer to final race
// Returns: none
void update_finals_places(struct race *race) {
    struct track_piece *piece_a = race->track;
    int piece_a_index = 0;
    while (piece_a != NULL) {
        struct driver *driver_a = piece_a->drivers;
        while (driver_a != NULL) {
            int drivers_ahead = count_drivers_ahead_in_finals(
                race, piece_a, piece_a_index, driver_a
            );
            driver_a->place = drivers_ahead + 1;
            driver_a = driver_a->next;
        }
        piece_a = piece_a->next;
        piece_a_index++;
    }
}

// Updates the places for normal races
// Params: *race - pointer to race to update
// Returns: none
void update_non_finals_places(struct race *race) {
    int driver_count = count_drivers(race);
    struct track_piece *current_track = race->track;
    while (current_track != NULL) {
        int track_driver_count = 0;
        struct driver *current_driver = current_track->drivers;
        while (current_driver != NULL) {
            track_driver_count++;
            current_driver = current_driver->next;
        }
        current_driver = current_track->drivers;
        for (int i = 1; current_driver != NULL; i++) {
            current_driver->place = driver_count + i - track_driver_count;
            current_driver = current_driver->next;
        }
        driver_count -= track_driver_count;
        current_track = current_track->next;
    }
}


// Handler for updating driver places
// Params: *race - pointer to race to update
// Returns: none
void update_places(struct race *race) {

    if (race->is_finals == TRUE && race->status == ACTIVE) {
        update_finals_places(race);
        return;
    }
    update_non_finals_places(race);
}

// Handler for checking if mystery boxes are in play and operating them
// Params: *race - pointer to race to check
// Returns: none
void check_mystery_boxes(struct race *race) {
    int total_drivers = count_drivers(race);
    if (total_drivers == 0) {
        return;
    }

    update_places(race);
    for (int place = 1; place <= total_drivers; place++) {
        struct track_piece *piece = find_track_by_place(race, place);
        if (piece != NULL && piece->type == MYSTERY_BOX) {
            apply_mystery_boxes(race, place);
            update_places(race);
        }
    }
}

// Applies mystery boxes, called in check_mystery_boxes
// Params:
//      *race - pointer to race to apply mystery boxes
//      mb_driver_place - the place of the driver relative to 
//                        other mystery box drivers
// Returns:
//      none
void apply_mystery_boxes(struct race *race, int mb_driver_place) {
    struct driver *mb_driver = find_driver_by_place(race, mb_driver_place);
    struct track_piece *mb_piece = find_track_by_place(race, mb_driver_place);
    if (
        mb_driver == NULL ||
        mb_piece == NULL ||
        mb_piece->type != MYSTERY_BOX
    ) {
        return;
    }

    if (mb_driver->invincible == TRUE) {
        mb_driver->invincible = FALSE;
    }

    int attempts = BULLET + 1;
    while (attempts > 0) {
        int applied = FALSE;

        if (race->next_mystery_box == MUSHROOM) {
            applied = mb_apply_mushroom(race, mb_driver);
        } else if (race->next_mystery_box == BANANA_PEEL) {
            applied = mb_apply_banana(race, mb_driver);
        } else if (race->next_mystery_box == STAR) {
            applied = mb_apply_star(race, mb_driver);
        } else if (race->next_mystery_box == LIGHTNING) {
            applied = mb_apply_lightning(race, mb_driver);
        } else if (race->next_mystery_box == BLUE_SHELL) {
            applied = mb_apply_blue_shell(race, mb_driver);
        } else if (race->next_mystery_box == BULLET) {
            applied = mb_apply_bullet(race, mb_driver);
        }

        race->next_mystery_box++;
        if (race->next_mystery_box == NO_MYSTERY_BOX) {
            race->next_mystery_box = MUSHROOM;
        }

        if (applied) {
            return;
        }
        attempts--;
    }
}

// Counts only drivers who have not finished yet
// Params: *race - pointer to race to count
// Returns: int - number of drivers who are yet to finish
int count_active_drivers(struct race *race) {
    int count = 0;
    struct track_piece *piece = race->track;
    while (piece != NULL) {
        if (piece->type != FINISH_LINE) {
            struct driver *driver = piece->drivers;
            while (driver != NULL) {
                count++;
                driver = driver->next;
            }
        }
        piece = piece->next;
    }
    return count;
}

// Return the overall place for a given active driver.
// Params:
//      *race - pointer to race
//      active_rank - the placement of active drivers
// Returns:
//      int - the overall placement of the driver
int active_rank_to_overall_place(struct race *race, int active_rank) {
    int total = count_drivers(race);
    int active_seen = 0;
    for (int place = 1; place <= total; place++) {
        struct track_piece *piece = find_track_by_place(race, place);
        if (piece != NULL && piece->type != FINISH_LINE) {
            active_seen++;
            if (active_seen == active_rank) {
                return place;
            }
        }
    }
    return -1;
}

// Opposite to previous function
// Params:
//      *race - pointer to race
//      overall_place - the overall placement of a driver
// Returns:
//      int - the placement relative to active drivers
int overall_place_to_active_rank(struct race *race, int overall_place) {
    int total = count_drivers(race);
    int active_seen = 0;
    for (int place = 1; place <= total; place++) {
        struct track_piece *piece = find_track_by_place(race, place);
        if (piece != NULL && piece->type != FINISH_LINE) {
            active_seen++;
            if (place == overall_place) {
                return active_seen;
            }
        }
    }
    return -1;
}

// Applies mushroom power-up to a driver
// Params:
//      *race - pointer to race
//      *mb_driver - pointer to driver to apply mushroom to
// Returns:
//      int - TRUE if successful, FALSE otherwise (placeholder in this case)
int mb_apply_mushroom(struct race *race, struct driver *mb_driver) {
    mb_driver->speed++;
    if (mb_driver->speed > MAX_SPEED) {
        mb_driver->speed = MAX_SPEED;
    }
    printf("Mushroom power-up applied by %s!\n", mb_driver->name);
    return TRUE;
}

// Applies banana peel power-up to a driver
// Params:
//      *race - pointer to race
//      *mb_driver - pointer to driver to apply banana peel to
// Returns:
//      int - TRUE if successful, FALSE otherwise
int mb_apply_banana(struct race *race, struct driver *mb_driver) {
    int active_rank = overall_place_to_active_rank(race, mb_driver->place);
    int active_total = count_active_drivers(race);

    if (active_rank != -1 && active_rank < active_total) {
        int behind_place = active_rank_to_overall_place(race, active_rank + 1);
        struct driver *one_behind = find_driver_by_place(race, behind_place);

        if (one_behind != NULL) {
            if (one_behind->invincible == TRUE) {
                one_behind->invincible = FALSE;
            } else if (one_behind->speed > MIN_SPEED) {
                one_behind->speed--;
            }
            if (one_behind->speed < MIN_SPEED) {
                one_behind->speed = MIN_SPEED;
            }
        }
    }
    printf("Banana peel power-up applied by %s!\n", mb_driver->name);
    return TRUE;
}

// Applies star power-up to a driver
// Params:
//      *race - pointer to race
//      *mb_driver - pointer to driver to apply star to
// Returns:
//      int - TRUE if successful, FALSE otherwise (placeholder in this case)
int mb_apply_star(struct race *race, struct driver *mb_driver) {
    mb_driver->invincible = TRUE;
    printf("Star power-up applied by %s!\n", mb_driver->name);
    return TRUE;
}

// Checks if a star is active, and a victim has enough speed
// Params:
//      *current_driver - pointer to iterating driver
//      *mb_driver - pointer to driver that activated the power-up
// Returns:
//      none
void check_star_and_speed(
    struct driver *current_driver,
    struct driver *mb_driver
) {
    if (current_driver != mb_driver) {
        if (current_driver->invincible == TRUE) {
            current_driver->invincible = FALSE;
        } else if (current_driver->speed > MIN_SPEED) {
            current_driver->speed--;
        }
        if (current_driver->speed < MIN_SPEED) {
            current_driver->speed = MIN_SPEED;
        }
    }
}

// Applies lightning power-up to other drivers
// Params:
//      *race - pointer to race
//      *mb_driver - pointer to driver that activated the lightning
// Returns:
//      TRUE if lightning was successful, FALSE otherwise
int mb_apply_lightning(struct race *race, struct driver *mb_driver) {

    struct track_piece *current_track = race->track;
    while (current_track != NULL) {
        if (current_track->type == FINISH_LINE) {
            current_track = current_track->next;
            continue;
        }
        struct driver *current_driver = current_track->drivers;
        while (current_driver != NULL) {
            check_star_and_speed(current_driver, mb_driver);
            current_driver = current_driver->next;
        }
        current_track = current_track->next;
    }

    printf("Lightning power-up applied by %s!\n", mb_driver->name);
    return TRUE;
}

// Find the previous driver on a track piece
// Params:
//      *piece - pointer to track piece to check
//      *target - pointer to target driver
// Returns:
//      *driver - pointer to driver before target
struct driver *find_prev_driver_on_piece(
    struct track_piece *piece,
    struct driver *target
) {
    struct driver *prev = NULL;
    struct driver *cursor = piece->drivers;
    while (cursor != NULL && cursor != target) {
        prev = cursor;
        cursor = cursor->next;
    }
    return prev;
}

// Replaces a driver in the first position of a track
// Params:
//      *piece - pointer to track piece to swap on
//      *prev - pointer to previous driver
//      *replacement - pointer to replacement driver
// Returns:
//      none
void replace_driver_reference(
    struct track_piece *piece,
    struct driver *prev,
    struct driver *replacement
) {
    if (prev == NULL) {
        piece->drivers = replacement;
    } else {
        prev->next = replacement;
    }
}

// Swaps blue shell targets (position 1 and 2 in the race)
// Params:
//      *first_piece - pointer to piece that first place is on
//      *second_piece - pointer to piece that second place is on
//      *first_place - pointer to driver in first place
//      *second_place - pointer to driver in second place
// Returns:
//      none
void swap_blue_shell_targets(
    struct track_piece *first_piece,
    struct track_piece *second_piece,
    struct driver *first_place,
    struct driver *second_place
) {
    struct driver *first_prev =
        find_prev_driver_on_piece(first_piece, first_place);
    struct driver *second_prev =
        find_prev_driver_on_piece(second_piece, second_place);
    struct driver *first_next = first_place->next;
    struct driver *second_next = second_place->next;

    replace_driver_reference(first_piece, first_prev, second_place);
    replace_driver_reference(second_piece, second_prev, first_place);
    if (first_piece == second_piece && first_next == second_place) {
        first_place->next = second_next;
        second_place->next = first_place;
        return;
    }
    if (first_piece == second_piece && second_next == first_place) {
        second_place->next = first_next;
        first_place->next = second_place;
        return;
    }
    first_place->next = second_next;
    second_place->next = first_next;
}

// Applies blue shell to first and second place in the race
// Params:
//      *race - pointer to the race
//      *mb_driver - pointer to driver that activated the blue shell
// Returns:
//      TRUE if successful, FALSE otherwise
int mb_apply_blue_shell(struct race *race, struct driver *mb_driver) {
    int active_rank = overall_place_to_active_rank(race, mb_driver->place);
    int active_total = count_active_drivers(race);
    if (active_rank == -1 || active_total < 2 || active_rank == 1) {
        return FALSE;
    }

    int first_overall = active_rank_to_overall_place(race, 1);
    int second_overall = active_rank_to_overall_place(race, 2);
    struct driver *first_place = find_driver_by_place(race, first_overall);
    struct driver *second_place = find_driver_by_place(race, second_overall);
    struct track_piece *first_piece = find_track_by_place(race, first_overall);
    struct track_piece *second_piece = 
        find_track_by_place(race, second_overall);

    if (first_place == NULL || second_place == NULL ||
        first_piece == NULL || second_piece == NULL) {
        return FALSE;
    }

    if (first_place->invincible == TRUE) {
        first_place->invincible = FALSE;
        printf("Blue shell power-up applied by %s!\n", mb_driver->name);
        return TRUE;
    }

    swap_blue_shell_targets(
        first_piece,
        second_piece,
        first_place,
        second_place);

    printf("Blue shell power-up applied by %s!\n", mb_driver->name);
    return TRUE;
}

// Inserts a driver before a target on a piece
// Params:
//      *piece - pointer to piece that drivers are on
//      *target - pointer to driver to insert before
//      *driver_to_insert - pointer to driver to insert
// Returns:
//      none
void insert_driver_before_target(
    struct track_piece *piece,
    struct driver *target,
    struct driver *driver_to_insert
) {
    struct driver *target_prev = find_prev_driver_on_piece(piece, target);
    driver_to_insert->next = target;
    if (target_prev == NULL) {
        piece->drivers = driver_to_insert;
    } else {
        target_prev->next = driver_to_insert;
    }
}

// Applies the bullet power-up to a race
// Params:
//      *race - pointer to race
//      *mb_driver - pointer to driver that activated the bullet
// Returns:
//      int - TRUE if successful, FALSE otherwise
int mb_apply_bullet(struct race *race, struct driver *mb_driver) {
    int active_total = count_active_drivers(race);
    int active_rank = overall_place_to_active_rank(race, mb_driver->place);
    int min_bullet_active_rank = (active_total / 2) + 2;
    if (active_rank == -1 || active_rank < min_bullet_active_rank) {
        return FALSE;
    }
    int two_ahead_place = active_rank_to_overall_place(race, active_rank - 2);
    struct driver *two_ahead = find_driver_by_place(race, two_ahead_place);
    if (two_ahead == NULL) {
        return FALSE;
    }
    struct track_piece *mb_driver_piece =
        find_track_by_place(race, mb_driver->place);
    struct track_piece *two_ahead_piece =
        find_track_by_place(race, two_ahead_place);
    if (mb_driver_piece == NULL || two_ahead_piece == NULL) {
        return FALSE;
    }

    if (two_ahead->invincible == TRUE) {
        two_ahead->invincible = FALSE;
        printf("Bullet power-up applied by %s!\n", mb_driver->name);
        return TRUE;
    }

    struct driver *mb_prev =
        find_prev_driver_on_piece(mb_driver_piece, mb_driver);
    if (mb_prev == NULL) {
        mb_driver_piece->drivers = mb_driver->next;
    } else {
        mb_prev->next = mb_driver->next;
    }
    insert_driver_before_target(two_ahead_piece, two_ahead, mb_driver);

    printf("Bullet power-up applied by %s!\n", mb_driver->name);
    return TRUE;
}

// Helper function that searches for a race by a name and returns a pointer
// Params:
//      *series - pointer to the series
//      race_name - string of race name to search for
// Returns:
//      *race - pointer to race if found, else NULL
struct race *find_race_by_name(
    struct series *series,
    char race_name[MAX_SIZE]
) {

    if (series->races == NULL) {
        printf("ERROR: No race with name %s.\n", race_name);
        return NULL;
    }

    struct race *current_race = series->races;

    while (
        current_race != NULL &&
        strcmp(current_race->name, race_name) != 0
    ) {
        current_race = current_race->next;
    }

    if (current_race == NULL) {
        printf("ERROR: No race with name %s.\n", race_name);
        return NULL;
    } else {
        return current_race;
    }

}

// Helper function that searches for a driver by a name and returns a pointer
// Params:
//      *series - pointer to the series
//      driver_name - string of driver name to search for
// Returns:
//      *driver - pointer to race if found, else NULL
struct driver *find_driver_by_name(
    struct race *race,
    char driver_name[MAX_SIZE]
) {

    if (race->drivers == NULL) {
        printf("ERROR: No drivers in race %s.\n", race->name);
        return NULL;
    }

    struct driver *current_driver = race->drivers;

    while (
        current_driver != NULL &&
        strcmp(current_driver->name, driver_name) != 0
    ) {
        current_driver = current_driver->next;
    }

    if (current_driver == NULL) {
        printf("ERROR: Driver %s not found in race %s.\n",
               driver_name, race->name);
        return NULL;
    } else {
        return current_driver;
    }
}

// Helper function that finds a driver by their place in the race
// Params:
//      *race - pointer to the race to search in
//      place - the place to find
// Returns:
//      *driver - pointer to the driver at the by place,
//                or NULL if doesn't exist
struct driver *find_driver_by_place(struct race *race, int place) {
    
    struct track_piece *current_track = race->track;
    struct driver *found_driver = NULL;
    while (current_track != NULL) {
        struct driver *current_driver = current_track->drivers;
        while (current_driver != NULL) {
            if (current_driver->place == place) {
                found_driver = current_driver;
            }
            current_driver = current_driver->next;
        }
        current_track = current_track->next;
    }
    return found_driver;
}

// Helper function that finds the track piece a driver place is on
// Params:
//      *race - pointer to the race to search
//      place - int of the place to search for
// Returns:
//      *track - pointer to the track piece with the driver
struct track_piece *find_track_by_place(struct race *race, int place) {
    struct track_piece *current_track = race->track;

    while (current_track != NULL) {
        struct driver *current_driver = current_track->drivers;
        while (current_driver != NULL) {
            if (current_driver->place == place) {
                return current_track;
            } else {
                current_driver = current_driver->next;
            }
        }
        current_track = current_track->next;
    }
    return NULL;
}

// Check whether or not a race has started
// Params:
//      race - a pointer to the race to check
// Returns:
//      TRUE if race already started, FALSE if race no started
int is_race_not_started(struct race *race) {
    if (race->status != NOT_STARTED) {
        printf("ERROR: Race %s has already started.\n", race->name);
        return TRUE;
    } else {
        return FALSE;
    }
}

// Check whether or not a race has finished
// Params:
//      race - a pointer to the race to check
// Returns:
//      TRUE if a race is finished, FALSE if it hasn't
int is_race_completed(struct race *race) {
    if (race->is_finals == TRUE) {
        struct track_piece *track = race->track;
        while (track != NULL) {
            if (track->type != FINISH_LINE && track->drivers != NULL) {
                return FALSE;
            }
            track = track->next;
        }

        struct track_piece *finish = race->track;
        while (finish != NULL && finish->type != FINISH_LINE) {
            finish = finish->next;
        }
        if (finish == NULL) {
            return FALSE;
        }

        struct driver *driver = finish->drivers;
        while (driver != NULL) {
            if (driver->laps_completed < 3) {
                return FALSE;
            }
            driver = driver->next;
        }
        return TRUE;
    }

    struct track_piece *current_track = race->track;

    while (current_track->next != NULL && current_track->type != FINISH_LINE) {
        struct driver *current_driver = current_track->drivers;
        if (current_driver != NULL) {
            return FALSE;
        }
        current_track = current_track->next;
    }
    return TRUE;
}

// Function to count the number of drivers in a race
// Params:
//      race - a pointer to the race
// Returns: the number of drivers in the race
int count_drivers(struct race *race) {
    
    if (race == NULL) {
        return 0;
    }
    
    int driver_count = 0;
    
    if (race->status == NOT_STARTED) {
        // Count drivers in the waiting list
        struct driver *current = race->drivers;
        while (current != NULL) {
            driver_count++;
            current = current->next;
        }
    } else if (race->status == ACTIVE) {
        // Count drivers on all track pieces
        struct track_piece *current_track = race->track;
        while (current_track != NULL) {
            struct driver *current_driver = current_track->drivers;
            while (current_driver != NULL) {
                driver_count++;
                current_driver = current_driver->next;
            }
            current_track = current_track->next;
        }
    } else if (race->status == COMPLETED) {
        struct driver *current_driver = race->drivers;
        while (current_driver != NULL) {
            driver_count++;
            current_driver = current_driver->next;
        }
    }
    return driver_count;
}

// Helper function that returns the place of the leading active driver
// Params:
//      *race - pointer to race to look through
// Returns:
//      place - int of the leading active driver
int first_active_place(struct race *race) {

    struct track_piece *current_track = race->track;
    struct driver *first_active = NULL;
    while (current_track != NULL) {
        current_track = current_track->next;
        if (current_track->drivers != NULL) {
            first_active = current_track->drivers;
        }
    }
    return first_active->place;
}

// Stage 1.4
// Function to print out the racing series
// Params:
//      series - a pointer to the racing series
// Returns: None
void print_series(struct series *series) {

    printf("===================[ %s ]===================\n", series->name);

    if (series->races == NULL) {
        printf("The racing series is empty!\n");
        return;
    }
    
    printf("Races:\n");
    
    // Iterate through races
    struct race *current_race = series->races;
    while (current_race != NULL) {
        int driver_place = count_drivers(current_race);
        printf("    %s [%s]\n",
                current_race->name, status_to_string(current_race->status));
        printf("    (%s)\n", location_to_string(current_race->location));
        print_track(current_race->track, &driver_place);
        print_drivers(current_race);
        current_race = current_race->next;
    }
    printf("\n");
    
    return;
}

///////////////////////////////////////////////////////////////////////////////
// Provided function definitions
////////////////////////////////////////////////////////////////////////////////

// Function to print the program usage information
// Params: None
// Returns: None
void print_usage() {

    printf(
       "======================[ Usage Info ]=====================\n"
       "                                                         \n"
       "  ?                                                      \n"
       "    Show this help information.                          \n"
       "  a r [race_name] [location]                             \n"
       "    Add a new race with the given name and location.     \n"
       "  a t [race_name] [piece_type]                           \n"
       "    Add a track piece of the given type to the race.     \n"
       "  a d [race_name] [driver_name] [speed]                  \n"
       "    Add a driver to the specified race.                  \n"
       "  *                                                      \n"
       "    Print the racing series.                             \n"
       "  i t [n] [race_name] [piece_type]                       \n"
       "    Insert a track piece at position [n] in the race.    \n"
       "  i d [n] [race_name] [driver_name] [speed]              \n"
       "    Insert a driver at [position] in the specified race. \n"
       "  c [existing_race] [new_race]                           \n"
       "    Adds a new race with the same track layout.          \n"
       "  s [race_name]                                          \n"
       "    Start the specified race.                            \n"
       "  v [race_name]                                          \n"
       "    Validates the specified rules meets track compliance.\n"
       "  m [driver_name] [current_race] [new_race]              \n"
       "    Moves the driver from one race to another.           \n"
       "  q                                                      \n"
       "    Cancels the karting series.                          \n"
       "  r [driver_name]                                        \n"
       "    Removes the driver from all races.                   \n"
       "  t [race_name] [turns]                                  \n"
       "    Advance the race by [turns].                         \n"
       "  e [race_name]                                          \n"
       "    Automatically run turns until the race finishes.     \n"
       "  f [location]                                           \n"
       "    Create a finals race for the given location.         \n"
       "                                                         \n"
       "=========================================================\n"
    );

}

// Function to print the welcome banner
// Params: None
// Returns: None
void print_welcome_banner() {

    printf(""
    "          Welcome to the CS Karting Racing Series!\n"
    "                  .\n"
    "                  |\\\n"
    "                  |_\\\n"
    "                  |\n"
    "       .==========||=======.    .===================.\n"
    "      /    _______||____    \\  /   _[_0|_[?]_______   \\\n"
    "     /   /'              '\\  \\/  /'               '\\   \\\n"
    "    |   |                  \\/   /                   |   |\n"
    "    |   |                  /   / \\                  |   |\n"
    "     \\  \\                 /   /\\  \\                /   /\n"
    "      \\  '---------------'   /  \\  '--------------'   /\n"
    "       \\.===[_0|====[_0|===./    \\.========|0_]=====./\n"
    "\n"
    );

}

// Helper function to print drivers per track
// Params:
//      *driver - pointer to driver to print
//      place - int driver place
// Returns:
//      none
void print_track_driver(struct driver *driver, int place){
    if (driver->place == place) {
        printf("        %d. %s\n",
            driver->place, driver->name);
    }
}

// Helper function to print out the track information
// PARAMS:
//      track - the first track piece in a by race
//      *driver_place - int for driver place
// RETURNS: None
void print_track(struct track_piece *track, int *driver_place) {

    if (track == NULL) {
        printf("        Empty Track!\n");
        return;
    }

    while (track->next != NULL) {
        printf("        %s\n", type_to_string(track->type));

        for (int place = 1; place <= MAX_DRIVERS; place++) {
            struct driver *current_driver = track->drivers;
            while (current_driver != NULL) {
                print_track_driver(current_driver, place);
                current_driver = current_driver->next;
            }
        }

        if (track->next != NULL) {
            printf("        |\n");
            printf("        ⌄\n");
        }

        track = track->next;
    }
    printf("        %s\n", type_to_string(track->type));

    // Print drivers on the final track piece (e.g. FINISH_LINE).
    int count = 0;
    for (
        struct driver *current_driver = track->drivers;
    current_driver != NULL;
    current_driver = current_driver->next
    ) {
        count++;
    }

    if (count > 0) {
        for (int place = 1; place <= MAX_DRIVERS; place++) {
            struct driver *current_driver = track->drivers;
            while (current_driver != NULL) {
                print_track_driver(current_driver, place);
                current_driver = current_driver->next;
            }
        }
    }
}

// Helper function to print out the drivers within a race
// PARAMS:
//      race - the race containing the drivers to be printed
// RETURNS: None
void print_drivers(struct race *race) {

    printf("        Drivers:\n");

    if (race->status == NOT_STARTED) {
        struct driver *current = race->drivers;
        if (current == NULL) {
            printf("            Empty Driver List!\n");
        }

        int count = 1;
        while (current != NULL) {
            printf("            %d. %s (speed: %d)\n", 
                   count, current->name, current->speed);
            count++;
            current = current->next;
        }
    } else if (race->status == ACTIVE) {
        int total_drivers = count_drivers(race);

        if (total_drivers == 0) {
            printf("            Empty Driver List!\n");
            return;
        }

        for (int place = 1; place <= total_drivers; place++) {
            struct driver *current_driver = find_driver_by_place(race, place);
            if (current_driver != NULL) {
                printf("            %d. %s (speed: %d)\n",
                       place, current_driver->name, current_driver->speed);
            }
        }

    } else if (race->status == COMPLETED) {
        struct driver *current = race->drivers;
        int count = 1;
        while (current != NULL) {
            printf("            %d. %s (speed: %d)\n", 
                   count, current->name, current->speed);
            count++;
            current = current->next;
        }

    }
}

// Scan in the a name string into the provided buffer, placing
// '\0' at the end.
//
// Params:
//      name - a char array of length MAX_SIZE, which will be used
//                  to store the name.
// Returns: None
// Usage:
// ```
//      char name[MAX_SIZE];
//      scan_name(name);
// ```
void scan_name(char name[MAX_SIZE]) {
    scan_token(name, MAX_SIZE);
}

// Scans a string and converts it to a location.
//
// Returns:
//      The corresponding location, if the string was valid,
//      Otherwise, returns INVALID.
//
// Usage:
// ```
//      enum location location = scan_location();
// ```
//
enum location scan_location(void) {
    char type[MAX_SIZE];
    scan_token(type, MAX_SIZE);
    return string_to_location(type);
}

// Scans a string and converts it to a location.
//
// Returns:
//      The corresponding pieve_type, if the string was valid,
//      Otherwise, returns INVALID.
//
// Usage:
// ```
//      enum piece_type type = scan_location();
// ```
//
enum piece_type scan_piece_type(void) {
    char type[MAX_SIZE];
    scan_token(type, MAX_SIZE);
    return string_to_type(type);
}

////////////////////////////////////////////////////////////////////////////////
// Additional provided function definitions
////////////////////////////////////////////////////////////////////////////////

// You don't need to use any of these, or understand how they work!
// We use them to implement some of the provided helper functions.

enum points place_to_points(int place) {
    if (place == 1) {
        return FIRST;
    }
    if (place == 2) {
        return SECOND;
    }
    if (place == 3) {
        return THIRD;
    }
    if (place == 4) {
        return FOURTH;
    }
    if (place == 5) {
        return FIFTH;
    }
    if (place == 6) {
        return SIXTH;
    }
    if (place == 7) {
        return SEVENTH;
    } else {
        return EIGHTH;
    }
}

enum location string_to_location(char *type_str) {
    int len = strlen(type_str);

    if (strncasecmp(type_str, "ALBERT_PARK", len) == 0) {
        return ALBERT_PARK;
    }
    if (strncasecmp(type_str, "MARINA_BAY", len) == 0) {
        return MARINA_BAY;
    }
    if (strncasecmp(type_str, "MONZA", len) == 0) {
        return MONZA;
    }
    if (strncasecmp(type_str, "SUZUKA", len) == 0) {
        return SUZUKA;
    } else {
        return ZANDVOORT;
    }
}

char *location_to_string(enum location location) {

    if (location == ALBERT_PARK) {
        return "ALBERT_PARK";
    }
    if (location == MARINA_BAY) {
        return "MARINA_BAY";
    }
    if (location == MONZA) {
        return "MONZA";
    }
    if (location == SUZUKA) {
        return "SUZUKA";
    } else  {
        return "ZANDVOORT";
    }

}
enum piece_type string_to_type(char *type_str) {
    int len = strlen(type_str);

    if (strncasecmp(type_str, "START_LINE", len) == 0) {
        return START_LINE;
    }
    if (strncasecmp(type_str, "FINISH_LINE", len) == 0) {
        return FINISH_LINE;
    }
    if (strncasecmp(type_str, "STRAIGHT", len) == 0) {
        return STRAIGHT;
    }
    if (strncasecmp(type_str, "LEFT_TURN", len) == 0) {
        return LEFT_TURN;
    }
    if (strncasecmp(type_str, "RIGHT_TURN", len) == 0) {
        return RIGHT_TURN;
    }
    if (strncasecmp(type_str, "JUMP", len) == 0) {
        return JUMP;
    }
    if (strncasecmp(type_str, "MYSTERY_BOX", len) == 0) {
        return MYSTERY_BOX;
    }

    return -1;
}

char *type_to_string(enum piece_type type) {
    if (type == START_LINE) {
        return "START_LINE";
    }
    if (type == FINISH_LINE) {
        return "FINISH_LINE";
    }
    if (type == STRAIGHT) {
        return "STRAIGHT";
    }
    if (type == LEFT_TURN) {
        return "LEFT_TURN";
    }
    if (type == RIGHT_TURN) {
        return "RIGHT_TURN";
    }
    if (type == JUMP) {
        return "JUMP";
    }
    if (type == MYSTERY_BOX) {
        return "MYSTERY_BOX";
    }
    return "INVALID";
}

char *status_to_string(enum race_status status) {
    
    if (status == NOT_STARTED) {
        return "NOT_STARTED";
    } else if (status == ACTIVE) {
        return "ACTIVE";
    } else {
        return "COMPLETED";
    }

}

int scan_token(char *buffer, int buffer_size) {
    if (buffer_size == 0) {
        return 0;
    }

    char c;
    int i = 0;
    int num_scanned = 0;

    scanf(" ");

    while (i < buffer_size - 1 && (num_scanned = scanf("%c", &c)) == 1 &&
           !isspace(c)) {
        buffer[i++] = c;
    }

    if (i > 0) {
        buffer[i] = '\0';
    }

    return num_scanned;
}
