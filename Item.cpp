#include "Item.h"
#include <string>
MainWeapon::MainWeapon(TYPES type) {
	item_type = MAIN_WEAPON;
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
std::string Weapon::get_description() {
	return u8"Атака:"+std::to_string(this->Damage);
}
std::string Shield::get_description() {
	return u8"Защита:"+ std::to_string(this->Defense);
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
	isDefined = true;
}
Shield::Shield(bool start) :MainWeapon(SHIELD) {
	if (start)  this->Defense = 2;
	else this->Defense = rand() % 20 + 2;
	isDefined = true;
}

SecondaryWeapon::SecondaryWeapon(ACTIONS type,int action_value) {
	this->type = type;
	item_type = SECOND_WEAPON;
	this->isDefined = true;
	this->action_value = action_value;
}
SecondaryWeapon::SecondaryWeapon()
{
	this->isDefined = false;
}
bool SecondaryWeapon::AreYouExist() {
	return this->isDefined;
}
void SecondaryWeapon::Drop() {
	this->isDefined = false;
}
