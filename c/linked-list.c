#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "emalloc.h"
#include "linked-list.h"

node_t *new_node(char *text) {
    assert( text != NULL);

    node_t *temp = (node_t *)emalloc(sizeof(node_t));

    strncpy(temp->text, text, LIST_MAXLEN_TEXT);
    temp->next = NULL;

    return temp;
}


node_t *add_front(node_t *list, node_t *new) {
    new->next = list;
    return new;
}


node_t *add_end(node_t *list, node_t *new) {
    node_t *curr;

    if (list == NULL) {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new;
    new->next = NULL;
    return list;
}

/*
A function that adds the node new is pointing to to the linked list, in lexicographic order.
*/
node_t *add_inorder(node_t *list, node_t *new) {
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (list == NULL) {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next) {
        if (strcmp(new->text, curr->text) > 0) {
            prev = curr;
        } else {
            break;
        }
    }

    new->next = curr;

    if (prev == NULL) {
        return (new);
    } else {
        prev->next = new;
        return list;
    }
}

node_t *peek_front(node_t *list) {
    return list;
}


node_t *remove_front(node_t *list) {
    if (list == NULL) {
        return NULL;
    }

    return list->next;
}

/*
A function that checks to see if the linked list contains a node that has the given word,
returning 1 if it is found and 0 if it is not.
*/
int has_word(node_t *list, char *word) {
    node_t *curr = NULL;
    char copy[LIST_MAXLEN_TEXT];
    char *t;
    char *saveptr2;

    for (curr = list; curr != NULL; curr = curr->next) {
        strncpy(copy, curr->text, LIST_MAXLEN_TEXT);
        t = strtok_r(copy, " ", &saveptr2);
        while (t) {
            lowercase(t);
            if (strcmp(word, t) == 0) {
                return 1;
            }
            t = strtok_r(NULL, " ", &saveptr2);
        }        
    }
    return 0;
}

/*
A function that lowercases the word passed in
*/
void lowercase(char word[MAX_WORD_LENGTH]) {
    int i;
    
    for (i = 0; i < strlen(word); i++) {
        word[i] = tolower(word[i]);
    }
}

void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for ( ; list != NULL; list = list->next) {
        (*fn)(list, arg);
    }
}
