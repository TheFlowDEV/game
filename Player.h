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

class BattleManager;
enum Moves{UP,DOWN,LEFT,RIGHT}; // перечисление для движений игрока по карте
class Player {
private:
	BattleManager& bm;//Ссылка на объект класса BattleManager
	Map* mapGen;
	std::map<std::string, bool>& emitter; // ссылка на emitter из Main.h
	std::map<std::string, std::pair<int, int>>& coords_emitter; // Ссылка на coords_emitter из Main.h
	

	


	std::mutex& console_mutex; // Ссылка на мьютекс из Main.h
	float move_interval=0.12f;// интервал между передвижениями игрока
	std::chrono::steady_clock::time_point last_move_time; // последнее время движения игрока
	bool shouldntStop(); // метод, который возвращает true - если игрок может двигаться. Зависит от move_interval
	void Move(Moves move); // Метод для движения игрока по карте
	
public:
	std::unique_ptr<MainWeapon> first_weapon; // Указатель на основное оружие
	std::unique_ptr<MainWeapon> second_weapon;
	std::unique_ptr<MainWeapon> third_weapon;
	SecondaryWeapon fs_weapon; // Зелье
	SecondaryWeapon ss_weapon;

	int exp = 0, hp = 20, money = 0;// очки опыта,здоровья и деньги

	int level = 0; // уровень игрока

	int attack = 2;// атака
	int defense = 1; // защита
	int dexterity = 3; // ловкость

	template<class Archive> // сериализация
	void serialize(Archive& ar) {

		ar(level, hp, exp, money, attack, defense, dexterity, first_weapon, second_weapon, third_weapon, fs_weapon, ss_weapon);

	}
	friend class Game;
	std::pair<int, int>* player_coords; // указатель  на координаты игрока

	bool ready = false; // готов ли игрок взаимодейстовать с игрой
	bool canMove=true; // готов ли игрок двигаться
	bool battlemode = false; // Режим битвы?
	bool lookinventory = false; // Открыт ли сейчас инвентарь?
	Player(std::mutex &mutexss,std::map<std::string,bool>& emit,std::map<std::string,std::pair<int,int>>& coords_emit,BattleManager& bms); // конструктор
	void UpdateMap(Map* map_ptr, std::pair<int, int>* coords); // обновление карты и координаты игрока
	void HandleKeyboardEvents();// обработка нажатий игрока
	void LevelUp();// повышение уровня и характеристик
	std::string GetWeaponDescription(MainWeapon* weapon); // получить описание главного оружия(для магазина)
	std::string GetWeaponDescription(SecondaryWeapon* weapon); // получить описание зелья(для магазина)

	bool EnemyNearThePlayer(); // рядом ли враг?
	void GetDamage(int damage);// Метод для получения урона
	void Win();// Метод для отрисовки окна победы и присвоения награды
	void run_from_battle();// Метод для побега из битвы
	void reinitialize(); // Переинициализация игрока при старте новой игры
};

#endif