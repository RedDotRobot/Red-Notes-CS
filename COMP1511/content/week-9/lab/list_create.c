// Create a list from Command Line Arguments
// list_create.c
//
// This program was written by LUCAS CHEUNG (z5763342)
// on 15-04-2026
//
// A program which creates and prints a linked list 
// from command line arguments!

#include <stdio.h>
#include <stdlib.h>

struct node {
    char *data;
    struct node *next;
};

struct node *arguments_to_list(int argc, char *argv[]);
void free_list(struct node *head);
void print_list(struct node *head);

int main(int argc, char **argv) {
    struct node *head = arguments_to_list(argc, argv);
    print_list(head);
    free_list(head);

    return 0;
}

// Create linked list from argument values
struct node *arguments_to_list(int argc, char *argv[]) {
    if (argc == 1) {
        return NULL;
    }

    struct node *head = malloc(sizeof(struct node));
    head->data = argv[1];
    head->next = NULL;

    struct node *current = head;
    for (int i = 2; i < argc; i++) {
        struct node *new_node = malloc(sizeof(struct node));
        current->next = new_node;
        new_node->data = argv[i];
        new_node->next = NULL;
        current = new_node;
    }
    return head;
}

// Free the linked list from memory
void free_list(struct node *head) {
    struct node *current = head;

    if (current == NULL) {
        return;
    }

    while (current != NULL) {
        struct node *next = current->next;
        free(current);
        current = next;
    }
}

// Print the values of the linked list
void print_list(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%s -> ", current->data);
        current = current->next;
    }
    printf("X\n");
}
