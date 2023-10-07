#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>
#include "Position.h"
#include <stdbool.h>

typedef struct position Position;

typedef struct Node{
    Position data;
    struct Node* next;
} Node;

typedef struct linkedList{
    Node* head;
    Node* tail;
    size_t len;
} LinkedList; 


LinkedList* LinkedList_construct();
int LinkedList_append(LinkedList*, Position);
int LinkedList_appendXY(LinkedList*, int, int);
int LinkedList_appendHead(LinkedList*, Position);
int LinkedList_pop(LinkedList*);
Position LinkedList_get(LinkedList*, int);
bool LinkedList_isPosInList(LinkedList* l, Position position);
void LinkedList_popHead(LinkedList*);
int LinkedList_destruct(LinkedList*);

#endif