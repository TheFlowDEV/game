#pragma once
#include "Item.h"
#include "Player.h"
#include <memory>
class Shop {
private:
	Item* GenerateItem();
public:
	Item* first_item=nullptr;
	Item* second_item=nullptr;
	Item* third_item=nullptr;
	int& current_etage;
	int last_etage_generated = -1;
	Shop(int& cur_et);
	std::string GetDescription(Item* item);
	long long seed;
	void SetSeed(long long seed);
	void Generate();
	Item* Buy(int choice);
	void Clear();
};