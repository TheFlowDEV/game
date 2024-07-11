#include "ConsoleFunctions.h"
#include "BattleManager.h"
#include <fstream>
#include <sstream>
BattleManager::BattleManager(Player& players):player(players) {
}
void BattleManager::enemy_turn() {
	if (turn % 2 == 1) {
		player.GetDamage(enemy->UseDamage(turn)-defense_count);
		defense_count = 0;
		if (used_secondary) {
			player.dexterity = old_dexterity;
			player.defense = old_defense;
			player.attack = old_attack;
		}
		draw_player_stats();
		if (player.hp <= 0) {
			clear();
			std::cout << "ÈÃÐÀ ÎÊÎÍ×ÅÍÀ! ÊÑÒÀÒÈ, ÂÀØÈ ÑÎÕÐÀÍÅÍÈß ÓÄÀËÅÍÛ ÒÎÆÅ! ÕÎÐÎØÅÃÎ ÄÍß!";
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
			remove("player.sav");
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
		defense_count = reinterpret_cast<Shield*>(weapon)->Use().second;
		SetXY(0, 5);
		std::cout << u8"Âû èñïîëüçîâàëè ùèò. Â ñëåäóþùåì õîäó áóäåò íà "<<defense_count<<u8" ìåíüøå óðîíà";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	else {
		int old_hp = enemy->hp;
		defeat = enemy->GetDamage(weapon->type, reinterpret_cast<Weapon*>(weapon)->Use().second+player.attack/2);
		SetXY(0, 5);
		std::cout << u8"Âðàãó íàíåñëè " << old_hp - enemy->hp << u8" åäèíèö óðîíà";
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		if (defeat) {
			if (old_attack != 0) {
				player.attack = old_attack;
				player.dexterity = old_dexterity;
				player.defense = old_defense;
			}
			player.Win();
			return true;
		}
	}
	if (!defeat) {
		draw_enemy_stats();
		turn++;
		enemy_turn();
		return false;
	}
}
bool BattleManager::use_secondary_weapon(SecondaryWeapon* weapon_ptr) {
	SecondaryWeapon& weapon = *(weapon_ptr);
	bool defeat = false;
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
			std::cout << u8"Âðàãó íàíåñëè " << old_hp-enemy->hp << u8" åäèíèö óðîíà";
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
	if (rand() % player.dexterity==0) {
		clear();
		std::cout << u8"Âû ñáåæàëè!";
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		player.run_from_battle();
	}
	else {
		SetXY(0, 5);
		std::cout << u8"Ó âàñ, ê ñîæàëåíèþ, íè÷åãî íå âûøëî";
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		std::cout << "                                    ";
		std::cout << u8"Îæèäàåì ñëåäóþùåãî äåéñòâèÿ";

	}
}
void BattleManager::InitializeUI() {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetXY(0, 0);
	SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
	std::cout << u8"Èñïîëüçîâàòü ãëàâíîå îðóæèå";
	SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
	SetXY(0, 1);
	std::cout << u8"Èñïîëüçîâàòü âòîðîñòåïåííîå îðóæèå";
	SetXY(0, 2);
	std::cout << u8"Ñáåæàòü";
	draw_player_stats();
	draw_enemy_stats();
}
void BattleManager::draw_player_stats() {
	SetXY(0, 6);
	std::stringstream stats;
	stats << u8"ÈÃÐÎÊ ";
	stats << u8"ÎÇ:" << player.hp << u8" ÀÒÊ/ËÂÊ/ÇÀÙ:" << player.attack << "/" << player.dexterity << "/" << player.defense;
	std::cout << stats.str();
}
void BattleManager::draw_enemy_stats() {
	SetXY(0, 7);
	std::stringstream stats;
	stats << u8"ÂÐÀÃ ";
	stats << u8"ÎÇ:" << enemy->hp << u8" ÒÈÏ:";
	switch (enemy->type) {
	case ICE_GOLEM:
		stats << u8"ËÅÄßÍÎÉ ÃÎËÅÌ";
		break;
	case ORK:
		stats << u8"ÎÐÊ";
		break;
	case BAT:
		stats << u8"ËÅÒÓ×Àß ÌÛØÜ";
		break;
	case ZOMBIE:
		stats << u8"ÇÎÌÁÈ";
		break;
	case SKELETON:
		stats << u8"ÑÊÅËÅÒ";
		break;
	case THEBOSS:
		stats << u8"ÁÎÑÑ";
		break;
	}
	std::cout << stats.str();
}