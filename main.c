#include <stdio.h>
#include <stdlib.h>
#include "game.h"

// VARIABLES
GAME *game = NULL;
SHIP *ship = NULL;

// FUNCTIONS
void inicialize();
void loop();
void render();
void update();

void main(int argc, char *argv[]) {
	inicialize();
	loop();
}

/*
	Inicializa variáveis globais
	parameters: void
	return: void
*/
void inicialize(){
	hideCursor();
	game = createGame();
	ship = createShip();
	
	// CENTRALIZANDO NAVE NA TELA
	ship->position->x = (WINDOW_WIDTH / 2) - (ship->dimension->width / 2);
	ship->position->y = (WINDOW_HEIGHT / 2) - (ship->dimension->height / 2);
	
	// MUDANDO A DIMENÇÃO DA JANELA
	setWindowDimension(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// RENDERIZANDO O PAINEL
	renderScoreboard(game, ship);
}

/*
	Loop do jogo
	parameters: void
	return: void
*/
void loop(){
	if(game->start){
		render();
		update();
		loop();
		sleep(game->speed);
	}
}

/*
	Renderiza elementos do jogo
	parameters: void
	return: void
*/
void render(){
	// RENDERIZA NAVE
	renderShip(ship);
}

/*
	Atualiza elementos do jogo
	parameters: void
	return: void
*/
void update(){
	// ATUALIZA NAVE
	updateShip(ship, &(DIMENSION){WINDOW_WIDTH, WINDOW_HEIGHT});
}
