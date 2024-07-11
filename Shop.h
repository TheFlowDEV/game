#pragma once
#include "Item.h"
class Shop {
	Item first_item;
	Item second_item;
	Item third_item;
	long long seed;
	void SetSeed(long long seed);
	void Generate();
	void Buy();
};