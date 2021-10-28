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
		
		for(unsigned short i = 0; i < LIMIT_ASTEROIDS; i++) game->asteroids[i] = NULL;
	}
	
	return game;
}

/*
	Renderiza o placar do jogo
	parameters: GAME *game, SHIP *ship
	return: void
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
		for(unsigned short i = 0; i < WINDOW_WIDTH; i++) printf("%c", 223);
	}
}

/*
	Gera e atualiza asteroids
	parameters: GAME *game, SHIP *ship
	return: void
*/
void updateGame(GAME *game, SHIP *ship){
	srand(time(NULL) * clock());
	static unsigned short id = 0;
	
	if(ship && game){
		// Aplica um delay na movimentação dos asteroids
		for(unsigned short i = 0; i < DELAY_BULLET; i++);
		
		for(unsigned short i = 0; i < LIMIT_ASTEROIDS; i++){
			// CRIA NOVO ASTEROIDE
			if(game->asteroids[i] == NULL){
				if(id % LIMIT_ASTEROIDS == 0)
					addAsteroid(game, ship, i);
			}
			// MOVIMENTA ASTEROIDE
			else{
				clearAsteroid(game->asteroids[i]);
				if(updateAsteroid(game->asteroids[i], WINDOW_HEIGHT - 1))
					removeAsteroid(game, ship, i);
			}
			
			renderAsteroid(game->asteroids[i]);
			id = rand() * LIMIT_ASTEROIDS;
		}

		// APLICANDO COLISÃO ENTRE TIRO E ASTEROID
		for(unsigned short i = 0; i < LIMIT_BULLETS; i++){
			// VERIFICA SE A BALA NÃO É NULA
			if(ship->bullets[i]){
				for(unsigned short j = 0; j < LIMIT_ASTEROIDS; j++){
					// VERIFICA SE O ASTEROIDE NÃO É NULO
					if(game->asteroids[j]){
						// VERFICA SE HOUVE COLISÃO
						if(hasColision(game->asteroids[j]->position, ship->bullets[i]->position)){
							game->score += PLUSSCORE;
							createExplosion(ship->bullets[i]->position);
							removeBullet(ship, i);
							removeAsteroid(game, ship, j);
							clearConsole(WINDOW_WIDTH, HEIGHT_MENU - 1);
							renderScoreboard(game, ship);
							break;
						}
					}
				}
			}
		}
	}	
}

/*
	Adiciona um asteroide no array
	parameters: GAME *game, SHIP *ship, unsigned short index
	return: void
*/
void addAsteroid(GAME *game, SHIP *ship, unsigned short index){
	if(game && ship){
		unsigned short x = (rand() % (WINDOW_WIDTH - ship->dimension->width * 2)) + ship->dimension->width;
		ASTEROID *asteroid = createAsteroid(x, HEIGHT_MENU);
		
		game->asteroids[index] = asteroid;
	}
}

/*
	Remove um asteroide do array
	parameters: GAME *game, SHIP *ship, unsigned short index
	return: void
*/
void removeAsteroid(GAME *game, SHIP *ship, unsigned short index){
	if(game && ship){
		clearAsteroid(game->asteroids[index]);
		free(game->asteroids[index]);
		game->asteroids[index] = NULL;
	}
}

/*
	Verifica se houve uma colisão entre dois objetos
	parameters: POSITION *p1, POSITION *p2;
	return: void
*/
bool hasColision(POSITION *p1, POSITION *p2){
	return (p1->x == p2->x && p1->y == p2->y);
}

/*
	Gera uma explosão na tela
	parameters: POSITION *posision
	return: void
*/
void createExplosion(POSITION *position){
	gotoXY(position->x, position->y - 1);
	printf("#");
	gotoXY(position->x - 1, position->y);
	printf("###");
	gotoXY(position->x, position->y + 1);
	printf("#");
	
	Sleep(100);
	
	gotoXY(position->x - 1, position->y - 2);
	printf("#  #");
	gotoXY(position->x - 2, position->y - 1);
	printf("######");
	gotoXY(position->x - 1, position->y);
	printf("####");
	gotoXY(position->x - 2, position->y + 1);
	printf("######");
	gotoXY(position->x - 1, position->y + 2);
	printf("#  #");
	
	Sleep(100);
	
	for(char i = 2 ; i >= -2; i--){
		gotoXY(position->x - 2, position->y + i);
		printf("         ");
	}
}
