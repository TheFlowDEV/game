#pragma once
enum TYPES { SWORD, BOW,SHIELD};
enum ACTIONS {HEAL,DAMAGE,RAISE_CHARACTERISTICS,RANDOM};
class MainWeapon {
public:
	TYPES type;
};
class Weapon:MainWeapon {
	int Damage;
	Weapon();
	int Hit();
};
class Shield :MainWeapon {
	int Defense;
	Shield();
	int Defend();
};
class SecondaryWeapon {
	ACTIONS type;
	SecondaryWeapon();
	int Use();
};