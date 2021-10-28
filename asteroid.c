#include "asteroid.h"

/*
	Cria a estrutura do asteroide
	parameters: void
	return: ASTEROID
*/
ASTEROID *createAsteroid(unsigned short x, unsigned short y){
	ASTEROID *asteroid = (ASTEROID*) calloc(1, sizeof(ASTEROID));
	
	if(asteroid){
		asteroid->body	 		= 2;
		asteroid->position 		= createPosition();
		asteroid->position->x 	= x;
		asteroid->position->y 	= y;
	}	
	
	return asteroid;
}

/*
	Renderiza asteroide na tela
	parameters: void
	return: void
*/
void renderAsteroid(ASTEROID *asteroid){
	if(asteroid){
		gotoXY(asteroid->position->x, asteroid->position->y);
		printf("%c", asteroid->body);
	}
}

/*
	Função que limpa o asteroide da tela
	parameters: ASTEROID *asteroid
	return: void
*/
void clearAsteroid(ASTEROID *asteroid){
	if(asteroid){
		gotoXY(asteroid->position->x, asteroid->position->y);
		printf(" ");
	}
}

/*
	Atualiza posição do asteroide
	parameters: void
	return: bool
*/
bool updateAsteroid(ASTEROID *asteroid, unsigned short height){
	if(asteroid){
		clearAsteroid(asteroid);
		
		asteroid->position->y++;
		renderAsteroid(asteroid);
		
		return (asteroid->position->y >= height);
	}
	
	return false;
}

/*
	Limpa o console
	parameters: unsigned short width, unsigned short height
	return: void
*/
void clearConsole(unsigned short width, unsigned short height){
	for(unsigned short l = 0; l < width; l++){
		for(unsigned short c = 0; c < height; c++){
			gotoXY(l, c);
			printf(" ");
		}
	}
}
