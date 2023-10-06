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
    Position foodPosition;
    int score ;
} Snake;

Snake* Snake_construct(int upperBoundY, int lowerBoundY,int upperBoundX,int lowerBoundX);
void Snake_destruct(Snake* s);
void Snake_changeDirection (Snake* s, char userInput);
char getUserInputIfAny();
Position Snake_getNextHeadPosition(Snake* s, Position *pos);
Position Snake_move (Snake* s);
LinkedList* Snake_getBody(Snake* s);
Position Snake_provideFood(Snake* s);
bool Snake_eat (Snake* s);
bool Snake_initialStage(Snake* s);
bool Snake_hitWall (Snake* s); 
bool Snake_hitItself(Snake* s) ;

#endif