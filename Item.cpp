#include "Item.h"
MainWeapon::MainWeapon(TYPES type) {
	this->type = type;
}
Weapon::Weapon(TYPES type):MainWeapon(type) {
	switch (type) {
	case SWORD:
		this->Damage = rand() % 20;
		break;
	case BOW:
		this->Damage = rand() % 15;
		break;
	}
}
MainWeapon::MainWeapon() {}
SecondaryWeapon::SecondaryWeapon(){}