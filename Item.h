#pragma once
#ifndef ITEM_H
#define ITEM_H
#include <iostream>
enum TYPES { SWORD, BOW,SHIELD};
enum ACTIONS {HEAL,DAMAGE,RAISE_CHARACTERISTICS,RANDOM};

class Player;
class MainWeapon {
public:
	TYPES type;
	MainWeapon(TYPES type);
	virtual std::pair<TYPES,int> Use() = 0;
	virtual std::string get_description() = 0;
	int GET_CLASS();
};
class Weapon:public MainWeapon {
private:
	int Damage;
public:
	Weapon(TYPES type,bool start);
    std::pair<TYPES,int> Use();
	std::string get_description();

};
class Shield :public MainWeapon {
private:
	int Defense;
public:
	Shield(bool start);
	std::pair<TYPES, int> Use();
	std::string get_description();

};
class SecondaryWeapon {
private:
	ACTIONS type;
	bool IsDefined;
	int action_value;
public:
	SecondaryWeapon(ACTIONS type,int action_value);
	SecondaryWeapon();
	int Use(Player* player);
	bool AreYouExist();

};
#endif