#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Serialization.h"
#include <map>
#include <utility>
#include <Windows.h>
#include <vector>
#include <mutex>
#include "Item.h"
#include <conio.h>
#include "Map.h"
#include "map"
#include <iostream>
#include "ConsoleFunctions.h"
#include "Enemy.h"
//using boost::archive::archive_flags;
enum Moves{UP,DOWN,LEFT,RIGHT};
class Player {
private:
	Map* mapGen;
	std::map<std::string, bool>& emitter;
	std::map<std::string, std::pair<int, int>>& coords_emitter;

	std::unique_ptr<MainWeapon> first_weapon;
	std::unique_ptr<MainWeapon> second_weapon;
	std::unique_ptr<MainWeapon> third_weapon;
	SecondaryWeapon fs_weapon;
	SecondaryWeapon ss_weapon;
	

	

	int exp= 0,hp=20,money=0;

	int level = 0;

	int attack = 5;// атака
	int defense = 5; // защита
	int dexterity = 5; // ловкость

	std::mutex& console_mutex;
	float move_interval=0.12f;
	std::chrono::steady_clock::time_point last_move_time;
	bool shouldntStop();
	void Move(Moves move);
	
public:
	template<class Archive>
	void serialize(Archive& ar) {

		ar(level, exp, attack, defense, dexterity, first_weapon, second_weapon, third_weapon, fs_weapon, ss_weapon);

	}
	friend class Game;
	std::pair<int, int>* player_coords;
	bool ready = false;
	bool canMove=true;
	bool battlemode = false;
	bool lookinventory = false;
	bool chest_mode = false;
	//friend class boost::serialization::access;
	Player(std::mutex &mutexss,std::map<std::string,bool>& emit,std::map<std::string,std::pair<int,int>>& coords_emit);
	void UpdateMap(Map* map_ptr, std::pair<int, int>* coords);
	void HandleKeyboardEvents();
	void GoToBattle();
	void LevelUp();
	bool EnemyNearThePlayer();
	void GetDamage(ENEMY_TYPES enemy_type);

};
//BOOST_CLASS_IMPLEMENTATION(Player, boost::serialization::level_type::object_serializable)

#endif