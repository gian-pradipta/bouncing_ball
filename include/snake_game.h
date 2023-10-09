#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "graphic.h"
#include "snake.h"

typedef struct snakeGame {
    Snake* s;
    Graphic* g;
    Position nextFoodPosition;
    int score; 
} SnakeGame;


SnakeGame* SnakeGame_construct(int rows, int columns);
void SnakeGame_destruct (SnakeGame* s);
Position SnakeGame_nextFoodPosition();
char SnakeGame_getUserInputIfAny();
void SnakeGame_startScreen();
bool SnakeGame_eat (SnakeGame* s);
bool SnakeGame_hitWall (SnakeGame* s); 
bool SnakeGame_hitItself(SnakeGame* s) ;
void SnakeGame_renderSnake(SnakeGame* s);
void SnakeGame_gameStart(SnakeGame* sg);
void SnakeGame_putFood(SnakeGame* sg);
void SnakeGame_isLost(SnakeGame* sg);
void SnakeGame_setStartingFood(SnakeGame* sg);
void SnakeGame_readScores(SnakeGame* sg);
void SnakeGame_gameStartNoAnsii(SnakeGame* sg);


#endif