#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;
enum TYPES { SWORD, BOW,SHIELD};
enum ACTIONS {HEAL,DAMAGE,RAISE_CHARACTERISTICS,RANDOM};

class Player;
class MainWeapon {
protected:
	string description;
public:
	TYPES type;
	MainWeapon(TYPES type);
	virtual std::pair<TYPES,int> Use() = 0;
	int GET_CLASS();
};
class Weapon:public MainWeapon {
private:
	int Damage;
public:
	Weapon(TYPES type,bool start);
    std::pair<TYPES,int> Use();
};
class Shield :public MainWeapon {
private:
	int Defense;
public:
	Shield(bool start);
	std::pair<TYPES, int> Use();
};
class SecondaryWeapon {
private:
	ACTIONS type;
	bool IsDefined;
public:
	SecondaryWeapon(ACTIONS type);
	SecondaryWeapon();
	int Use(Player* player);
	bool AreYouExist();

};
#endif