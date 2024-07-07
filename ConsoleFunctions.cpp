#include "ConsoleFunctions.h"

void SetXY(short X, short Y) {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hout, coord);
}
void clear() {
	system("cls");
}
