#ifndef SNAKE_H
#define SNAKE_H

#include "LinkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "graphic.h"
#include "Position.h"
#include "snake.h"

typedef struct snake{
    int uprbX;
    int uprbY;
    int lwrbX;
    int lwrbY;
    LinkedList* bodyparts;
    char direction;
} Snake;

Snake* Snake_construct(int upperBoundY, int lowerBoundY,int upperBoundX,int lowerBoundX);
void Snake_destruct(Snake* s);

void Snake_changeDirection (Snake* s, char userInput);
void Snake_getNextHeadPosition(Snake* s, Position *pos);
void Snake_move (Snake* s);
void Snake_addLength(Snake* s);
void Snake_turn(Snake*, char);
LinkedList* Snake_getBody(Snake* s);




#endif