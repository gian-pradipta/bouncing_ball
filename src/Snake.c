#include "../include/LinkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

typedef struct snake{
    int uprbX;
    int uprbY;
    int lwrbX;
    int lwrbY;
    LinkedList* bodyparts;
    char direction;
} Snake;

Snake* Snake_construct(int upperBoundY, int lowerBoundY,int upperBoundX,int lowerBoundX) {
    srand(time(NULL));

    Snake* s = (Snake*) malloc(sizeof(Snake));
    s->bodyparts = LinkedList_construct();
    s->lwrbX = lowerBoundX;
    s->lwrbY = lowerBoundY;
    s->uprbX = upperBoundX;
    s->uprbY = upperBoundY;
    s->direction = 'd';
    return s;
}

void Snake_destruct (Snake* s) {
    LinkedList_destruct(s->bodyparts);
    free(s);
}

void Snake_changeDirection (Snake* s, char newDirection) {
    char oldDirection = s->direction;
    if (!(newDirection == 'w' ||
        newDirection == 'a' ||
        newDirection == 'd' ||
        newDirection == 's')) 
    {
        printf("%c",newDirection);
        return;
    }
    bool invalidChange = false;
    invalidChange = invalidChange || (oldDirection == 'w' && newDirection == 's');
    invalidChange = invalidChange || (oldDirection == 's' && newDirection == 'w');
    invalidChange = invalidChange || (oldDirection == 'a' && newDirection == 'd');
    invalidChange = invalidChange || (oldDirection == 'd' && newDirection == 'a');

    if (invalidChange) return ;
    s->direction = newDirection;

}


Position Snake_getNextHeadPosition(Snake* s, Position *pos) {
    if (s->direction == 'w') {
        pos->y--;
    }
    if (s->direction == 'd') {
        pos->x++;
    }
    if (s->direction == 'a') {
        pos->x--;
    }

    if (s->direction == 's') {
        pos->y++;
    }
    
}

void Snake_moveHeadNodeBefore(Snake* s) {
    Position oldPos;
    oldPos = s->bodyparts->head->data;
    if (s->direction == 'w') {
        s->bodyparts->head->data = s->bodyparts->head->next->data;
        s->bodyparts->head->data.y++;
    }
    if (s->direction == 's') {
        s->bodyparts->head->data = s->bodyparts->head->next->data;
        s->bodyparts->head->data.y++;
    }
}

void Snake_move (Snake* s) {
    LinkedList* body = s->bodyparts;
    Position oldHeadPosition = s->bodyparts->head->data;
    LinkedList_pop(body);
    Snake_getNextHeadPosition(s, &oldHeadPosition);
    LinkedList_appendHead(body, oldHeadPosition);
}

void Snake_turn(Snake* s, char newDirection) {
    Snake_changeDirection(s, newDirection);
    Snake_move(s);
}

LinkedList* Snake_getBody(Snake* s) {
    LinkedList_appendXY(s->bodyparts, s->uprbY/2, s->uprbX/2);
    LinkedList_appendXY(s->bodyparts, s->uprbY/2+1, s->uprbX/2);
    return s->bodyparts;
}




