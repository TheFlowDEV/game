#pragma once
#ifndef ITEM_H
#define ITEM_H
#include "Serialization.h"
#include <iostream>


enum TYPES { SWORD, BOW,SHIELD};
enum ACTIONS {HEAL,DAMAGE,RAISE_CHARACTERISTICS,RANDOM};
enum ITEM_TYPE {MAIN_WEAPON,SECOND_WEAPON};
class Player;
class Item {
public:
	virtual ~Item() = default;
	int cost = 0;
	ITEM_TYPE item_type;
	bool isDefined = false;
	template<class Archive>
	void serialize(Archive& ar) {
		ar(isDefined);
	}
};
class MainWeapon: public Item {
public:
	TYPES type;
	MainWeapon(TYPES type);
	virtual std::pair<TYPES,int> Use() = 0;
	virtual std::string get_description() = 0;
	int GET_CLASS();
	template<class Archive>
	void serialize(Archive& ar) {
		ar(cereal::base_class<Item>(this),type);
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
	//friend class boost::serialization::access;
private:

public:
	int Defense;
	template<class Archive>
	void serialize(Archive& ar) {
		ar(cereal::base_class<MainWeapon>(this), Defense);

	};
	Shield():MainWeapon(SHIELD) {};
	Shield(bool start);
	std::pair<TYPES, int> Use();
	std::string get_description();

};
class SecondaryWeapon:public Item {
	//friend class boost::serialization::access;
public:
	template<class Archive>
	void serialize(Archive& ar) {
		ar(cereal::base_class<Item>(this),type, action_value);
	};
	int action_value;
	ACTIONS type;
	SecondaryWeapon(ACTIONS type,int action_value);
	SecondaryWeapon();
	void Drop();
	bool AreYouExist();

};
CEREAL_REGISTER_TYPE(Weapon)
CEREAL_REGISTER_TYPE(Shield)
#endif
