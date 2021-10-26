#include "ship.h"

/*
	Função que cria uma nova nave
	parameters: void
	return: SHIP
*/
SHIP *createShip(){
	SHIP *ship = (SHIP*) calloc(1, sizeof(SHIP));
	
	if(ship){
		unsigned char body[SHIP_HEIGHT][SHIP_WIDTH] = {
			{32, 32, '^', 32, 32},
			{32, '#', '#', '#', 32},
			{'#', '#', '#', '#', '#'}
		};
		
		for(unsigned int l = 0; l < SHIP_HEIGHT; l++)
			for(unsigned int c = 0; c < SHIP_WIDTH; c++)
				ship->body[l][c] = body[l][c];
		
		ship->position				= createPosition();
		ship->dimension				= createDimension();
		ship->dimension->width 		= SHIP_WIDTH;
		ship->dimension->height 	= SHIP_HEIGHT;
		ship->lifes 				= 5;
		ship->fuel 					= 100;
		ship->speed 				= 2;
		ship->amountBullets			= 0;
	}
	
	return ship;
}

/*
	Função que renderiza a nave na tela
	parameters: SHIP *ship
	return: void
*/
void renderShip(SHIP *ship){
	if(ship){
		for(unsigned int l = 0; l < ship->dimension->height; l++){
			gotoXY(ship->position->x, ship->position->y + l);
			
			for(unsigned int c = 0; c < ship->dimension->width; c++){
				printf("%c", ship->body[l][c]);
			}
		}
	}	
}

/*
	Função que limpa a nave da tela
	parameters: SHIP *ship
	return: void
*/
void clearShip(SHIP *ship){
	if(ship){
		for(unsigned int l = 0; l < ship->dimension->height; l++){
			gotoXY(ship->position->x, ship->position->y + l);
			
			for(unsigned int c = 0; c < ship->dimension->width; c++){
				printf(" ");
			}
		}
	}
}

/*
	Função que atualiza os atributos da nave
	parameters: SHIP *ship
	return: void
*/
void updateShip(SHIP *ship, DIMENSION *limits){
	if(ship && limits){
		char key = '\0';
	
		// VERIFICA SE ALGUMA TECLA FOI PRESSIONADA
		if(kbhit()){
			key = getch();
			clearShip(ship);
		}	
		
		// ATUALIZA A POSIÇÃO DA NAVE	
		switch(key){
			case UP:
				ship->position->y -= ship->speed;
				break;
			case RIGHT:
				ship->position->x += ship->speed;
				break;
			case DOWN:
				ship->position->y += ship->speed;
				break;
			case LEFT:
				ship->position->x -= ship->speed;
				break;
			case SPACE:
				shoot(ship);
				break;
		}
		
		// VERIFICA SE A NAVE ÚLTRAPASSOU OS LIMITES DA TELA
		if(ship->position->y < 0) ship->position->y = 0;
		if(ship->position->x < 0) ship->position->x = 0;
		
		if(ship->position->y + ship->dimension->height >= limits->height) ship->position->y = limits->height - ship->dimension->height;
		if(ship->position->x + ship->dimension->width >= limits->width) ship->position->x = limits->width - ship->dimension->width - 1;
		
		// RENDERIZA E ATULIZA BALAS
		if(ship->bullets && ship->amountBullets > 0){
			for(unsigned int i = 0; i < ship->amountBullets; i++){
				renderBullet(ship->bullets[i]);
				if(updateBullet(ship->bullets[i])){
					gotoXY(ship->bullets[i]->position->x, ship->bullets[i]->position->y);
					printf(" ");
					
					ship->amountBullets--;
					free(ship->bullets[i]);
				}
			}	
		}
	}
}

/*
	Adiciona uma nova bala na nave
	parameters: SHIP *ship
	return: void
*/
void shoot(SHIP *ship){
	if(ship){
		BULLET *bullet = createBullet(ship->position->x + (ship->dimension->width / 2), ship->position->y - (ship->dimension->height / 2));
	
		if(bullet && ship->amountBullets < LIMIT_BULLETS){
			ship->amountBullets++;
			ship->bullets[ship->amountBullets - 1] = bullet;
		}
	}
}
