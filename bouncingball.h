#ifndef BOUNCINGBALL_H
#define BOUNCINGBALL_H

#include "LinkedList.h"

typedef struct Node Node;
typedef struct linkedList LinkedList;


typedef struct graphic {
    int rows;
    int columns;
    int** pixels;
    int** freshGraphic;
} Graphic ;

void Graphic_putPixel(Graphic*,int,int);
void Graphic_deletePixel(Graphic*,int,int);
void Graphic_movePixel(Graphic* ,int, int, int, int);
void Graphic_renderShape(Graphic*, LinkedList*);
Graphic* Graphic_construct(int, int);



#endif