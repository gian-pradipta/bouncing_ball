#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>


typedef struct position {
    int y;
    int x;
} Position;

typedef struct Node{
    Position data;
    struct Node* next;
} Node;

typedef struct linkedList{
    Node* head;
    Node* tail;
    size_t len;
} LinkedList; 


int LinkedList_append(LinkedList*, Position);
int LinkedList_appendXY(LinkedList*, int, int);
int LinkedList_appendHead(LinkedList*, Position);
int LinkedList_pop(LinkedList*);
Position LinkedList_get(LinkedList*, int);
LinkedList* LinkedList_construct();
int LinkedList_destruct(LinkedList*);

#endif