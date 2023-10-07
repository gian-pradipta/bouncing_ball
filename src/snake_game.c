#include "../include/graphic.h"
#include "../include/snake.h"
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct snakeGame {
    Snake* s;
    Graphic* g;
    Position nextFoodPosition;
    int score; 
} SnakeGame;

SnakeGame* SnakeGame_construct(int rows, int columns) {
    srand(time(NULL));
    SnakeGame* sg = (SnakeGame*) malloc(sizeof(SnakeGame));
    sg->g = Graphic_construct(rows, columns);
    sg->s = Snake_construct(rows, 0, columns, 0);
    sg->score = 0;
    return sg;
}

void SnakeGame_destruct (SnakeGame* s) {
    Graphic_destruct(s->g);
    Snake_destruct(s->s);
    free(s);
}

Position SnakeGame_nextFoodPosition(SnakeGame* sg) {
    Snake* s = sg->s;
    Position foodPos;
    // x > 1
    // y > 1 
    while (1) {
        int randomX = rand()%((s->uprbX - 2) - (s->lwrbX + 1)) + s->lwrbX+1;
        int randomY = rand()%((s->uprbY -2) - (s->lwrbY + 1)) + s->lwrbY+1;
        if (randomY == 0 || randomY == 0 || randomX >= s->uprbX -1|| randomY >= s->uprbY-1) {continue;}
        foodPos.x = randomX;
        foodPos.y = randomY;
        if (!LinkedList_isPosInList(s->bodyparts, foodPos)) {
            break;
        }
    }
    sg->nextFoodPosition = foodPos;
    return foodPos;

}


char SnakeGame_getUserInputIfAny(SnakeGame* sg){
    if (_kbhit()) {return _getch();}

    return sg->s->direction;
}
void SnakeGame_startScreen(){
    printf("WELCOME TO SNAKE GAME \n");
    printf("Press Any Key to Start \n");
    _getch();
}



void SnakeGame_readScores(SnakeGame* sg) {
    FILE* file;
    char c;
    const char* filepath = "score/score.txt";
    file = fopen(filepath, "r");
    if (file == NULL) {
        printf("No score!");
        exit(EXIT_FAILURE);
    }
    while ((c = fgetc(file)) != EOF){
        printf("%c", c);
    }
    
    fclose(file);
}

void SnakeGame_writeHighScore() {

}

bool SnakeGame_eat (SnakeGame* sg) {
    Snake* s = sg->s;

    if (s->bodyparts->head->data.y == sg->nextFoodPosition.y &&
        s->bodyparts->head->data.x == sg->nextFoodPosition.x
        ) 
    {
        LinkedList_appendHead(s->bodyparts, sg->nextFoodPosition);
        
        sg->score ++;
        return true;
    }
    return false;
}
bool SnakeGame_hitWall (SnakeGame* sg) {
    Snake* s = sg->s;
    bool result = false ;
    int x = s->bodyparts->head->data.x;
    int y = s->bodyparts->head->data.y;
    result = result || (x == s->lwrbX);
    result = result || (x == s->uprbX-1);
    result = result || (y == s->lwrbY);
    result = result || (y == s->uprbY-1);

    return result;
}; 
bool SnakeGame_hitItself(SnakeGame* sg) {
    Snake* s = sg->s;
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
};

void SnakeGame_renderSnake(SnakeGame* sg) {
    Snake* s = sg->s;
    Graphic_putShape(sg->g, sg->s->bodyparts);
    Graphic_renderGraphic(sg->g);
}

void SnakeGame_initializeSnake(SnakeGame* sg) {
    Snake* s = sg->s;
    LinkedList_appendXY(s->bodyparts, s->uprbY/2, s->uprbX/2);
    LinkedList_appendXY(s->bodyparts, s->uprbY/2+1, s->uprbX/2);
}

void SnakeGame_putFood(SnakeGame* sg) {
    if (!SnakeGame_eat(sg)) {
        Graphic_putPixel(sg->g, sg->nextFoodPosition.y, sg->nextFoodPosition.x);
        return;
    }
    Position nextPos = SnakeGame_nextFoodPosition(sg);
    Graphic_putPixel(sg->g, nextPos.y, nextPos.x);
}

void SnakeGame_setStartingFood(SnakeGame* sg) {
    Position nextPos = SnakeGame_nextFoodPosition(sg);
    sg->nextFoodPosition = nextPos;
}

bool SnakeGame_isLost(SnakeGame* sg) {
    if (SnakeGame_hitItself(sg) || SnakeGame_hitWall(sg)){
        return true;
    }
    return false;
}

void SnakeGame_gameStart(SnakeGame* sg) {
    Snake* s = sg->s;
    SnakeGame_initializeSnake(sg);
    size_t frameDelay = 75000;
    SnakeGame_setStartingFood(sg);
    while (1) {
        Graphic_refresh(sg->g);
        SnakeGame_putFood(sg);
        char userInput = SnakeGame_getUserInputIfAny(sg);
        SnakeGame_renderSnake(sg);
        printf("Total Score: %d\n", sg->score);
        Snake_changeDirection(s, userInput);
        Snake_move(s);
        if (sg->s->direction == 'w' || 'a') frameDelay = 190000; else frameDelay = 75000;
        usleep(frameDelay);
        if (SnakeGame_isLost(sg)) {
            break;
        }
        system("cls");
    }


}