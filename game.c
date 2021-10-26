#include "game.h"

/*
	Cria a estrutura do jogo
	parameters: void
	return: GAME
*/
GAME *createGame(){
	GAME *game = (GAME*) calloc(1, sizeof(GAME));
	
	if(game){
		game->start = true;
		game->score = 0;
		game->level = 1;
		game->speed = 2000;
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
		
		sprintf(text, level, game->score);
		
		gotoXY((WINDOW_WIDTH / 2) - (strlen(text) / 2), Y);
		printf(text);
		
		// LIFES
		for(unsigned short i = 0; i < ship->lifes ; i++){
			gotoXY(WINDOW_WIDTH - ship->lifes + i - 1, Y);
			printf("%c", HEART);
		}
	}
}
