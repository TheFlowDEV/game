#pragma once
#include "Serialization.h"
#include <Windows.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <map>
#include "Map.h"
#include "Shop.h"
#include "BattleManager.h"
#include "Player.h"
#include "Enemy_Thread_Handler.h"
#include "ConsoleFunctions.h"
#include <mutex>
std::mutex console_mutex; // консольный мьютекс для синхронизации потоков при обращении к консоли
#pragma comment(lib, "Winmm.lib")

void draw_frame(short x,short y);
/*
	Функция для отрисовки рамки для предмета в инвентаре
	x:short - Координата X левого верхнего угла окна
	y:short - Координата Y левого верхнего угла окна
*/
void draw_frame(short x, short y,MainWeapon* weapon);
/*
	Функция для отрисовки оружия в рамке в инвентаре
	x:short - Координата X левого верхнего угла окна
	y:short - Координата Y левого верхнего угла окна
	weapon:MainWeapon* - Указатель на объект класса MainWeapon. Это основное оружие игрока
*/

void draw_frame(short x, short y, SecondaryWeapon* weapon);
/*
	Функция для отрисовки оружия в рамке в инвентаре
	x:short - Координата X левого верхнего угла окна
	y:short - Координата Y левого верхнего угла окна
	weapon:SecondaryWeapon* - Указатель на объект класса SecondaryWeapon. Это вспомогательное оружие игрока
	*/
class Game
{
private:
	std::map<std::string, bool> emitter{ {"special",false},{"chest",false},{"regen",false},{"exit",false},{"shop",false},{"inventory",false},{"battle_end",false} }; // Объект класса map, который сообщает о событиях, с которыми сталкивается игрок, основному игровому циклу
	std::map<std::string, std::pair<int, int>>coords_emitter{ {"chest",{0,0}}}; // Объект класса map, который сообщает о координатах столкновения(на данный момент только сундук)
	BattleManager bm = BattleManager(player);// Объект класса BattleManager, который отвечает за битву игрока с противником
	bool game_started = false; // Переменная, которая служит для того,чтобы обозначить, что игра уже запущена
	Player player = Player(console_mutex,emitter,coords_emitter,bm); // Объект класса Player(Игрок)
	int current_etage = 0;// Текущий этаж
	Map map = Map(current_etage);// Объект класса Map(карта)
	Shop shop= Shop(current_etage);// Объект класса Shop(магазин)
	long long seed= (clock() * rand()) + (clock() * (rand() + clock()));// переменная, отвечающая за случайность генерации предметов в магазине
	void ShowRecords();
	/*
	Функция для отрисовки рекордов
	*/
	void draw_game();
	/*
	Функция для отрисовки основной игры

	*/
	void redraw_start_screen(int choose);
	/*
	Функция для перерисовки стартового окна
	choose:int - какой пункт меню игрок выбрал

	*/
	void draw_start_screen();
	/*
	Функция для отрисовки стартового окна

	*/
	void redraw_map(bool regenerate);
	/*
	Функция для отрисовки карты игры
	regenerate:bool - стоит ли перегенерировать

	*/
	void load_game(std::ifstream &file);
	/*
	Функция для загрузки игры из сохранения
	file:std::ifstream& - ссылка на файл сохранения
	*/
	void load_game_choice(std::ifstream &file);
	/*
	Функция для отрисовки окна о загрузке игры
	file:std::ifstream& - ссылка на файл сохранения
	*/
	void save_game();
	/*
	Функция для сохранения игры
	*/
	void ChangeInventory(Item* item);
	/*
	Функция для изменения ячеек инвентаря при открытии сундука или покупке
	item:Item* - указатель на предмет, на который нужно сменить предмет из инвентаря
	
	*/

public:
	void Initialize();
	/*
	Функция для инициализации игры

	*/
};
int main();