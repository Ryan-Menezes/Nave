#ifndef HELPERS_H_DEFINED
#define HELPERS_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// DIMENSÃO
typedef struct{
	unsigned short width;
	unsigned short height;
}DIMENSION;

// POSIÇÃO
typedef struct{
	unsigned short x;
	unsigned short y;
}POSITION;

DIMENSION *createDimension();
POSITION *createPosition();
void gotoXY(unsigned short x, unsigned short y);
void hideCursor();
void setWindowDimension(unsigned short width, unsigned short height);

#endif
