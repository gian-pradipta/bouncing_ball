#include "LinkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "bouncingball.h"

typedef struct{
    int uprbX;
    int uprbY;
    int lwrbX;
    int lwrbY;
    LinkedList* bodyparts;
    char direction;
} Snake;

Snake* Snake_construct(int upperBoundY, int lowerBoundY,int upperBoundX,int lowerBoundX) {
    Snake* s = (Snake*) malloc(sizeof(Snake));
    s->bodyparts = LinkedList_construct();
    s->lwrbX = lowerBoundX;
    s->lwrbY = lowerBoundY;
    s->uprbX = upperBoundX;
    s->uprbY = upperBoundY;
    s->direction = 'd';
    return s;
}


void Snake_changeDirection (Snake* s, char userInput) {
    char oldDirection = s->direction;
    bool invalidChange = false;
    invalidChange = invalidChange || (oldDirection == 'w' && userInput == 's');
    invalidChange = invalidChange || (oldDirection == 'a' && userInput == 'd');

    if (invalidChange) return ;
    s->direction = userInput;

}

char Snake_getUserInputIfAny(Snake* s) {
    if (_kbhit()) {return _getch();}

    return s->direction;
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

void Snake_move (Snake* s) {
    LinkedList* body = s->bodyparts;
    Position oldHeadPosition = s->bodyparts->head->data;
    LinkedList_pop(body);
    Snake_getNextHeadPosition(s, &oldHeadPosition);
    LinkedList_appendHead(body, oldHeadPosition);
    char userInput = Snake_getUserInputIfAny(s);
    Snake_changeDirection(s, userInput);
}

LinkedList* Snake_getBody(Snake* s) {
    LinkedList_appendXY(s->bodyparts, s->uprbY/2, s->uprbX/2);
    LinkedList_appendXY(s->bodyparts, s->uprbY/2+1, s->uprbX/2);
    return s->bodyparts;
}
void Snake_eat (Snake* s) {
      
}
void Snake_hitWall (Snake* s) {
    
}
