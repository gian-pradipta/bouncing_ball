#include "LinkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "bouncingball.h"
#include <time.h>

typedef struct{
    int uprbX;
    int uprbY;
    int lwrbX;
    int lwrbY;
    LinkedList* bodyparts;
    char direction;
    Position foodPosition;
    int score ;
} Snake;

Snake* Snake_construct(int upperBoundY, int lowerBoundY,int upperBoundX,int lowerBoundX) {
    srand(time(NULL));

    Snake* s = (Snake*) malloc(sizeof(Snake));
    Position pos = {-1,-1};
    s->score = 0;
    s->bodyparts = LinkedList_construct();
    s->lwrbX = lowerBoundX;
    s->lwrbY = lowerBoundY;
    s->uprbX = upperBoundX;
    s->uprbY = upperBoundY;
    s->direction = 'd';
    s->foodPosition = pos;
    return s;
}

void Snake_destruct (Snake* s) {
    LinkedList_destruct(s->bodyparts);
    free(s);
}

void Snake_changeDirection (Snake* s, char userInput) {
    char oldDirection = s->direction;
    bool invalidChange = false;
    invalidChange = invalidChange || (oldDirection == 'w' && userInput == 's');
    invalidChange = invalidChange || (oldDirection == 's' && userInput == 'w');
    invalidChange = invalidChange || (oldDirection == 'a' && userInput == 'd');
    invalidChange = invalidChange || (oldDirection == 'd' && userInput == 'a');

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

Position Snake_move (Snake* s) {
    LinkedList* body = s->bodyparts;
    Position oldHeadPosition = s->bodyparts->head->data;
    Position formerTail = body->tail->data;
    LinkedList_pop(body);
    Snake_getNextHeadPosition(s, &oldHeadPosition);
    LinkedList_appendHead(body, oldHeadPosition);
    char userInput = Snake_getUserInputIfAny(s);
    Snake_changeDirection(s, userInput);
    return formerTail;
}

LinkedList* Snake_getBody(Snake* s) {
    LinkedList_appendXY(s->bodyparts, s->uprbY/2, s->uprbX/2);
    LinkedList_appendXY(s->bodyparts, s->uprbY/2+1, s->uprbX/2);
    return s->bodyparts;
}

Position Snake_provideFood(Snake* s) {
    Position foodPos;
    while (1) {
        int randomX = rand()%(s->uprbX) + s->lwrbX+1;
        int randomY = rand()%(s->uprbY) + s->lwrbY+1;
        foodPos.x = randomX;
        foodPos.y = randomY;
        if (!LinkedList_isPosInList(s->bodyparts, foodPos)) {
            break;
        }
    }
    s->foodPosition = foodPos;
    return foodPos;

}


bool Snake_initialStage(Snake* s) {
    if (s->foodPosition.x == -1) {
        return true;
    }
    return false;
}
bool Snake_eat (Snake* s) {
    if (s->bodyparts->head->data.y == s->foodPosition.y &&
        s->bodyparts->head->data.x == s->foodPosition.x
        ) 
    {
        LinkedList_appendHead(s->bodyparts, s->foodPosition);
        
        s->score++;
        return true;
    }
    return false;
}
bool Snake_hitWall (Snake* s) {
    bool result = false ;
    int x = s->bodyparts->head->data.x;
    int y = s->bodyparts->head->data.y;
    result = result || (x == s->lwrbX+1);
    result = result || (x == s->uprbX-1);
    result = result || (y == s->lwrbY+1);
    result = result || (y == s->uprbY-1);

    return result;
}



bool Snake_hitItself(Snake* s) {
    Position headPosition = s->bodyparts->head->data;
    LinkedList* l = s->bodyparts;
    Position found ;
    for (int i = 1;i < l->len; i++ ) {
        found = LinkedList_get(l, i);
        if (found.x == headPosition.x &&
            found.y == headPosition.y)
            {
                return true;
            }
    }
    
    return false;
}