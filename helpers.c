#include "helpers.h"

SIZE *createSize();

/*
	Cria uma posição
	parameters: void
	return: POSITION
*/
POSITION *createPosition(){
	POSITION *position = (POSITION*) calloc(1, sizeof(POSITION));
	
	position->x = 0;
	position->y = 0;
	
	return position;
}

/*
	Cria uma dimensão
	parameters: void
	return: DIMENSION
*/
DIMENSION *createDimension(){
	DIMENSION *dimension = (DIMENSION*) calloc(1, sizeof(DIMENSION));
	
	dimension->width = 0;
	dimension->height = 0;
	
	return dimension;
}

/*
	Posiciona o cursor do mouse numa posição indicada
	parameters: unsigned int x, unsigned int y
	return: void
*/
void gotoXY(unsigned int x, unsigned int y){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coords = {x, y};
	
	SetConsoleCursorPosition(hStdout, coords);
}

/*
	Oculta o cursor
	parameters: void
	return: void
*/
void hideCursor(){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = {1, FALSE};
	SetConsoleCursorInfo(hStdout, &cursor);
}

/*
	Define o tamanho da janela
	parameters: void
	return: void
*/
void setWindowDimension(unsigned int width, unsigned int height){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT sr;
	COORD consoleSize;

	consoleSize.X = width; 
	consoleSize.Y = height;

	sr.Top = sr.Left = 0;
	sr.Right = width - 1;
	sr.Bottom = height - 1;

	SetConsoleWindowInfo(hStdout, TRUE, &sr);
	SetConsoleScreenBufferSize(hStdout, consoleSize);
}
