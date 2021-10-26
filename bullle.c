#include "bullet.h"

/*
	Cria a estrutura da bala
	parameters: void
	return: BULLET
*/
BULLET *createBullet(unsigned short x, unsigned short y){
	BULLET *bullet = (BULLET*) calloc(1, sizeof(BULLET));
	
	if(bullet){
		bullet->caractere = 2;
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
		printf("%c", bullet->caractere);
	}
}

/*
	Atualiza posição da bala
	parameters: void
	return: void
*/
bool updateBullet(BULLET *bullet){
	if(bullet){
		gotoXY(bullet->position->x, bullet->position->y);
		printf(" ");
		
		bullet->position->y--;
		gotoXY(bullet->position->x, bullet->position->y);
		printf("%c", bullet->caractere);
		
		return (bullet->position->y == 0);
	}
	
	return false;
}
