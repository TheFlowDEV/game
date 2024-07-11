#include "Shop.h"
#include <vector>
void Shop::SetSeed(long long seed) {
	this->seed = seed;
}
Item* Shop::Buy(int choice) {
	switch (choice) {
	case 0:
		return first_item;
	case 1:
		return second_item;
	case 2:
		return third_item;
	}
}
void Shop::Generate() {
	if (last_etage_generated != current_etage) {
		last_etage_generated = current_etage;
		
		first_item = GenerateItem();
		second_item = GenerateItem();
		third_item = GenerateItem();
	}
}
Item* Shop::GenerateItem() {
	int rand_num = rand();
	if (rand_num % 2 == 0) {
		//���������� MainWeapon
		if (seed + rand() % 3 == 1) {// ��� 
			Item* shield = new Shield(false);
			shield->cost = rand() % 100 + 100;
			return shield;
		}
		else {// ��� ��� ���
			if ((seed / 2 + rand()) % 2 == 0) {
				Item* sword = new Weapon(SWORD, false);
				sword->cost = rand() % 100 + 90;
				return sword;

			}
			else {
				Item* bow = new Weapon(BOW, false);
				bow->cost = rand() % 100 + 95;

				return bow;
			}
		}
	}
	else {
		//���������� SecondaryWeapon
		Item* potion = new SecondaryWeapon(static_cast<ACTIONS>((seed + rand()) % 4), rand() % 30);
		potion->cost = rand() % 50 + 190;
		return potion;
	}
}
std::string Shop::GetDescription(Item* item) {
	if (item == nullptr) {
		return u8"������ ������";
	}
	if (item->item_type == MAIN_WEAPON) {
		MainWeapon* weapon = static_cast<MainWeapon*>(item);
		std::stringstream fw_description;
		if (weapon->isDefined) {
			switch (weapon->type) {
			case SWORD:
				fw_description << u8"��� ";
				break;
			case BOW:
				fw_description << u8"��� ";
				break;
			case SHIELD:
				fw_description << u8"��� ������� " << static_cast<Shield*>(weapon)->Defense;
				break;
			}
			if (!(weapon->type == SHIELD)) {
				fw_description << u8"����� ";
				fw_description << static_cast<Weapon*>(weapon)->Use().second;
				fw_description << u8" ����� " << item->cost;
			}
			return fw_description.str();
		}
		else {
			return  u8"������ ������";
		}
	}
	else {
		SecondaryWeapon* weapon = dynamic_cast<SecondaryWeapon*>(item);
		std::stringstream fw_description;
		if (weapon->AreYouExist()) {
			switch (weapon->type) {
			case HEAL:
				fw_description << u8"������� ";
				break;
			case DAMAGE:
				fw_description << u8"���� ";
				break;
			case RAISE_CHARACTERISTICS:
				fw_description << u8"��������� ������������� ";
				break;
			case RANDOM:
				fw_description << u8"��������� �������� ";
				break;
			}
			fw_description << u8"����� " << weapon->action_value <<u8" ����� "<<item->cost;
			return fw_description.str();
		}
		else {
			return u8"������ ������";
		}
	}
}
Shop::Shop(int& cur_et):current_etage(cur_et) {
}
void Shop::Clear()
{
	delete first_item;
	delete second_item;
	delete third_item;
	first_item= nullptr;
	second_item=nullptr;
	third_item=nullptr;
}