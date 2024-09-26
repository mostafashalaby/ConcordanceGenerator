#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "seng265-list.h"

#define MAX_LINE_LENGTH 100
#define MAX_WORD_LENGTH 40

void print_word(node_t *, void *);
node_t* split_lines(FILE *);
node_t* get_keywords(node_t *, node_t *);
int length_of_keyword(node_t *);
void print_final(node_t *, node_t *);
void format_word(char *, int);
void free_list(node_t *);

int main(int argc, char *argv[]) {
    char *input_name;
    char *exclusion_name;
    int i;    
    FILE *file_handle;
    node_t *input_head = NULL;
    node_t *exclusion_head = NULL;
    node_t *keywords_head = NULL;  

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i+1 < argc) {
            exclusion_name = argv[++i];
        } else {
            input_name = argv[i];
        }
    }

    file_handle = fopen(input_name, "r");  
    if (file_handle == NULL) {
        fprintf(stderr, "unable to open %s\n", input_name);
        exit(1);
    }
    input_head = split_lines(file_handle);
    fclose(file_handle);

    if (argc == 4) {
        file_handle = fopen(exclusion_name, "r");
        if (file_handle == NULL) {
            fprintf(stderr, "unable to open %s\n", exclusion_name);
            exit(1);
        }     
        exclusion_head = split_lines(file_handle);
        fclose(file_handle);
    }
    
    keywords_head = get_keywords(input_head, exclusion_head);

    print_final(keywords_head, input_head);

    free_list(input_head);
    free_list(exclusion_head);
    free_list(keywords_head);
}

void print_word(node_t *node, void *arg) {
    char *format = (char *)arg;
    printf(format, node->text);
}

/*
A function that takes a pointer to some file, populating a linked list with its contents and
returning a pointer to the head of the linked list of type node_t.
*/
node_t* split_lines (FILE *file_handle) {
    node_t *head = NULL;
    node_t *temp = NULL;
    node_t *prev = NULL;
    node_t *next = NULL;
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, file_handle) != -1) {
        line[strlen(line)-1] = '\0';
        temp = new_node(line);
        head = add_front(head, temp); //O(1) operation, rather than add_back() which is O(n)
    }
    if (line) {
        free(line);
    }

    temp = head;
    while (temp != NULL) { //corrects the order of lines. While this loop is O(n), it is slightly better
        next = temp->next; //than adding to the back of the list each time.
        temp->next = prev;
        prev = temp;
        temp = next;
      }
    head = prev;
    
    return head;
}

/*
A function that takes:
- a pointer to the head of the linked list of input_head
- a pointer to the head of the linked list of exclusion_head
It then populates a linked list with the appropriate keywords and returns
the pointer to the head of that linked list.
*/
node_t* get_keywords(node_t *input_head, node_t *exclusion_head) {
    node_t *keywords_head = NULL;
    node_t *curr = NULL;
    node_t *temp = NULL;
    char copy[MAX_LINE_LENGTH];
    char *t;
    int in_exclusion;
    int in_keywords;
    char *saveptr1;
    
    for (curr = input_head; curr != NULL; curr = curr->next) {
        strncpy(copy, curr->text, MAX_LINE_LENGTH);
        t = strtok_r(copy, " ", &saveptr1);
        while (t) {
            lowercase(t); //lowercase() is in seng265-list.c
            in_exclusion = has_word(exclusion_head, t); //has_word() is in seng265-list.c
            in_keywords = has_word(keywords_head, t);
            if (!in_exclusion && !in_keywords) {
                temp = new_node(t);
                keywords_head = add_inorder(keywords_head, temp); //add_inorder() is in seng265-list.c
            }
            t = strtok_r(NULL, " ", &saveptr1);
        }
    }        
    return keywords_head;
}

/*
Helper function that returns the length all keywords should be when printed out
*/
int length_of_keyword(node_t *keywords_head) {
    node_t *curr = NULL;

    if (!keywords_head) {
        return 0;
    }
    int longest = strlen(keywords_head->text);

    for (curr = keywords_head; curr != NULL; curr = curr->next) {
        if (strlen(curr->text) > longest) {
            longest = strlen(curr->text);
        }
    }
    longest += 2;
    return longest;
}

/*
A function that prints the final output to the screen, as wanted
*/
void print_final(node_t *keywords_head, node_t *input_head) {
    node_t *curr_keyword = NULL;
    node_t *curr_line = NULL;
    char *t;
    char *word;
    char line[MAX_LINE_LENGTH];
    char word_copy[MAX_WORD_LENGTH];
    int found;
    int i;
    int wanted_length = length_of_keyword(keywords_head);
    
    for (curr_keyword = keywords_head; curr_keyword != NULL; curr_keyword = curr_keyword->next) {
        word = curr_keyword->text;
        i = 0;
        for (curr_line = input_head; curr_line != NULL; curr_line = curr_line->next) {
            i++;
            strncpy(line, curr_line->text, MAX_LINE_LENGTH);
            t = strtok(line, " ");
            found = 0;
            while (t) {
                lowercase(t);
                if (strcmp(word, t) == 0) {
                    found++;
                }
                t = strtok(NULL, " ");
            }
            if (found) {
                strncpy(word_copy, word, MAX_WORD_LENGTH);
                format_word(word_copy, wanted_length);
                if (found > 1) {
                    printf("%s%s (%d*)\n", word_copy, curr_line->text, i);
                }
                else {
                    printf("%s%s (%d)\n", word_copy, curr_line->text, i);
                }
            }
        }
    }
}

/*
Helper function that capitalizes the word and adds spaces as needed
*/
void format_word(char *word, int wanted_length) {
    int current_length = strlen(word);
    int i;
    
    for (i = 0; i < wanted_length; i++) {
        if (i < current_length) {
            word[i] = toupper(word[i]);
        } else {
            word[i] = ' ';
        }
    }
}

/*
A function that frees up the linked list headed at node_t *head
*/
void free_list(node_t *head) {
    node_t *curr = head;

    while (curr != NULL) {
        assert(curr != NULL);
        head = remove_front(head);
        free(curr);
        curr = head;
    }
   
    assert(head == NULL); 
}
