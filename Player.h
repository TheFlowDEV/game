#pragma once
#include <map>
#include <utility>
#include <Windows.h>
#include <vector>
#include <mutex>
#include <conio.h>
#include "Map.h"
#include <iostream>
#include "ConsoleFunctions.h"
using namespace std;
class Player {
private:
	pair<int, int> *player_coords;
	Map* mapGen;

	std::mutex& console_mutex;
	float move_interval=0.05f;
	std::chrono::steady_clock::time_point last_move_time;
	bool shouldntStop();
	void Move(int move);
	
public:
	bool canMove=true;
	Player(Map* map_ptr, pair<int, int>* coords,std::mutex &mutexss);
	void HandleKeyboardEvents();
	void GoToBattle();

};