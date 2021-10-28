#include "helpers.h"

SIZE *createSize();

/*
	Cria uma posi��o
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
	Cria uma dimens�o
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
	Posiciona o cursor do mouse numa posi��o indicada
	parameters: unsigned short x, unsigned short y
	return: void
*/
void gotoXY(unsigned short x, unsigned short y){
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
	parameters: unsigned short width, unsigned short height
	return: void
*/
void setWindowDimension(unsigned short width, unsigned short height){
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
