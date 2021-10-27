#ifndef ASTEROID_H_DEFINED
#define ASTEROID_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include "helpers.h"

// ASTEROID
typedef struct{
	unsigned char body;
	POSITION *position;
}ASTEROID;

ASTEROID *createAsteroid(unsigned short x, unsigned short y);
void renderAsteroid(ASTEROID *asteroid);
void clearAsteroid(ASTEROID *asteroid);
bool updateAsteroid(ASTEROID *asteroid, unsigned short height);

#endif
