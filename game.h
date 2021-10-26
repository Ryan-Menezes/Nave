#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include "helpers.h"
#include "bullet.h"
#include "ship.h"

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 30

// MAPA
typedef struct{
	DIMENSION *dimension;
}MAP;

// GAME
typedef struct{
	bool start;
	unsigned int score;
	unsigned short level;
	unsigned short speed;
	MAP *map;
}GAME;

MAP *createMap();
GAME *createGame();
void renderScoreboard(GAME *game, SHIP *ship);

#endif
