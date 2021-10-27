#include "bullet.h"

/*
	Cria a estrutura da bala
	parameters: void
	return: BULLET
*/
BULLET *createBullet(unsigned short x, unsigned short y){
	BULLET *bullet = (BULLET*) calloc(1, sizeof(BULLET));
	
	if(bullet){
		bullet->body	 = '.';
		bullet->position = createPosition();
		bullet->position->x = x;
		bullet->position->y = y;
	}	
	
	return bullet;
}

/*
	Renderiza bala na tela
	parameters: void
	return: void
*/
void renderBullet(BULLET *bullet){
	if(bullet){
		gotoXY(bullet->position->x, bullet->position->y);
		printf("%c", bullet->body);
	}
}

/*
	Função que limpa a bala da tela
	parameters: BULLET *bullet
	return: void
*/
void clearBullet(BULLET *bullet){
	if(bullet){
		gotoXY(bullet->position->x, bullet->position->y);
		printf(" ");
	}
}

/*
	Atualiza posição da bala
	parameters: void
	return: bool
*/
bool updateBullet(BULLET *bullet, unsigned short width){
	if(bullet){
		clearBullet(bullet);
		
		bullet->position->y--;
		renderBullet(bullet);
		
		return (bullet->position->y <= width);
	}
	
	return false;
}
