#include "ConsoleFunctions.h"
#include "BattleManager.h"
#include <fstream>
#include <sstream>
//смотрите описание также в BattleManager.h
BattleManager::BattleManager(Player& players):player(players) {
}
void BattleManager::enemy_turn() {// ход противника
	if (turn % 2 == 1) {//если действительно ход противника
		player.GetDamage(enemy->UseDamage(turn) - defense_count <= 0 ? 0: enemy->UseDamage(turn) - defense_count);
		defense_count = 0;
		if (used_secondary) {
			player.dexterity = old_dexterity;
			player.defense = old_defense;
			player.attack = old_attack;
		}
		draw_player_stats();
		if (player.hp <= 0) {//игрок умер
			clear();
			std::cout << u8"ИГРА ОКОНЧЕНА! КСТАТИ, ВАШИ СОХРАНЕНИЯ УДАЛЕНЫ ТОЖЕ! ХОРОШЕГО ДНЯ!";
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			remove("player.sav");// удаляем сохранение
			exit(0);
		}

		turn++;
	}
}


void BattleManager::clear_bm() {
	this->enemy = nullptr;
	this->turn = 0;
	this->menu = MAIN;
}
bool BattleManager::use_mainweapon(MainWeapon* weapon) {
	bool defeat = false;
	if (weapon->type == SHIELD) {
		defense_count = reinterpret_cast<Shield*>(weapon)->Use().second;//получаем защиту от щита
		SetXY(0, 5);
		std::cout << u8"Вы использовали щит. В следующем ходу будет на "<<defense_count<<u8" меньше урона";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	else {
		int old_hp = enemy->hp;
		defeat = enemy->GetDamage(weapon->type, reinterpret_cast<Weapon*>(weapon)->Use().second+player.attack/2);
		SetXY(0, 5);
		std::cout << u8"Врагу нанесли " << old_hp - enemy->hp << u8" единиц урона";//считаем урон
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (defeat) {//враг побеждён?
			if (old_attack != 0) {//возвращаем значения к старым
				player.attack = old_attack;
				player.dexterity = old_dexterity;
				player.defense = old_defense;
			}
			player.Win();//игрок выиграл
			return true;
		}
	}
	if (!defeat) {
		//игра продолжается
		draw_enemy_stats();
		turn++;
		enemy_turn();
		return false;
	}
}
bool BattleManager::use_secondary_weapon(SecondaryWeapon* weapon_ptr) {
	SecondaryWeapon& weapon = *(weapon_ptr);
	bool defeat = false;
	//использование зелий
	switch (weapon.type) {
	case HEAL:
		player.hp += weapon.action_value;
		break;
	case DAMAGE:
		defeat = enemy->GetDamageByPotion(weapon.action_value);
		break;
	case RAISE_CHARACTERISTICS:
		
		old_attack = player.attack;
		old_dexterity = player.dexterity;
		old_defense = player.defense;
		
		player.attack += weapon.action_value;
		player.dexterity += weapon.action_value;
		player.defense += weapon.action_value;
		used_secondary = true;

		break;
	case RANDOM:
		int rand_num = rand()%4;
		switch (rand_num) {
		case 0:
			player.hp += weapon.action_value;
			break;
		case 1:
		{
			int old_hp = enemy->hp;
			defeat = enemy->GetDamageByPotion(weapon.action_value);

			SetXY(0, 5);
			std::cout << u8"Врагу нанесли " << old_hp-enemy->hp << u8" единиц урона";
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			break;
		}
		case 2:
			old_attack = player.attack;
			old_dexterity = player.dexterity;
			old_defense = player.defense;
			player.attack += weapon.action_value;
			player.dexterity += weapon.action_value;
			player.defense += weapon.action_value;
			used_secondary = true;
			break;
		}
	}
	weapon.Drop();

	if (defeat) {
		if (old_attack != 0) {
			player.attack = old_attack;
			player.dexterity = old_dexterity;
			player.defense = old_defense;
		}
		player.Win();
		return true;
	}
	else {
		draw_player_stats();
		draw_enemy_stats();
		return false;
	}
}
void BattleManager::run() {
	//побег игрока
	if (rand() % player.dexterity==0 && enemy->type!=THEBOSS) {
		clear();
		std::cout << u8"Вы сбежали!";
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		player.run_from_battle();
	}
	else {
		SetXY(0, 5);
		std::cout << u8"У вас, к сожалению, ничего не вышло";
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		std::cout << "                                    ";
		turn++;
		enemy_turn();

	}
}
void BattleManager::InitializeUI() {
	//отрисовка окна битвы
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetXY(0, 0);
	SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
	std::cout << u8"Использовать главное оружие";
	SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
	SetXY(0, 1);
	std::cout << u8"Использовать второстепенное оружие";
	SetXY(0, 2);
	std::cout << u8"Сбежать";
	draw_player_stats();
	draw_enemy_stats();
}
void BattleManager::draw_player_stats() {
	SetXY(0, 6);
	std::stringstream stats;
	stats << u8"ИГРОК ";
	stats << u8"ОЗ:" << player.hp << u8" АТК/ЛВК/ЗАЩ:" << player.attack << "/" << player.dexterity << "/" << player.defense;
	std::cout << stats.str();
}
void BattleManager::draw_enemy_stats() {
	SetXY(0, 7);
	std::stringstream stats;
	stats << u8"ВРАГ ";
	stats << u8"ОЗ:" << enemy->hp << u8" ТИП:";
	switch (enemy->type) {
	case ICE_GOLEM:
		stats << u8"ЛЕДЯНОЙ ГОЛЕМ";
		break;
	case ORK:
		stats << u8"ОРК";
		break;
	case BAT:
		stats << u8"ЛЕТУЧАЯ МЫШЬ";
		break;
	case ZOMBIE:
		stats << u8"ЗОМБИ";
		break;
	case SKELETON:
		stats << u8"СКЕЛЕТ";
		break;
	case THEBOSS:
		stats << u8"БОСС";
		break;
	}
	std::cout << stats.str();
}