#ifndef SNAKE_H
#define SNAKE_H

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

Snake* Snake_construct(int upperBoundY, int lowerBoundY,int upperBoundX,int lowerBoundX);
void Snake_changeDirection (Snake* s, char userInput);
char getUserInputIfAny();
Position Snake_getNextHeadPosition(Snake* s, Position *pos);
void Snake_move (Snake* s);
LinkedList* Snake_getBody(Snake* s);


#endif