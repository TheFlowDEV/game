#pragma once
#include "Item.h"
#include "Player.h"
#include <memory>
class Shop {
private:
	Item* GenerateItem(); // Генерация предметов в магазине
public:
	Item* first_item=nullptr;
	Item* second_item=nullptr;
	Item* third_item=nullptr;
	int& current_etage; //ссылка на текущий этаж
	int last_etage_generated = -1; // последний этаж на котором генерировали
	Shop(int& cur_et);// конструктор
	std::string GetDescription(Item* item);// получить описание предмета
	long long seed;// 'семя' для генерации предметов в магазине
	void SetSeed(long long seed);// установить семя
	void Generate();//метод для генерации
	Item* Buy(int choice);// Метод для 'покупки предмета'
	void Clear();// очистка магазина(а конкретно first_item,second_item,third_item)
};