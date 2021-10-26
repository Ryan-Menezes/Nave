#ifndef BULLET_H_DEFINED
#define BULLET_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include "helpers.h"

// BULLET
typedef struct{
	unsigned char caractere;
	POSITION *position;
}BULLET;

BULLET *createBullet(unsigned short x, unsigned short y);
void renderBullet(BULLET *bullet);
bool updateBullet(BULLET *bullet);

#endif