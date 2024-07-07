#include "Item.h"
MainWeapon::MainWeapon(TYPES type) {
	this->type = type;
}

std::pair<TYPES,int> Weapon::Use() {
	std::pair<TYPES, int> ans = { this->type,this->Damage };
	return ans;
}
std::pair<TYPES, int> Shield::Use() {
	std::pair<TYPES, int> ans = { this->type,this->Defense};
	return ans;
}
int MainWeapon::GET_CLASS()
{
	switch (this->type) {
	case SWORD:
		return 0;
	case BOW:
		return 0;
	case SHIELD:
		return 1;

}
}
Weapon::Weapon(TYPES type,bool start):MainWeapon(type) {
	switch (type) {
	case SWORD:
		if (!start) this->Damage = rand() % 20;
		else this->Damage = 2;
		break;
	case BOW:
		if (!start) this->Damage = rand() % 15;
		else this->Damage = 1;
		break;
	}
}
Shield::Shield(bool start) :MainWeapon(SHIELD) {
	if (start) this->Defense = rand() % 20;
	else this->Defense = 2;
}

SecondaryWeapon::SecondaryWeapon(ACTIONS type) {
	this->type = type;
	this->IsDefined = true;
}
SecondaryWeapon::SecondaryWeapon()
{
	this->IsDefined = false;
}
