#include "Player.h"
#include "BattleManager.h"
#include "locale"
void Player::Move(Moves move) {
	std::pair<int, int>& player_coords = *(this->player_coords);
	switch (move) {
	case UP:
		if (player_coords.second - 1 > 0 && mapGen->generated_map[player_coords.second - 1][player_coords.first] == '.') {

			console_mutex.lock();
			SetXY(player_coords.first, player_coords.second);
			mapGen->generated_map[player_coords.second][player_coords.first] = '.';
			std::cout << '.';

			SetXY(player_coords.first, player_coords.second - 1);
			player_coords.second -= 1;
			mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
			std::cout << u8"\u263A";
			console_mutex.unlock();
		}
		else {
			switch (mapGen->generated_map[player_coords.second - 1][player_coords.first])
			{
			case '$':
				coords_emitter["chest"] = { player_coords.first,player_coords.second - 1 };
				emitter["chest"] = true;
				emitter["special"] = true;
				break;
			case 'R':
				emitter["regen"] = true;
				emitter["special"] = true;
				break;
			case 'S':
				emitter["shop"] = true;
				emitter["special"] = true;
				break;
			}
		}
		break;
	case DOWN:
		if (player_coords.second + 1 < mapGen->map_height && mapGen->generated_map[player_coords.second + 1][player_coords.first] == '.') {
			console_mutex.lock();
			SetXY(player_coords.first, player_coords.second);
			mapGen->generated_map[player_coords.second][player_coords.first] = '.';
			std::cout << '.';
			SetXY(player_coords.first, player_coords.second + 1);
			player_coords.second += 1;
			mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
			std::cout << u8"\u263A";
			console_mutex.unlock();

		}
		else {
			switch (mapGen->generated_map[player_coords.second + 1][player_coords.first])
			{
			case '$':
				coords_emitter["chest"] = { player_coords.first,player_coords.second + 1 };
				emitter["chest"] = true;
				emitter["special"] = true;
				break;
			case 'R':
				emitter["regen"] = true;
				emitter["special"] = true;
				break;
			case 'S':
				emitter["shop"] = true;
				emitter["special"] = true;
				break;
			}
		}
		break;

	case LEFT:
		if (player_coords.second > 0 && mapGen->generated_map[player_coords.second][player_coords.first - 1] == '.') {
			console_mutex.lock();
			SetXY(player_coords.first, player_coords.second);
			mapGen->generated_map[player_coords.second][player_coords.first] = '.';
			std::cout << '.';
			SetXY(player_coords.first - 1, player_coords.second);
			player_coords.first -= 1;
			mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
			std::cout << u8"\u263A";
			console_mutex.unlock();

		}
		else {
			switch (mapGen->generated_map[player_coords.second][player_coords.first - 1])
			{
			case '$':
				coords_emitter["chest"] = { player_coords.first - 1,player_coords.second };
				emitter["chest"] = true;
				emitter["special"] = true;
				break;
			case 'R':
				emitter["regen"] = true;
				emitter["special"] = true;
				break;
			case 'S':
				emitter["shop"] = true;
				emitter["special"] = true;
				break;
			}
		}
		break;
	case RIGHT:
		if (player_coords.first + 1 < mapGen->map_width && mapGen->generated_map[player_coords.second][player_coords.first + 1] == '.') {
			console_mutex.lock();
			SetXY(player_coords.first, player_coords.second);
			mapGen->generated_map[player_coords.second][player_coords.first] = '.';
			std::cout << '.';
			player_coords.first += 1;
			mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
			mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
			SetXY(player_coords.first, player_coords.second);
			std::cout << u8"\u263A";
			console_mutex.unlock();

		}
		else {
			switch (mapGen->generated_map[player_coords.second][player_coords.first + 1])
			{
			case '$':
				coords_emitter["chest"] = { player_coords.first + 1,player_coords.second };
				emitter["chest"] = true;
				emitter["special"] = true;
				break;
			case 'R':
				emitter["regen"] = true;
				emitter["special"] = true;
				break;
			case 'S':
				emitter["shop"] = true;
				emitter["special"] = true;
				break;
			}
			break;
		}
	}
}

Player::Player(std::mutex& mutexss, std::map<std::string, bool>& emit, std::map<std::string, std::pair<int, int>>& coords_emit, BattleManager& bms) :console_mutex(mutexss), emitter(emit), coords_emitter(coords_emit),bm(bms) {
	first_weapon = std::make_unique<Weapon>(Weapon(SWORD, true));
	second_weapon = std::make_unique<Weapon>(Weapon(BOW, true));
	third_weapon = std::make_unique<Shield>(Shield(true));
	fs_weapon = SecondaryWeapon(RANDOM, 10);
}
void Player::UpdateMap(Map* map_ptr, std::pair<int, int>* coords) {
	this->player_coords = coords;
	this->mapGen = map_ptr;
}

void Player::HandleKeyboardEvents() {
	if (ready) {
		if (canMove) {
			if (shouldntStop()) {
				std::pair<int, int>& player_coords = *(this->player_coords);

				if (GetAsyncKeyState(VK_UP) & 0x8000) { // стрелка вверх
					Move(UP);

				}
				else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //стрелка вниз
					Move(DOWN);
				}
				else if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // влево
					Move(LEFT);
				}
				else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // вправо
					Move(RIGHT);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // клавиша ESC
				canMove = false;
				emitter["exit"] = true;
				emitter["special"] = true;
			}
			else if (GetAsyncKeyState(0x49) & 0x8000) {// клавиша I	
				this->ready = false;
				lookinventory = true;
				emitter["inventory"] = true;
				emitter["special"] = true;

			}
		}


		else if (lookinventory) {
			if (GetAsyncKeyState(0x49) & 0x8000) { // клавиша I
				this->ready = false;
				lookinventory = false;
				emitter["inventory"] = true;
				emitter["special"] = true;
			}

		}
		else if (battlemode) {
			if (GetAsyncKeyState(VK_UP) & 0x8000) { // стрелка вверх
				if (bm.menu==MAIN) {
					HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << u8"Использовать главное оружие";
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << u8"Использовать второстепенное оружие";
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << u8"Сбежать";
						break;
					}
					if (bm.choice == 0) bm.choice = 2;
					else bm.choice--;
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << u8"Использовать главное оружие";
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << u8"Использовать второстепенное оружие";
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << u8"Сбежать";
						break;
					}
				}
				else if (bm.menu==SECONDARYWEAPON){
					HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(&fs_weapon);
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(&ss_weapon);
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << u8"Назад";
						break;
					}
					if (bm.choice == 0) bm.choice = 2;
					else bm.choice--;
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(&fs_weapon);
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(&ss_weapon);
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << u8"Назад";
						break;
					}
				}
				else {
					HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(first_weapon.get());
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(second_weapon.get());
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(third_weapon.get());
						break;
					}
					if (bm.choice == 0) bm.choice =2;
					else bm.choice--;
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(first_weapon.get());
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(second_weapon.get());
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(third_weapon.get());
						break;
					}
				}
				HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000) { //стрелка вниз
				if (bm.menu == MAIN) {
					HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << u8"Использовать главное оружие";
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << u8"Использовать второстепенное оружие";
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << u8"Сбежать";
						break;
					}
					if (bm.choice == 2) bm.choice =0;
					else bm.choice++;
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << u8"Использовать главное оружие";
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << u8"Использовать второстепенное оружие";
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << u8"Сбежать";
						break;
					}
				}
				else if (bm.menu==MAINWEAPON){
					HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(first_weapon.get());
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(second_weapon.get());
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(third_weapon.get());
						break;
					}
					if (bm.choice == 2) bm.choice = 0;
				   	else bm.choice++;
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(first_weapon.get());
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(second_weapon.get());
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(third_weapon.get());
						break;
					}
				}
				else {
					HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(&fs_weapon);
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << GetWeaponDescription(&ss_weapon);
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						std::cout << u8"Назад";
						break;
					
					}
					if (bm.choice == 2) bm.choice = 0;
					else bm.choice++;
					switch (bm.choice) {
					case 0:
						SetXY(0, 0);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(&fs_weapon);
						break;
					case 1:
						SetXY(0, 1);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(&ss_weapon);
						break;
					case 2:
						SetXY(0, 2);
						SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
						std::cout << u8"Назад";
						break;
					}
				}
				HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));

				std::this_thread::sleep_for(std::chrono::milliseconds(100));

			}
			
			else if (GetAsyncKeyState(VK_RETURN) & 0x8000) { // ENTER
				if (bm.menu == MAIN) {
					switch (bm.choice) {
					case 0: {
						bm.menu = MAINWEAPON;
						clear();
						SetXY(0, 0);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(8 << 4 | 15));
						std::cout << GetWeaponDescription(first_weapon.get());
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(0 << 4 | 15));

						SetXY(0, 1);
						std::cout << GetWeaponDescription(second_weapon.get());
						SetXY(0, 2);
						std::cout << GetWeaponDescription(third_weapon.get());
					}
						break;
					case 1: {
						bm.menu = SECONDARYWEAPON;
						
						clear();
						bm.choice = 0;
						SetXY(0, 0);
						std::cout << GetWeaponDescription(&fs_weapon);
						SetXY(0, 1);
						std::cout << GetWeaponDescription(&ss_weapon);
						SetXY(0, 2);
						std::cout << u8"Назад";
						break;
					}
					case 2:
						bm.run();
						break;
					}

				}
				else if (bm.menu == MAINWEAPON) {
					switch (bm.choice) {
					case 0:
						if (first_weapon->isDefined) {
							bool win = bm.use_mainweapon(first_weapon.get());
							if (!win) {
								bm.menu = MAIN;
								bm.choice = 0;
								clear();
								bm.InitializeUI();
							}
						}
						break;
					case 1:
						if (second_weapon->isDefined) {
							bool win = bm.use_mainweapon(second_weapon.get());
							if (!win) {
								bm.menu = MAIN;
								bm.choice = 0;
								clear();
								bm.InitializeUI();
							}
						}
						break;
					case 2:
						if (third_weapon->isDefined) {
							bool win = bm.use_mainweapon(third_weapon.get());
							if (!win) {
								bm.menu = MAIN;
								bm.choice = 0;
								clear();
								bm.InitializeUI();
							}
						}
						break;
					}
				}
				else if (bm.menu == SECONDARYWEAPON) {
					switch (bm.choice) {
					case 0:
						if (fs_weapon.AreYouExist()) {
							bool win = bm.use_secondary_weapon(&fs_weapon);
							if (!win) {
								bm.menu = MAIN;
								bm.choice = 0;
								clear();
								bm.InitializeUI();
							}
						}
						break;
					case 1:
						if (ss_weapon.AreYouExist()) {
							bool win = bm.use_secondary_weapon(&ss_weapon);
							if (!win) {
								bm.menu = MAIN;
								bm.choice = 0;
								clear();
								bm.InitializeUI();
							}
						}
						break;
					case 2:
						bm.menu = MAIN;
						bm.choice = 0;
						clear();
						bm.InitializeUI();
					}
				}
				HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

			}

		}
	}
}
bool Player::shouldntStop() {
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = now - last_move_time;
	if (elapsed.count() >= move_interval) {
		last_move_time = now;
		return true;
	}
	return false;
}
void Player::LevelUp() {
	dexterity += rand() % 2 + 1;
	attack += rand() % 4 + 1;
	defense += rand() % 3 + 1;
}

bool Player::EnemyNearThePlayer() {
	//что вблизи игрока
	int x = this->player_coords->first;
	int y = this->player_coords->second;
	std::vector<std::vector<char>> map = this->mapGen->generated_map;
	char l_object=map[y][x-1], d_object = map[y+1][x], u_object =map[y-1][x], r_object = map[y][x+1];
	if (l_object == 'E' || d_object == 'E' || r_object == 'E' || u_object == 'E') return true;
	return false;


	
}
void Player::GetDamage(int damage) {
	if (!(rand() % ((11 - dexterity)==0?1:11-dexterity) == 0)) {
		this->hp -= (damage-this->defense)<0?0:damage - this->defense;
	}
	else {
		SetXY(0, 5);
		std::cout << u8"Вы, совершив нереальный пируэт увернулись, от атаки противника. Противник в шоке";
		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		SetXY(0, 5);
		std::cout << u8"                                                                                ";//очистка строки

	}

}
void Player::Win() {
	ready = false;
	clear();
	SetXY(0, 0);
	std::cout << u8"Вы браво сражались и победили. Поздравляем!";
	SetXY(0, 1);
	int old_level = exp / 20;
	int exp = rand() % 20 + 1;
	int money = rand() % 40 + 2;
	level = (this->exp / 50);
	this->exp += exp;
	this->money += money;
	std::cout << u8"Вы получаете " << exp << u8" единиц опыта и " << money << u8" денег";
	SetXY(0, 2);
	std::cout << u8"Вы отдохнули и готовы идти в бой. Ваши очки здоровья восстановлены!";
	hp = 20 * (level + 1);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	if (old_level!=level) LevelUp();
	emitter["battle_end"] = true;
	emitter["special"] = true;

}
void Player::run_from_battle() {
	ready = false;
	emitter["battle_end"] = true;
	emitter["special"] = true;
}
std::string Player::GetWeaponDescription(MainWeapon* weapon)
{
	std::stringstream fw_description;
	if (weapon->isDefined) {
		switch (weapon->type) {
		case SWORD:
			fw_description << u8"Меч ";
			break;
		case BOW:
			fw_description << u8"Лук ";
			break;
		case SHIELD:
			fw_description << u8"Щит защитой " << reinterpret_cast<Shield*>(weapon)->Defense;
			break;
		}
		if (!(weapon->type==SHIELD)) fw_description << u8"силой " << reinterpret_cast<Weapon*>(weapon)->Use().second;
		return fw_description.str();
	}
	else {
		return  u8"ПУСТАЯ КЛЕТКА";
	}
}
std::string Player::GetWeaponDescription(SecondaryWeapon* weapon) {
	std::stringstream fw_description;
	if (weapon->AreYouExist()) {
		switch (weapon->type) {
		case HEAL:
			fw_description << u8"Лечение ";
			break;
		case DAMAGE:
			fw_description << u8"Урон ";
			break;
		case RAISE_CHARACTERISTICS:
			fw_description << u8"Повышение характеристик ";
			break;
		case RANDOM:
			fw_description << u8"Случайное действие ";
			break;
		}
		fw_description << u8"силой " << weapon->action_value;
		return fw_description.str();
	}
	else {
		return u8"ПУСТАЯ КЛЕТКА";
	}
}