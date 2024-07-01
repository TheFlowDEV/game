#pragma once
#include <Windows.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <map>
#include "Map.h"
#include "Enemy_Thread_Handler.h"
#include <mutex>
void SetXY(short X, short Y);
void clear();
class Game
{
private:
	void ShowRecords();
	void draw_game();
	void redraw_start_screen(int choose);

	void draw_start_screen();
public:
	void Initialize();

};
int main();