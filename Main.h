#pragma once
#include "Serialization.h"
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
#pragma comment(lib, "Winmm.lib")

enum NXT_ACTIONS{BATTLE,NEXT_ETAGE};
void draw_frame(short x,short y);
void draw_frame(short x, short y,MainWeapon* weapon);
void draw_frame(short x, short y, SecondaryWeapon* weapon);
class Game
{
private:
	std::map<std::string, bool> emitter{ {"special",false},{"chest",false},{"regen",false},{"exit",false},{"shop",false},{"inventory",false} };
	std::map<std::string, std::pair<int, int>>coords_emitter{ {"chest",{0,0}}};
	Player player = Player(console_mutex,emitter,coords_emitter);
	Map map = Map();
	long long seed;
	int current_etage=0;
	void ShowRecords();
	void draw_game(bool first_start);
	void redraw_start_screen(int choose);
	void draw_start_screen();
	void redraw_map(bool regenerate);
	void load_game(std::ifstream &file);
	void load_game_choice(std::ifstream &file);
	void save_game();
public:
	void Initialize();

};
int main();