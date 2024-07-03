#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;
enum TYPES { SWORD, BOW,SHIELD};
enum ACTIONS {HEAL,DAMAGE,RAISE_CHARACTERISTICS,RANDOM};
class Player;
class MainWeapon {
private:
	TYPES type;
public:
	MainWeapon(TYPES type);
	MainWeapon();
};
class Weapon:MainWeapon {
private:
	int Damage;
public:
	Weapon(TYPES type);
	int Hit();
};
class Shield :MainWeapon {
private:
	int Defense;
public:
	Shield(TYPES type);
	int Defend();
};
class SecondaryWeapon {
private:
	ACTIONS type;
public:
	SecondaryWeapon(ACTIONS type);
	SecondaryWeapon();
	int Use(Player* player);
};
#endif