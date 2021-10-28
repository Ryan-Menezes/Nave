#ifndef SHIP_H_DEFINED
#define SHIP_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include "helpers.h"
#include "bullet.h"

#define SHIP_WIDTH 5
#define SHIP_HEIGHT 3
#define LIMIT_BULLETS 10
#define HEIGHT_MENU 4

// NAVE
typedef struct{
	unsigned char body[SHIP_HEIGHT][SHIP_WIDTH];
	POSITION *position;
	DIMENSION *dimension;
	unsigned char lifes;
	unsigned char fuel;
	unsigned short speed;
	BULLET *bullets[LIMIT_BULLETS];
}SHIP;

// TECLAS
typedef enum{
	ENTER 		= 13,
	SPACE 		= 32,
	HEART		= 3,
	UP			= 'w',
	DOWN		= 's',
	RIGHT		= 'd',
	LEFT		= 'a'
}KEYS;

SHIP *createShip();
void renderShip(SHIP *ship);
void clearShip();
void updateShip(SHIP *ship, DIMENSION *limits);
void shoot(SHIP *ship);
void addBullet(SHIP *ship, unsigned short index);
void removeBullet(SHIP *ship, unsigned short index);

#endif
