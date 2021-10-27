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
		
		for(unsigned int i = 0; i < LIMIT_BULLETS; i++) ship->bullets[i] = NULL;
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
			setbuf(stdin, NULL);
			
			// ATUALIZA A POSIÇÃO DA NAVE	
			switch(key){
				case UP:
					clearShip(ship);
					ship->position->y -= ship->speed;
					break;
				case RIGHT:
					clearShip(ship);
					ship->position->x += ship->speed;
					break;
				case DOWN:
					clearShip(ship);
					ship->position->y += ship->speed;
					break;
				case LEFT:
					clearShip(ship);
					ship->position->x -= ship->speed;
					break;
				case SPACE:
					shoot(ship);
					break;
			}
			
			if(key != SPACE){
				// VERIFICA SE A NAVE ÚLTRAPASSOU OS LIMITES DA TELA
				if(ship->position->y <= HEIGHT_MENU) ship->position->y = HEIGHT_MENU + 1;
				if(ship->position->x <= 0) ship->position->x = 1;
				
				if(ship->position->y + ship->dimension->height >= limits->height) ship->position->y = limits->height - ship->dimension->height - 1;
				if(ship->position->x + ship->dimension->width >= limits->width) ship->position->x = limits->width - ship->dimension->width - 1;
				
				// RENDERIZA NAVE
				renderShip(ship);
			}
		}
		
		// RENDERIZA E ATULIZA BALAS
		if(ship->bullets && ship->amountBullets > 0){
			for(unsigned int i = 0; i < LIMIT_BULLETS; i++){
				// VERIFICA SE A BALA NÃO É NULA
				if(ship->bullets[i]){
					renderBullet(ship->bullets[i]);
					
					// SE A BALA ÚLTRAPASSOU OS LIMITES DA TELA, ELA SERÁ REMOVIDA
					if(updateBullet(ship->bullets[i], HEIGHT_MENU)){
						clearBullet(ship->bullets[i]);
						
						ship->amountBullets--;
						ship->bullets[i] = NULL;
					}
				}
			}	
		}
	}
}

/*
	Dispara uma bala da nave
	parameters: SHIP *ship
	return: void
*/
void shoot(SHIP *ship){
	if(ship && ship->amountBullets < LIMIT_BULLETS && ship->position->y > HEIGHT_MENU + 1){
		BULLET *bullet = createBullet(ship->position->x + (ship->dimension->width / 2), ship->position->y - (ship->dimension->height / 2));
	
		if(bullet && ship->amountBullets < LIMIT_BULLETS){
			for(unsigned int i = 0; i < LIMIT_BULLETS; i++){
				// VERIFICA SE A BALA É NULA
				if(ship->bullets[i] == NULL){
					ship->bullets[i] = bullet;
					ship->amountBullets++;
					break;
				}
			}
		}
	}
}
