#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <map>
#include <utility>
#include <Windows.h>
#include <vector>
#include <mutex>
#include "Item.h"
#include <conio.h>
#include "Map.h"
#include <iostream>
#include "ConsoleFunctions.h"
#include "Enemy.h"

using namespace std;
class Player {
private:
	pair<int, int> *player_coords;
	Map* mapGen;
	/*
	MainWeapon first_weapon = MainWeapon();
	MainWeapon second_weapon = MainWeapon();
	MainWeapon third_weapon = MainWeapon();
	SecondaryWeapon fs_weapon = SecondaryWeapon();
	SecondaryWeapon ss_weapon = SecondaryWeapon();
	*/

	bool battlemode=false;
	bool lookinventory = false;

	int exp= 0,hp=20,money=0;

	int level = 0;

	int attack = 5;// атака
	int defense = 5; // защита
	int dexterity = 5; // ловкость

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
	void LevelUp();
	//char NearThePlayer();
	void GetDamage(ENEMY_TYPES enemy_type);

};
#endif