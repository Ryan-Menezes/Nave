#include "game.h"

/*
	Cria a estrutura do jogo
	parameters: void
	return: GAME
*/
GAME *createGame(){
	GAME *game = (GAME*) calloc(1, sizeof(GAME));
	
	if(game){
		game->start  = false;
		game->score  = 0;
		game->level  = 1;
		game->speed  = 50;
		game->lifes  = 5;
		game->status = START;
		
		for(unsigned short i = 0; i < LIMIT_ASTEROIDS; i++) game->asteroids[i] = NULL;
	}
	
	return game;
}

/*
	Inicia o jogo
	parameters: GAME *game, SHIP *ship
	return: void
*/
void startGame(GAME *game, SHIP *ship){
	if(game && ship){
		char *msg = "STARTS AT:";
		
		// INICIALIZANDO ESTRUTURAS
		game->score  = 0;
		game->level  = 1;
		game->lifes  = 5;
		game->start  = true;
		game->status = START;
		
		// CENTRALIZANDO NAVE NA TELA
		ship->position->x = (WINDOW_WIDTH / 2) - (ship->dimension->width / 2);
		ship->position->y = (WINDOW_HEIGHT / 2) - (ship->dimension->height / 2);
		
		for(unsigned short i = 0; i < LIMIT_ASTEROIDS; i++) game->asteroids[i] = NULL;
		for(unsigned short i = 0; i < LIMIT_BULLETS; i++) ship->bullets[i] = NULL;
		
		// RENDERIZANDO O PAINEL
		renderScoreboard(game);
		
		// CONTAGEM REGRESSIVA
		gotoXY(WINDOW_WIDTH / 2 - strlen(msg) / 2, WINDOW_HEIGHT / 2 - 1);
		printf(msg);
		
		for(unsigned short i = 5; i > 0; i--){
			gotoXY(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			printf("%i", i);
			Sleep(i * 500);
		}
		
		// LIMPA MENSAGEM
		gotoXY(WINDOW_WIDTH / 2 - strlen(msg) / 2, WINDOW_HEIGHT / 2 - 1);
		for(unsigned short i = 0; i < strlen(msg); i++) printf(" ");
		
		// RENDERIZANDO NAVE
		renderShip(ship);
	}
}

/*
	Renderiza o placar do jogo
	parameters: GAME *game
	return: void
*/
void renderScoreboard(GAME *game){
	if(game){
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
		for(unsigned short i = 0; i < game->lifes; i++){
			gotoXY(WINDOW_WIDTH - game->lifes + i - 1, Y);
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
	if(ship && game){
		srand(time(NULL) * clock());
		static unsigned short id = 0;
		
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
					removeAsteroid(game, i);
			}
			
			renderAsteroid(game->asteroids[i]);
			id = rand() * LIMIT_ASTEROIDS;
		}

		// APLICANDO COLISÃO ENTRE TIRO, ASTEROID E NAVE
		for(unsigned short i = 0; i < LIMIT_ASTEROIDS; i++){
			// VERIFICA SE O ASTEROIDE NÃO É NULO
			if(game->asteroids[i]){
				for(unsigned short j = 0; j < LIMIT_BULLETS; j++){
					// VERIFICA SE A BALA NÃO É NULA
					if(ship->bullets[j]){
						// VERFICA SE HOUVE COLISÃO ENTRE TIRO E ASTEROID
						if(hasColision(game->asteroids[i]->position, ship->bullets[j]->position)){
							game->score += PLUSSCORE;
							if(game->score == game->level * PLUSSCORE * 10){
								game->level++;
								game->lifes++;
							}
							createExplosion(game->asteroids[i]->position);
							removeBullet(ship, j);
							removeAsteroid(game, i);
							clearConsole(WINDOW_WIDTH, HEIGHT_MENU - 1);
							renderScoreboard(game);
							break;
						}
					}
				}
				
				// VERFICA SE HOUVE COLISÃO ENTRE NAVE E ASTEROID
				if(game->asteroids[i] && shipHasColision(ship, game->asteroids[i]->position)){
					renderShip(ship);
					
					if(game->lifes > 0) game->lifes--;
					// ENCERRA O JOGO
					else{
						game->start  = false;
						game->status = GAMEOVER;
					}
					
					removeAsteroid(game, i);
					clearConsole(WINDOW_WIDTH, HEIGHT_MENU - 1);
					renderScoreboard(game);
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
	parameters: GAME *game, unsigned short index
	return: void
*/
void removeAsteroid(GAME *game, unsigned short index){
	if(game){
		clearAsteroid(game->asteroids[index]);
		free(game->asteroids[index]);
		game->asteroids[index] = NULL;
	}
}

/*
	Verifica se houve uma colisão entre dois objetos
	parameters: POSITION *p1, POSITION *p2;
	return: bool
*/
bool hasColision(POSITION *p1, POSITION *p2){
	if(p1 && p2) return (p1->x == p2->x && p1->y == p2->y);
	
	return false;
}

/*
	Gera uma explosão na tela
	parameters: POSITION *posision
	return: void
*/
void createExplosion(POSITION *position){
	if(position){
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
}

/*
	Apresenta o menu de opções na tela
	parameters: GAME *game, SHIP *ship
	return: void
*/
void menu(GAME *game, SHIP *ship){
	if(game && ship){
		unsigned char *msg = NULL;
		const unsigned short ROWSBANNER = 7;
		unsigned char banner[][200] = {
			"00000000000000000000000000000",
			"01100001011111010000101111110",
			"01010001010001010000101000000",
			"01001001011111010000101111110",
			"01000101010001001001001000000",
			"01000011010001000110001111110",
			"00000000000000000000000000000"
		};
		
		const unsigned short AMOUNTOP = 2;
		unsigned char options[][100] = {"NEW GAME", "EXIT"};
		unsigned char *arrow = ">>";
		unsigned char op = '\0';
		unsigned short i = 0, j = 0;
		int c = 0;
		
		// LIMPANDO O CONSOLE
		clearConsole(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		// RENDERIZA O BANNER
		for(i = 0; i < ROWSBANNER; i++){
			gotoXY(WINDOW_WIDTH / 2 - strlen(banner[i]), WINDOW_HEIGHT / 2 - ROWSBANNER + i);
			
			for(j = 0; j < strlen(banner[i]); j++){
				for(c = 0; c < 2; c++){
					if(banner[i][j] == '0') printf("%c", 219);
					else printf(" ");
				}
			}
		}
		
		// RENDERIZA O MENU
		for(i = 0; i < AMOUNTOP; i++){
			gotoXY(WINDOW_WIDTH / 2 - strlen(options[i]) / 2, WINDOW_HEIGHT / 2 - AMOUNTOP +  ROWSBANNER / 2 + i);
			printf("%s", options[i]);
		}
		
		// CREDITOS AO DESENVOLVEDOR
		msg = "DEVELOPED BY RYAN DE MENEZES NOBRE CIRIACO";	
		gotoXY(WINDOW_WIDTH / 2 - strlen(msg) / 2, WINDOW_HEIGHT - 3);
		printf(msg);
		
		msg = "GITHUB: https://github.com/Ryan-Menezes";	
		gotoXY(WINDOW_WIDTH / 2 - strlen(msg) / 2, WINDOW_HEIGHT - 2);
		printf(msg);
		
		i = 0;
		
		// PEGA A OPÇÃO SELECIONADA
		while(op != ENTER){
			// RENDERIZA A SETA
			gotoXY((WINDOW_WIDTH / 2 - strlen(options[i]) / 2) - strlen(arrow) - 1, WINDOW_HEIGHT / 2 - AMOUNTOP +  ROWSBANNER / 2 + i);
			printf(arrow);
			
			op = getch();
			setbuf(stdin, NULL);
			
			// LIMPA A SETA
			gotoXY((WINDOW_WIDTH / 2 - strlen(options[i]) / 2) - strlen(arrow) - 1, WINDOW_HEIGHT / 2 +  ROWSBANNER / 2 - AMOUNTOP + i);
			for(unsigned int j = 0; j < strlen(arrow); j++) printf(" ");
			
			// MOVIMENTA A SETA
			switch(toupper(op)){
				case UP:
					if(i > 0) i--;		
					break;
				case DOWN:
					if(i <= 0) i++;		
					break;
			}
		}
		
		// LIMPANDO O CONSOLE
		clearConsole(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		// VERIFICA OPÇÃO SELECIONADA
		switch(i){
			case 0:
				startGame(game, ship);
				break;
			default:
				exit(0);
		}
	}
}

/*
	Apresenta mensagem de game over na tela
	parameters: GAME *game
	return: void
*/
void gameover(GAME *game){
	if(game){
		const unsigned short SIZE = 200;
		unsigned char *msg = (unsigned char *) calloc(SIZE, sizeof(unsigned char));
		
		game->status = START;
		
		// LIMPANDO O CONSOLE
		clearConsole(WINDOW_WIDTH, WINDOW_HEIGHT);
		
		strncpy(msg, "GAME OVER", SIZE);	
		gotoXY(WINDOW_WIDTH / 2 - strlen(msg) / 2, WINDOW_HEIGHT / 2 - 1);
		printf(msg);
		
		sprintf(msg, "SCORE: %i | LEVEL: %i", game->score, game->level);		
		gotoXY(WINDOW_WIDTH / 2 - strlen(msg) / 2, WINDOW_HEIGHT / 2 + 1);
		printf(msg);
		
		free(msg);
		getch();
	}
}
