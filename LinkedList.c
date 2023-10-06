#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"
#include <stdbool.h>

int LinkedList_append(LinkedList* ll, Position pos) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = pos;
    if (ll->len == 0) {
        ll->head = newNode;
        ll->tail = ll->head;
    }
    else {
        Node* oldTail = ll->tail;
        ll->tail->next = newNode;
        ll->tail = oldTail->next;
    }
    
    ll->len++;
    return 0;
}

int LinkedList_appendXY(LinkedList* ll, int x, int y) {
    Position pos = {x, y};
    return LinkedList_append(ll, pos);
}

int LinkedList_appendHead(LinkedList* ll, Position pos) {
    Node* newNode = (Node* ) malloc (sizeof(Node));
    newNode->data = pos;
    if (ll->len == 0) {
        ll->head = newNode;
        ll->tail = newNode;
    }
    else {
        newNode->next = ll->head;
        ll->head = newNode;
    }

    ll->len++;
    return 0;
}

int LinkedList_pop(LinkedList* ll) {
    if (ll->len == 0) {
        return -1;
    }
    if (ll->len == 1) {
        ll->head = NULL;
        ll->tail = NULL;
        ll->len--;
        return 0;
    }
    
    Node* deletedTail = ll->tail;
    Node* replacementTail;
    Node* helper = ll->head;
    while (helper->next != ll->tail) {
        helper = helper->next;
    }
    replacementTail = helper;
    replacementTail->next = NULL;
    ll->tail = replacementTail;
    free(deletedTail);
    ll->len--;
    return 0;
}

Position LinkedList_get(LinkedList* ll, int index) {
    Position pos = {-1, -1};
    bool isError = false;
    isError = isError || (index < 0);
    isError = isError || (index >= ll->len);
    if (isError) {
        return pos;
    }
    Node* helper = ll->head;
    for (int i = 0 ; i < index; i++) {
        helper = helper->next;
    }
    pos = helper->data;
    return pos;
}

bool LinkedList_isPosInList(LinkedList* l, Position position) {
    Node *helper = l->head;
    Position found ;
    for (int i = 0;i < l->len; i++ ) {
        found = LinkedList_get(l, i);
        if (found.x == position.x &&
            found.y == position.y)
            {
                return true;
                break;
            }
    }
    return false;
}

LinkedList* LinkedList_construct() {
    LinkedList* ll = (LinkedList*) malloc(sizeof(LinkedList)) ;
    ll->head = NULL;
    ll->tail = NULL;
    ll->len = 0;
    return ll;
}

int LinkedList_destruct(LinkedList* ll) {
    while (ll->len != 0) {
        LinkedList_pop(ll);
    }
    free(ll);
}

