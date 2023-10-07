#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "LinkedList.h"

typedef struct Node Node;
typedef struct linkedList LinkedList;


typedef struct graphic Graphic ;

Graphic* Graphic_construct(int, int);
void Graphic_destruct (Graphic* this);

void Graphic_putPixel(Graphic*,int,int);
void Graphic_deletePixel(Graphic*,int,int);
void Graphic_movePixel(Graphic* ,int, int, int, int);
void Graphic_refresh(Graphic *graphic);
void Graphic_putShape(Graphic*, LinkedList*);
void Graphic_renderGraphic (Graphic* this);


#endif