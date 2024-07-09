#pragma once
#ifndef ITEM_H
#define ITEM_H
#include "Serialization.h"
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
	template<class Archive>
	void serialize(Archive& ar) {
		ar(type);
	}
};
class Weapon:public MainWeapon {
private:
	//friend class boost::serialization::access;
	int Damage;
	
public:
	template<class Archive>
	void serialize(Archive& ar) {
		ar(cereal::base_class<MainWeapon>(this), Damage);
	}
	Weapon() :MainWeapon(SWORD){};
	Weapon(TYPES type,bool start);
    std::pair<TYPES,int> Use();
	std::string get_description();


};
class Shield :public MainWeapon {
private:
	//friend class boost::serialization::access;
	int Defense;
	
public:
	template<class Archive>
	void serialize(Archive& ar) {
		ar(cereal::base_class<MainWeapon>(this), Defense);

	};
	Shield():MainWeapon(SHIELD) {};
	Shield(bool start);
	std::pair<TYPES, int> Use();
	std::string get_description();

};
class SecondaryWeapon {
private:
	//friend class boost::serialization::access;
	bool IsDefined;
	
public:
	template<class Archive>
	void serialize(Archive& ar) {
		ar(IsDefined, type, action_value);
	};
	int action_value;
	ACTIONS type;
	SecondaryWeapon(ACTIONS type,int action_value);
	SecondaryWeapon();
	int Use(Player* player);
	bool AreYouExist();

};
CEREAL_REGISTER_TYPE(Weapon)
CEREAL_REGISTER_TYPE(Shield)
#endif
