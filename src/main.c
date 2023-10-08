#include "../include/snake_game.h"
#include <stdio.h>

int main () 
{

    SnakeGame* sg = SnakeGame_construct(20, 50);
    SnakeGame_startScreen(sg);

    SnakeGame_gameStart(sg);

    SnakeGame_destruct(sg);

    // SnakeGame_readScores(sg);
    return 0;   
}