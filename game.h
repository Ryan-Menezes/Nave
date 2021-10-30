#ifndef GAME_H_DEFINED
#define GAME_H_DEFINED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "helpers.h"
#include "asteroid.h"
#include "bullet.h"
#include "ship.h"

#define START 1
#define GAMEOVER 0
#define PLUSSCORE 10
#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 30
#define LIMIT_ASTEROIDS 10
#define TITLE "NAVE"

// MAPA
typedef struct{
	DIMENSION *dimension;
}MAP;

// GAME
typedef struct{
	bool start;
	unsigned int score;
	unsigned short level;
	unsigned char lifes;
	unsigned char speed;
	unsigned char status;
	MAP *map;
	ASTEROID *asteroids[LIMIT_ASTEROIDS];
}GAME;

MAP *createMap();
GAME *createGame();
void startGame(GAME *game, SHIP *ship);
void renderScoreboard(GAME *game);
void updateGame(GAME *game, SHIP *ship);
void addAsteroid(GAME *game, SHIP *ship, unsigned short index);
void removeAsteroid(GAME *game, unsigned short index);
bool hasColision(POSITION *p1, POSITION *p2);
void createExplosion(POSITION *position);
void menu(GAME *game, SHIP *ship);
void gameover(GAME *game);

#endif
