#pragma once
#ifndef ITEM_H
#define ITEM_H
#include "Serialization.h"
#include <iostream>


enum TYPES { SWORD, BOW,SHIELD}; // Типы главного оружия
enum ACTIONS {HEAL,DAMAGE,RAISE_CHARACTERISTICS,RANDOM}; // Типы действий зелий
enum ITEM_TYPE {MAIN_WEAPON,SECOND_WEAPON}; // Типы предметов
class Player;
class Item {
	// Класс предмета
public:
	virtual ~Item() = default;// Виртуальный деструктор для правильной работы dynamic_cast
	int cost = 0;// цена
	ITEM_TYPE item_type; // тип предмета
	bool isDefined = false; // определён ли предмет?
	template<class Archive>// Сериализация
	void serialize(Archive& ar) {
		ar(isDefined);
	}
};
class MainWeapon: public Item {
	// Класс основного оружия
public:
	TYPES type; // Тип главного оружия
	MainWeapon(TYPES type); // Конструктор
	virtual std::pair<TYPES,int> Use() = 0; // Виртуальный метод для будущего переопределения. Использования оружия
	virtual std::string get_description() = 0; // Виртуальной метод для будущего переопределения. Возврат описания о предмете
	int GET_CLASS(); // Метод для получения 'класс' для основного оружия
	template<class Archive> // Сериализация
	void serialize(Archive& ar) {
		ar(cereal::base_class<Item>(this),type);
	}
};
class Weapon:public MainWeapon {
	// Класс для лука или меча
private:

	int Damage; // урон
	
public:
	template<class Archive> // Сериализация
	void serialize(Archive& ar) {
		ar(cereal::base_class<MainWeapon>(this), Damage);
	}
	Weapon() :MainWeapon(SWORD){}; // Пустой конструктор для правильной работы библиотеки для сериализации (НЕТ ПОДХОДЯЩЕГО КОНСТРУКТОРА ПО УМОЛЧАНИЮ)
	Weapon(TYPES type,bool start); // конструктор для класса оружия
    std::pair<TYPES,int> Use(); //  использование оружия
	std::string get_description(); // возврат описания о предмете


};
class Shield :public MainWeapon {
	// класс для щита
public:
	int Defense; // защита
	template<class Archive> // сериалищация
	void serialize(Archive& ar) {
		ar(cereal::base_class<MainWeapon>(this), Defense);

	};
	Shield():MainWeapon(SHIELD) {};// Пустой конструктор для правильной работы библиотеки для сериализации (НЕТ ПОДХОДЯЩЕГО КОНСТРУКТОРА ПО УМОЛЧАНИЮ)
	Shield(bool start);// конструктор для класса щит
	std::pair<TYPES, int> Use();//  использование щита
	std::string get_description();// возврат описания о предмете

};
class SecondaryWeapon:public Item {
	// Это класс, который описывает зелья 
public:
	template<class Archive> // Сериализация
	void serialize(Archive& ar) {
		ar(cereal::base_class<Item>(this),type, action_value);
	};
	int action_value;// сила действия
	ACTIONS type; // тип действия
	SecondaryWeapon(ACTIONS type,int action_value); // конструктор
	SecondaryWeapon();// Пустой конструктор для правильной работы библиотеки для сериализации (НЕТ ПОДХОДЯЩЕГО КОНСТРУКТОРА ПО УМОЛЧАНИЮ)
	void Drop(); // Метод, который устанавливает значение IsDefined в false(Зелье уже использовано)
	bool AreYouExist(); // Метод, который возвращает значение isDefined.

};
CEREAL_REGISTER_TYPE(Weapon) //Для правильной сериализации полиморфных классов
CEREAL_REGISTER_TYPE(Shield) //Для правильной сериализации полиморфных классов
#endif
