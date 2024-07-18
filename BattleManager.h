#pragma once
#include "ConsoleFunctions.h"
#include "Player.h"
#include "Enemy.h"
enum CHOICE {MAIN,MAINWEAPON,SECONDARYWEAPON}; // Перечисление, которое хранит состояния меню(Открыта главная страница,выбор главного оружия, выбор второстепенного оружия)
class BattleManager {
	/*
	Это класс, который "контроллирует" процесс битвы
	*/
private:
	Player& player; // ссылка на игрока
	int turn = 0; // счётчик ходов
	int defense_count = 0; // счётчик защиты для игрока( изменяется когда игрок применяет щит)
	int old_dexterity = player.dexterity, old_attack = player.attack, old_defense = player.defense; // параметры для того,чтобы откатить характеристики игрока к старым значениям после применения зелья
	bool used_secondary = false; // Использовано ли зелье, которое изменяет характеристики

	void enemy_turn(); // метод для хода противника
public:
	int choice; // указывает на то, какой пункт меню выбран( первый,второй и т.д.)
	CHOICE menu = MAIN; // В каком разделе меню находится игрок
	std::shared_ptr<Enemy> enemy = nullptr; // shared_ptr на объект класса Enemy
	BattleManager(Player& player); // конструктор, который инициализирует ссылку на игрока
	bool use_mainweapon(MainWeapon* weapon);
	/*
	Метод для использования главного оружия на противнике(и соответсвующего смены хода)

	weapon: MainWeapon*  - указатель на главное оружие

	Возвращает true, если противник в результате был убит
	*/
	bool use_secondary_weapon(SecondaryWeapon* weapon);
	/*
	Метод для использования  зелья(БЕЗ СМЕНЫ ХОДА)

	weapon: SecondaryWeapon*  - указатель на зелье

	Возвращает true, если противник в результате был убит
	*/
	void clear_bm();// метод для очистки объекта класса BattleManager(используется после окончания битвы)
	void run(); // метод для обработки 'побега' игрока от битвы
	void InitializeUI(); // Прорисовка окна боя
	void draw_player_stats(); // Прорисовка характеристик игрока
	void draw_enemy_stats(); // Прорисовка характеристик противника
};