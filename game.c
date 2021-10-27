#include "game.h"

/*
	Cria a estrutura do jogo
	parameters: void
	return: GAME
*/
GAME *createGame(){
	GAME *game = (GAME*) calloc(1, sizeof(GAME));
	
	if(game){
		game->start 			= true;
		game->score 			= 0;
		game->level 			= 1;
		game->speed 			= 50;
		
		for(unsigned int i = 0; i < LIMIT_ASTEROIDS; i++) game->asteroids[i] = NULL;
	}
	
	return game;
}

/*
	Renderiza o placar do jogo
	parameters: void
	return: GAME
*/
void renderScoreboard(GAME *game, SHIP *ship){
	if(ship && game){
		const short Y = 1;
	
		// SCORE
		gotoXY(1, Y);
		printf("SCORE: %u", game->score);
		
		// LEVEL
		unsigned char *level = "LEVEL: %i";
		unsigned char *text = (unsigned char*) calloc(50, sizeof(unsigned char));
		
		sprintf(text, level, game->level);
		
		gotoXY((WINDOW_WIDTH / 2) - (strlen(text) / 2), Y);
		printf(text);
		
		// LIFES
		for(unsigned short i = 0; i < ship->lifes ; i++){
			gotoXY(WINDOW_WIDTH - ship->lifes + i - 1, Y);
			printf("%c", HEART);
		}
		
		// SEPARADOR
		gotoXY(0, 3);
		for(unsigned int i = 0; i < WINDOW_WIDTH; i++) printf("%c", 223);
	}
}

/*
	Gera e atualiza asteroids
	parameters: void
	return: void
*/
void updateGame(GAME *game, SHIP *ship){
	srand(time(NULL));
	unsigned short x;
	static unsigned short id = 0;
	
	if(ship && game){
		for(unsigned int i = 0; i < LIMIT_ASTEROIDS; i++){
			// CRIA NOVO ASTEROIDE
			if(game->asteroids[i] == NULL){
				if(id % (LIMIT_ASTEROIDS * (i + 1)) == 0){
					x = (rand() % WINDOW_WIDTH - SHIP_WIDTH) + SHIP_WIDTH / 2;
					ASTEROID *asteroid = createAsteroid(x, HEIGHT_MENU);
					game->asteroids[i] = asteroid;
				}
			}
			// MOVIMENTA ASTEROIDE
			else{
				clearAsteroid(game->asteroids[i]);
				if(updateAsteroid(game->asteroids[i], WINDOW_HEIGHT - 1)){
					clearAsteroid(game->asteroids[i]);
					free(game->asteroids[i]);
					game->asteroids[i] = NULL;
				}
			}
			
			if(game->asteroids[i]) renderAsteroid(game->asteroids[i]);
		}
	}
	
	id++;	
}
