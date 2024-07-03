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
std::mutex console_mutex;

enum NXT_ACTIONS{BATTLE,NEXT_ETAGE};

class Game
{
private:
	std::map<string, bool> emitter{ {"special",false},{"chest",false},{"regen",false},{"exit",false} };
	Player player = Player(console_mutex,emitter);
	Map map = Map();
	long long seed;
	int current_etage=0;
	void ShowRecords();
	void draw_game(bool first_start);
	void redraw_start_screen(int choose);

	void draw_start_screen();
public:
	void Initialize();

};
int main();