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
void gotoXY(unsigned int x, unsigned int y);
void hideCursor();
void setWindowDimension(unsigned int width, unsigned int height);

#endif
