#include <stdio.h>
#include "cs_karting.h"

void debug_print_arrays(struct driver *driver_arr[], int driver_arr_len,
                        struct driver *mb_driver_arr[], int mb_driver_arr_len) {
    printf("\n");
    printf("  ── driver_arr (all drivers, best to worst place) ──────\n");
    if (driver_arr_len == 0) {
        printf("    [empty]\n");
    } else {
        for (int i = 0; i < driver_arr_len; i++) {
            struct driver *d = driver_arr[i];
            if (d == NULL) {
                printf("    [%2d] (NULL)\n", i);
            } else {
                printf("    [%2d] %-16s  speed: %d  place: %d%s\n",
                       i, d->name, d->speed, d->place,
                       d->invincible ? "  [INVINCIBLE]" : "");
            }
        }
    }
    printf("\n");
    printf("  ── mb_driver_arr (mystery box drivers this turn) ───────\n");
    if (mb_driver_arr_len == 0) {
        printf("    [empty]\n");
    } else {
        for (int i = 0; i < mb_driver_arr_len; i++) {
            struct driver *d = mb_driver_arr[i];
            if (d == NULL) {
                printf("    [%2d] (NULL)\n", i);
            } else {
                printf("    [%2d] %-16s  speed: %d  place: %d\n",
                       i, d->name, d->speed, d->place);
            }
        }
    }
    printf("  ────────────────────────────────────────────────────────\n\n");
}

// Prints all debug information about the entire racing series,
// including every race, its track layout, and the position of every driver.
void debug_print(struct series *series) {
    printf("\n");
    printf("========================================================\n");
    printf("  DEBUG PRINT: %s\n", series->name);
    printf("========================================================\n");
    if (series->races == NULL) {
        printf("  [No races in series]\n");
        printf("========================================================\n\n");
        return;
    }
    struct race *current_race = series->races;
    int race_num = 1;
    while (current_race != NULL) {
        printf("\n");
        printf("  Race #%d: \"%s\"\n", race_num, current_race->name);
        printf("  Location : %s\n", location_to_string(current_race->location));
        printf("  Status   : %s\n", status_to_string(current_race->status));
        printf("\n");
        if (current_race->status == NOT_STARTED) {
            printf("  [Track not yet built — race has not started]\n");
        } else {
            printf("  Track:\n");
            struct track_piece *piece = current_race->track;
            int piece_num = 0;
            while (piece != NULL) {
                printf("    [%2d] %-12s", piece_num, type_to_string(piece->type));
                if (piece->drivers == NULL) {
                    printf("  (empty)\n");
                } else {
                    struct driver *d = piece->drivers;
                    printf("  drivers:\n");
                    while (d != NULL) {
                        printf("           %*s  -> %s  (speed: %d, place: %d)\n",
                               14, "", d->name, d->speed, d->place);
                        d = d->next;
                    }
                }
                piece = piece->next;
                piece_num++;
            }
        }
        if (current_race->status == NOT_STARTED) {
            printf("\n  Drivers (waiting):\n");
            if (current_race->drivers == NULL) {
                printf("    [none]\n");
            } else {
                struct driver *d = current_race->drivers;
                int idx = 1;
                while (d != NULL) {
                    printf("    %2d. %-16s speed: %d\n", idx, d->name, d->speed);
                    d = d->next;
                    idx++;
                }
            }
        }
        if (current_race->status == COMPLETED) {
            printf("\n  Final Results:\n");
            if (current_race->drivers == NULL) {
                printf("    [no results recorded]\n");
            } else {
                struct driver *d = current_race->drivers;
                int place = 1;
                while (d != NULL) {
                    printf("    %2d. %-16s speed: %d  points: %d\n",
                           place, d->name, d->speed, place_to_points(place));
                    d = d->next;
                    place++;
                }
            }
        }
        printf("\n  --------------------------------------------------------\n");
        current_race = current_race->next;
        race_num++;
    }
    printf("========================================================\n\n");
}
