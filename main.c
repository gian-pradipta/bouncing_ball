#include "graphic.h"
#include "snake.h"
#include "snake_game.h"
#include <stdio.h>

int main () {
    // Graphic *g = Graphic_construct(10, 200);
    SnakeGame* sg = SnakeGame_construct(20, 50);

    SnakeGame_startScreen(sg);
    SnakeGame_gameStart(sg);
    printf("Game Over!\n");
    
    SnakeGame_destruct(sg);
    return 0;   
}