#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <conio.h>
#include "graphic.h"
#include <unistd.h>


typedef struct graphic {
    int rows;
    int columns;
    int** pixels;
} Graphic ;

void Graphic_putPixel(Graphic* this,int y,int x) {
    if (y > this->rows-1) {
        y = this->rows-1;
    }
    if (x > this->columns-1) {
        x = this->columns-1;
    }
    if (y < 0) {
        y = 0;
    }
    if (x < 0){
        x = 0;
    }
    this->pixels[y][x] = '#';
}


void Graphic_deletePixel(Graphic* this,int y,int x) {
    if (y > this->rows-1) {
        y = this->rows-1;
    }
    if (x > this->columns-1) {
        x = this->columns-1;
    }
    if (y < 0) {
        y = 0;
    }
    if (x < 0){
        x = 0;
    }
    this->pixels[y][x] = ' ';
}

void Graphic_movePixel(Graphic* this,int formerY, int formerX, int futureY, int futureX) {
    Graphic_deletePixel(this,formerY, formerX);
    Graphic_putPixel(this, futureY, futureX);
}
void Graphic_renderGraphic (Graphic* this) {
    int stringLen = this->rows*this->columns + this->rows + 1;
    char display[stringLen]; 
    int currentDisplayIndex = 0;
    for (int i = 0 ; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            display[currentDisplayIndex] = this->pixels[i][j];
            currentDisplayIndex++;
        }
        display[currentDisplayIndex] = '\n';
        currentDisplayIndex++;
    }
    display[currentDisplayIndex] = '\0';
    printf("%s", display);
}

bool Graphic_isPositionValid(Graphic* g, int yPos, int xPos) {
    bool isValid = true;
    int xUpperBound = g->columns -1;
    int yUpperBound = g->rows -1 ;
    int xLowerBound = 0;
    int yLowerBound = 0;
    isValid = xPos <= xUpperBound && xPos >= xLowerBound;
    isValid = isValid && (yPos <= yUpperBound && yPos >= yLowerBound);
    return isValid;
}


void Graphic_destruct (Graphic* this) {
    for (int i = 0; i < this->rows; i++) {
        free(this->pixels[i]);
    }
    free(this->pixels);
    free(this);
}

void Graphic_refresh(Graphic *graphic) {
    int rows = graphic->rows;
    int columns = graphic->columns;
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0 ; j < columns ; j++) {
            graphic->pixels[i][j] = ' ';
            if (i == 0 || j == 0) {
                graphic->pixels[i][j] = '*';
            }
            if (i == rows-1 || j == columns - 1) {
                graphic->pixels[i][j] = '*';
            }
        }
    }
}
void Graphic_putShape(Graphic* g, LinkedList* ll) {
    // Graphic_refresh(g);
    for (int i = 0; i < ll->len; i++) {
        Position pos;
        pos = LinkedList_get(ll, i);
        Graphic_putPixel(g, pos.y, pos.x);
    }
} 


Graphic* Graphic_construct(int rows, int columns) {
    Graphic *graphic = (Graphic *) malloc(sizeof(Graphic));
    graphic->rows = rows;
    graphic->columns = columns;
    graphic->pixels = (int**)malloc (rows * sizeof(int*) +30);
    for (int i = 0; i < rows; ++i) {
        graphic->pixels[i] = (int*)malloc(columns * sizeof(int) + 10);
    }
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0 ; j < columns ; j++) {
            graphic->pixels[i][j] = ' ';
            if (i == 0 || j == 0) {
                graphic->pixels[i][j] = '*';
            }
            if (i == rows-1 || j == columns - 1) {
                graphic->pixels[i][j] = '*';
            }
        }
    }
    return graphic; 
}



void Graphic_startScreen () {
    printf("WELCOME TO SNAKE GAME \n");
    printf("Press Any Key to Start \n");
     _getch();
}


// int main () {
//     Graphic* g = Graphic_construct(20, 100);
//     // Graphic_renderShape(g, pos, 3);
//     Snake* s = Snake_construct(20, 0, 100, 0);
    
//     LinkedList* ll = Snake_getBody(s);
    
//     size_t frameDelay = 75000;
//     Position oldTail = {2, 2};
//     Position foodPosition;
//     Graphic_startScreen(g);
//     while (1) {
//         if (Snake_initialStage(s)) {
//             foodPosition = Snake_provideFood(s);
//         }
//         if (Snake_eat(s)) {
//             foodPosition = Snake_provideFood(s);
//         }
//         Graphic_deletePixel(g, oldTail.y, oldTail.x);
//         Graphic_putPixel(g, foodPosition.y, foodPosition.x);
//         Graphic_renderShape(g, ll);
//         oldTail =  Snake_move(s);
//         if (Snake_hitWall(s) || Snake_hitItself(s)) {
//             // system("cls");
//             printf("Game Over\nYour Score is %d", s->score);
//             break;
//         }
//         if (s->direction == 'w' || s->direction == 's') {
//             frameDelay = 150000;
//         }
//         usleep(frameDelay);
//         system("cls");
//     }
//     Graphic_destruct(g);
//     Snake_destruct(s);

// }