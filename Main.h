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
#include "Player.h"
#include "Enemy_Thread_Handler.h"
#include "ConsoleFunctions.h"
#include <mutex>
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