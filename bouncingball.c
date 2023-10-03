#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

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
    this->pixels[y][x] = '*';
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

bool Graphic_isXValid(Graphic* g, int xPos) {
    bool isValid = true;
    int xUpperBound = g->columns -1;
    int xLowerBound = 0;
    isValid = xPos <= xUpperBound && xPos >= xLowerBound;
    return isValid;
}

bool Graphic_isYValid(Graphic* g, int yPos) {
    bool isValid = true;
    int yUpperBound = g->rows -1;
    int yLowerBound = 0;
    isValid = (yPos <= yUpperBound && yPos >= yLowerBound);
    return isValid;
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

void Graphic_bouncingMove(Graphic* g) {
    int frameDelay = 30000;
    //initialization pixel
    int randomNumber;
    int oldX = 0;
    int oldY = 0;
    int newY, newX;
    int shiftY = 1;
    int shiftX = 1;
    Graphic_putPixel(g, 0, 0);
    while (1) {
        Graphic_renderGraphic(g);
        newY = oldY + shiftY;
        newX = oldX + shiftX;
        if (Graphic_isPositionValid(g, newY, newX)) {
            Graphic_movePixel(g, oldY, oldX, newY, newX);
            oldY = newY;
            oldX = newX;
        } 
        else {
            if (!Graphic_isYValid(g, newY)) {
                shiftY = shiftY * -1;
            }
            if (!Graphic_isPositionValid(g, (newY + shiftY),newX)) {
                shiftX = shiftX * -1;
            }
        }

        usleep(frameDelay);
        system("cls");
    }
}
void Graphic_destruct (Graphic* this) {
    for (int i = 0; i < this->rows; i++) {
        free(this->pixels[i]);
    }
    free(this->pixels);
    free(this);
}

Graphic* Graphic_construct(int rows, int columns) {
    Graphic *graphic = (Graphic *) malloc(sizeof(Graphic));
    graphic->rows = rows;
    graphic->columns = columns;
    graphic->pixels = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; ++i) {
        graphic->pixels[i] = (int*)malloc(columns * sizeof(int));
    }
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0 ; j < columns ; j++) {
            graphic->pixels[i][j] = '*';
        }
    }
    return graphic; 
}
 

int main () {
    Graphic* g = Graphic_construct(20, 100);
    Graphic_bouncingMove(g);
    Graphic_destruct(g);
}