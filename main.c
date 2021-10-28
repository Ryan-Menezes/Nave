/*
	Jogo de navinha desenvolvido em linguagem C, cujo o objetivo é marcar a maior pontuação possível, enquanto você evita que asteroides atinjam você!
	
	Desenvolvido por: 	Ryan de Menezes Nobre Ciriaco
	GitHub: 			https://github.com/Ryan-Menezes
	E-Mail: 			menezesryan1010@gmail.com
	linkedin: 			https://www.linkedin.com/in/ryan-menezes-845080201/
*/

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

// VARIABLES
GAME *game = NULL;
SHIP *ship = NULL;

// FUNCTIONS
void inicialize();
void loop();
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
	
	// MUDANDO O TITULO DA JANELA
	SetConsoleTitle(TITLE);
	
	// MUDANDO A DIMENÇÃO DA JANELA
	setWindowDimension(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// LIMPANDO O CONSOLE
	clearConsole(WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// RENDERIZANDO O PAINEL
	renderScoreboard(game, ship);
	
	// RENDERIZANDO NAVE
	renderShip(ship);
}

/*
	Loop do jogo
	parameters: void
	return: void
*/
void loop(){
	if(game->start){
		update();
		Sleep(game->speed);
	}
	
	loop();
}

/*
	Atualiza elementos do jogo
	parameters: void
	return: void
*/
void update(){
	// ATUALIZA NAVE
	updateShip(ship, &(DIMENSION){WINDOW_WIDTH, WINDOW_HEIGHT});
	
	// GERA NOVOS ASTEROIDES, ATUALIZA POSIÇÂO DE ASTEROIDES, VERIFICA COLISÃO ENTRE ASTEROID, BALA E NAVE
	updateGame(game, ship);
}
