#include "Main.h"
#include <sstream>
#include "versionhelpers.h"
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
#define DEBUG false
HWND window;

std::string start_screen = u8"*************************************************************\n*                                                           *\n*                                                           *\n*                      Живые клетки                         *\n*                                                           *\n*                                                           *\n*                                                           *\n*************************************************************";
void draw_frame(short x,short y) {
	short ix = x;
	SetXY(ix, y);
	std::cout << "|";
	ix++;
	while (ix != x + 25) {
		SetXY(ix, y);
		std::cout << "-";
		ix++;
	}
	short iy = y;
	while (iy != y + 9) {
		SetXY(ix, iy);
		std::cout << "|";
		iy++;
	}
	iy--;
	ix--;
	while (ix != x) {
		SetXY(ix, iy);
		std::cout << "-";
		ix--;
	}
	while (iy != y - 1) {
		SetXY(ix, iy);
		std::cout << "|";
		iy--;
	}
}
void draw_frame(short x, short y, MainWeapon* weapon) {
	draw_frame(x, y);
	switch (weapon->type) {
	case BOW: {
		short x_center = x + 7;
		short iy = y + 1;
		while (iy != y + 8) {
			SetXY(x_center, iy);
			std::cout << "|";
			iy++;
		}
		iy--;
		x_center++;
		std::cout << "/";
		for (int i = 0; i < 2; i++) {
			iy--;
			x_center++;
			SetXY(x_center, iy);
			std::cout << "/";
		}
		iy--;
		x_center++;
		SetXY(x_center, iy);
		std::cout << ">";
		for (int i = 0; i < 3; i++) {
			iy--;
			x_center--;
			SetXY(x_center, iy);
			std::cout << "\\";
		}
		x_center = x + 7;
		for (int i = 0; i < 3; i++) {
			x_center++;
			SetXY(x_center, y + 4);
			std::cout << "=";
		}
		SetXY(x + 16, y + 7);
		std::cout << weapon->get_description();
		break;
	}
	case SWORD: {
		short ix = x + 1;
		short y_center = y + 4;
		SetXY(ix, y_center);
		std::cout << "(";
		ix++;
		SetXY(ix, y_center);
		std::cout << "=";
		for (int i = 0; i < 3; i++) {
			ix++;
			SetXY(ix, y_center);
			std::cout << "#";
		}
		ix++;
		SetXY(ix, y_center);
		std::cout << "{";
		SetXY(ix, y_center - 1);
		std::cout << ".";
		SetXY(ix, y_center + 1);
		std::cout << "`";
		ix++;
		SetXY(ix, y_center);
		std::cout << ">";
		SetXY(ix, y_center - 1);
		std::cout << "/";
		SetXY(ix, y_center + 1);
		std::cout << "\\";
		ix++;
		SetXY(ix, y_center);
		std::cout << "=";
		SetXY(ix, y_center - 1);
		std::cout << "~";
		SetXY(ix, y_center + 1);
		std::cout << "_";
		for (int i = 0; i < 14; i++) {
			ix++;
			SetXY(ix, y_center);
			std::cout << "=";
		}
		ix++;
		std::cout << "-";
		SetXY(x + 16, y + 7);
		std::cout << weapon->get_description();
		break;
	}
	case SHIELD:
	{
		short x_center = x + 7;
		short iy = y +1;
		SetXY(x_center, iy);
		std::cout << "_";
		SetXY(x_center - 3, iy);
		std::cout << "|";
		SetXY(x_center + 3, iy);
		std::cout << "|";
		SetXY(x_center - 1, iy);
		std::cout << "_";
		SetXY(x_center + 1, iy);
		std::cout << "_";
		SetXY(x_center - 2, iy);
		std::cout << "_";
		SetXY(x_center + 2, iy);
		std::cout << "_";
		for (int i = 0; i < 3; i++) {
			SetXY(x_center - 3, iy);
			std::cout << "|";
			SetXY(x_center + 3, iy);
			std::cout << "|";
			iy++;
		}
		SetXY(x_center - 3, iy);
		std::cout << "|";
		SetXY(x_center + 3, iy);
		std::cout << "|";
		iy++;

		SetXY(x_center - 2, iy);
		std::cout << "\\";
		SetXY(x_center + 2, iy);
		std::cout << "/";
		iy++;
		SetXY(x_center -1, iy);
		std::cout << "\\";
		SetXY(x_center + 1, iy);
		std::cout << "/";
		SetXY(x + 15, y + 7);
		std::cout << weapon->get_description();
		break;
	}
	}
}
void draw_frame(short x, short y, SecondaryWeapon* weapon) {
	draw_frame(x, y);
	if (weapon->AreYouExist()) {
		short x_start = x + 6;
		short iy = y + 1;
		for (int i = 0; i < 3; i++) {
			SetXY(x_start+i, iy);
			std::cout << "m";
		}
		iy++;
		SetXY(x_start, iy);
		std::cout << ")";
		SetXY(x_start+1, iy);
		std::cout << "-";
		SetXY(x_start+2, iy);
		std::cout << "(";
		iy++;
		x_start--;
		SetXY(x_start, iy);
		std::cout << "(";
		SetXY(x_start+4, iy);
		std::cout << ")";
		iy++;
		for (int i = 0; i < 3; i++) {
			SetXY(x_start, iy);
			std::cout << "|";
			SetXY(x_start+4, iy);
			std::cout << "|";
			iy++;
		}
		iy--;
		x_start += 1;
		SetXY(x_start, iy);
		std::cout << "_";
		SetXY(x_start + 1, iy);
		std::cout << "_";
		SetXY(x_start + 2, iy);
		std::cout << "_";
		SetXY(x + 1, y + 7);
		std::stringstream output;
		output << u8"Тип:";
		switch (weapon->type) {
		case RAISE_CHARACTERISTICS:
			output << u8"+АТК,ЛВК,ЗАЩ ";
			break;
		case DAMAGE:
			output << u8"Урон ";
			break;
		case HEAL:
			output << u8"Лечение ";
			break;
		case RANDOM:
			output << u8"Случайный ";
			break;
		}
		output << u8"Сила:" << weapon->action_value;
		std::cout << output.str();
	}
}
void Game::ShowRecords() {
		std::ifstream file("records.txt");
		int first_place=0, second_place=0, third_place=0;
		if (file.is_open()) {
			std::string line;
			if (getline(file, line)) first_place = stoi(line);
			if (getline(file, line)) second_place = stoi(line);
			if (getline(file, line)) third_place = stoi(line);
		}
		SetXY(0, 0);
		std::cout << u8"Рекорды";
		SetXY(0, 1);
		std::cout << "1." << first_place;
		SetXY(0, 2);
		std::cout << "2."<<second_place;
		SetXY(0, 3);
		std::cout << "3."<<third_place;
		SetXY(0, 5);
		SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
		std::cout << u8"Выход";
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		while (true) {
			if (_kbhit()) {
				int key = _getch();
				if (key == 13) break;
			}
		}

	}
void Game::draw_game(bool first_start=true) {
	game_started = true;
	mciSendString(TEXT("stop intro"), NULL, 0, NULL);
	mciSendString(TEXT("close intro"), NULL, 0, NULL);

	if (first_start) {
		shop.SetSeed(seed);
	}
	mciSendString(TEXT("open \"hodim.mp3\" type mpegvideo alias hodim"), NULL, 0, NULL);
	mciSendString(TEXT("play hodim repeat"), NULL, 0, NULL);
	mciSendStringA("setaudio hodim volume to 700", nullptr, 0, nullptr);

	

	if (first_start) map.generate();
	else map.generate(true);

	 for (int i = 0; i < map.map_width; i++) {
		 for (int j = 0; j < map.map_height; j++) {
			 switch (map.generated_map[j][i]) {
			 case 'R':
				 SetConsoleTextAttribute(hout, (WORD)(2 << 4 | 15));
				 SetXY(i, j);
				 std::cout << map.generated_map[j][i];
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				 break;
			 case '$':
				 SetXY(i, j);
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 14));
				 std::cout << '$';
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				 break;
			 case 'S':
				 SetXY(i, j);
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 3));
				 std::cout << "S";
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				 break;
			 case '#':
				 SetXY(i, j);
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 8));
				 std::cout << u8"▒";
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				 break;
			 case 'E':
				 SetXY(i, j);
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 4));
				 if (IsWindows11()) std::cout << u8"🕱";
				 else std::cout << "E";
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				 break;
			 case 'B':
				 SetXY(i, j);
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 4));
				 std::cout << "B";
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				 break;
			 default:
				 SetXY(i, j);
				 std::cout << map.generated_map[j][i];
				 break;
			 }
		 }
	 }
	 std::pair<int, int> player_coords;
	 
	 player_coords = map.spawn_player();
	 player.UpdateMap(&map, &player_coords); 
	 SetXY(0, map.map_height + 1);
	 std::stringstream HUD;
	 HUD << u8"ИНВЕНТАРЬ[I] ";
	 HUD << u8"АТК/ЛВК/ЗАЩ:" << player.attack << "/" << player.dexterity << "/" << player.defense << " ";
	 HUD << u8"ОЗ:" << player.hp << " " << u8"ДЕНЬГИ:" << player.money << u8" ЭТАЖ:" << this->current_etage;;
	 std::cout << HUD.str();
	 EnemyThreadHandler enemy_thread_handler = EnemyThreadHandler(&map,console_mutex);
	 std::thread enemy_thread(&EnemyThreadHandler::handle_enemies, &enemy_thread_handler, std::ref(*(player.player_coords)));
	 bool needStop = false;
	 bool win_game = false;
	 player.canMove = true;
	 player.ready = true;

	 while (!needStop) {
		 if (_kbhit() && GetForegroundWindow()==window) {
			 player.HandleKeyboardEvents();
		 }
		 if (emitter["special"]) {
			 enemy_thread_handler.stopMoving();
			 player.ready = false;
			 player.canMove = false;
			 if (emitter["regen"]) {
				 current_etage++;
				 shop.Clear();
				 save_game();
				 emitter["special"] = false;
				 emitter["regen"] = false;
				 clear();
				 redraw_map(true);
				 player.canMove = true;
				 player.ready = true;
				 enemy_thread_handler.startMoving();

			 }
			 else if (emitter["chest"]) {
				 clear();
				 if (rand() % 2 == 0) {
					 TYPES type = static_cast<TYPES>(rand() % 3);
					 Item* wp = nullptr;
					 if (type == SHIELD) {
						 wp = (new Shield(false));
					 }
					 else {
						 wp = (new Weapon(type, false));
					 }
					 ChangeInventory(wp);
				 }
			 
			 else {
				 ACTIONS type = static_cast<ACTIONS>(rand() % 4);
				 Item* wp = nullptr;
				 wp = new SecondaryWeapon(type, rand() % 30);
				 ChangeInventory(wp);
			 }
				 map.generated_map[coords_emitter["chest"].second][coords_emitter["chest"].first] = '.';
				 coords_emitter["chest"] = { 0,0 };
				 emitter["special"] = false;
				 emitter["chest"] = false;
				 redraw_map(false);
				 player.canMove = true;
				 player.ready = true;
				 enemy_thread_handler.startMoving();

			 }
			 else if (emitter["shop"]) {
				 clear();
				 bool LeaveShop = false;
				 int choice = 0;
				 shop.Generate();
				 SetXY(0, 0);
				 SetConsoleTextAttribute(hout,8 << 4 | 15);
				 std::cout << shop.GetDescription(shop.first_item);
				 SetConsoleTextAttribute(hout, 0 << 4 | 15);
				 SetXY(0, 1);
				 std::cout << shop.GetDescription(shop.second_item);
				 SetXY(0, 2);
				 std::cout << shop.GetDescription(shop.third_item);
				 SetXY(0, 3);
				 std::cout << u8"Выход";
				 while (!LeaveShop) {
					 if (_kbhit()) {
						 if (GetAsyncKeyState(VK_UP) & 0x8000) {
							 switch (choice) {
							 case 0:
								 SetXY(0, 0);
								 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
								 std::cout << shop.GetDescription(shop.first_item);
								 break;
							 case 1:
								 SetXY(0, 1);
								 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
								 std::cout << shop.GetDescription(shop.second_item);
								 break;
							 case 2:
								 SetXY(0, 2);
								 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
								 std::cout << shop.GetDescription(shop.third_item);
								 break;
							 case 3:
								 SetXY(0, 3);
								 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
								 std::cout << u8"Выход";
								 break;
							 }
							 if (choice == 0) choice = 3;
							 else choice--;
							 switch (choice) {
							 case 0:
								 SetXY(0, 0);
								 SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
								 std::cout << shop.GetDescription(shop.first_item);
								 break;
							 case 1:
								 SetXY(0, 1);
								 SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
								 std::cout << shop.GetDescription(shop.second_item);
								 break;
							 case 2:
								 SetXY(0, 2);
								 SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
								 std::cout << shop.GetDescription(shop.third_item);
								 break;
							 case 3:
								 SetXY(0, 3);
								 SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
								 std::cout << u8"Выход";
								 break;
							 }
							 std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
							 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						 }
						 else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
							 switch (choice) {
							 case 0:
								 SetXY(0, 0);
								 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
								 std::cout << shop.GetDescription(shop.first_item);
								 break;
							 case 1:
								 SetXY(0, 1);
								 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
								 std::cout << shop.GetDescription(shop.second_item);
								 break;
							 case 2:
								 SetXY(0, 2);
								 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
								 std::cout << shop.GetDescription(shop.third_item);
								 break;
							 case 3:
								 SetXY(0, 3);
								 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
								 std::cout << u8"Выход";
								 break;
							 }
							 if (choice == 3) choice = 0;
							 else choice++;
							 switch (choice) {
							 case 0:
								 SetXY(0, 0);
								 SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
								 std::cout << shop.GetDescription(shop.first_item);
								 break;
							 case 1:
								 SetXY(0, 1);
								 SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
								 std::cout << shop.GetDescription(shop.second_item);
								 break;
							 case 2:
								 SetXY(0, 2);
								 SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
								 std::cout << shop.GetDescription(shop.third_item);
								 break;
							 case 3:
								 SetXY(0, 3);
								 SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
								 std::cout << u8"Выход";
								 break;
							 }
							 std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
							 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						 }
						 else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
							 switch (choice) {
							 case 0:{
								 if (shop.first_item->isDefined && shop.first_item->cost <= player.money) {
									 clear();
									 player.money -= shop.first_item->cost;
									 std::this_thread::sleep_for(std::chrono::milliseconds(100));
									 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
									 ChangeInventory((shop.Buy(0)));
									 shop.first_item->isDefined = false;

									 clear();
									 SetXY(0, 0);
									 SetConsoleTextAttribute(hout, 8 << 4 | 15);
									 std::cout << shop.GetDescription(shop.first_item);
									 SetConsoleTextAttribute(hout, 0 << 4 | 15);
									 SetXY(0, 1);
									 std::cout << shop.GetDescription(shop.second_item);
									 SetXY(0, 2);
									 std::cout << shop.GetDescription(shop.third_item);
									 SetXY(0, 3);
									 std::cout << u8"Выход";
									 choice = 0;

								 }
								 break;
							 }
							 case 1:{
								 if (shop.second_item->isDefined && shop.second_item->cost <= player.money) {
									 clear();
									 player.money -= shop.second_item->cost;
									 std::this_thread::sleep_for(std::chrono::milliseconds(100));
									 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
									 ChangeInventory(shop.Buy(1));
									 shop.second_item->isDefined = false;
									 clear();
									 SetXY(0, 0);
									 SetConsoleTextAttribute(hout, 8 << 4 | 15);
									 std::cout << shop.GetDescription(shop.first_item);
									 SetConsoleTextAttribute(hout, 0 << 4 | 15);
									 SetXY(0, 1);
									 std::cout << shop.GetDescription(shop.second_item);
									 SetXY(0, 2);
									 std::cout << shop.GetDescription(shop.third_item);
									 SetXY(0, 3);
									 std::cout << u8"Выход";
									 choice = 0;
								 }
								 break;
							 }
							 case 2:
								 {
								 if (shop.third_item->isDefined && shop.third_item->cost <= player.money) {
									 clear();
									 player.money -= shop.third_item->cost;
									 std::this_thread::sleep_for(std::chrono::milliseconds(100));
									 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
									 ChangeInventory(shop.Buy(2));
									 clear();
									 shop.third_item->isDefined = false;
									 SetXY(0, 0);
									 SetConsoleTextAttribute(hout, 8 << 4 | 15);
									 std::cout << shop.GetDescription(shop.first_item);
									 SetConsoleTextAttribute(hout, 0 << 4 | 15);
									 SetXY(0, 1);
									 std::cout << shop.GetDescription(shop.second_item);
									 SetXY(0, 2);
									 std::cout << shop.GetDescription(shop.third_item);
									 SetXY(0, 3);
									 std::cout << u8"Выход";
									 choice = 0;
								 }
								 break;
								 }
							 case 3:
								 clear();
								 LeaveShop = true;
								 break;
							 }
							 std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
							 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
						 }
					 }
				 }
				 emitter["special"] = false;
				 emitter["shop"] = false;
				 redraw_map(false);
				 player.canMove = true;
				 player.ready = true;
				 enemy_thread_handler.startMoving();
			 }
			 else if (emitter["exit"]) {
				 needStop = true;
			 }
			 else if (emitter["inventory"]) {
				 enemy_thread_handler.stopMoving();
				 player.canMove = false;
				 clear();
				 emitter["special"] = false;
				 emitter["inventory"] = false;
				 if (!player.lookinventory) {
					 redraw_map(false);
					 player.canMove = true;
					 player.ready = true;
					 enemy_thread_handler.startMoving();
				 }
				 else {
					 SetXY(0,0);
					 std::cout << u8"Главные оружия";
					 draw_frame(0, 1,player.first_weapon.get());
					 draw_frame(0, 10, player.second_weapon.get());
					 draw_frame(0, 19, player.third_weapon.get());
					 SetXY(50, 0);
					 std::cout << u8"Второстепенные предметы";
					 draw_frame(50, 2,&player.fs_weapon);
					 draw_frame(50, 11,&player.ss_weapon);
					 std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
					 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
					 player.ready = true;
					 

				 }
			 }
			 else if (emitter["battle_end"]) {
				 mciSendString(TEXT("stop battle"), NULL, 0, NULL);
				 mciSendString(TEXT("close battle"), NULL, 0, NULL);

				 map.generated_map[bm.enemy->get_coords().second][bm.enemy->get_coords().first] = '.';
				 bool havefound = false;
				 for (auto & i : map.rooms) {
					 for (int j = 0; j < i->get_enemies()->size();j++) {

						 if (bm.enemy==(*(i->get_enemies()))[j]) {
							 havefound = true;
							 i->get_enemies()->erase(i->get_enemies()->begin() + j);
							 break;
						 }
					 }
					 if (havefound) break;

				 }
				 if (bm.enemy->type == THEBOSS) {
					 win_game = true;
					 emitter["battle_end"] = false;
					 emitter["special"] = false;
					 bm.clear_bm();
					 needStop = true;
				 }
				 else {
					 bm.clear_bm();
					 redraw_map(false);
					 mciSendString(TEXT("play hodim repeat"), NULL, 0, NULL);
					 player.battlemode = false;
					 emitter["battle_end"] = false;
					 emitter["special"] = false;
					 player.canMove = true;
					 player.ready = true;
					 enemy_thread_handler.startMoving();
				 }
			 }
		 }
		 if (player.EnemyNearThePlayer()&& !player.battlemode) {
			 mciSendString(TEXT("stop hodim"), NULL, 0, NULL);
			 mciSendString(TEXT("open \"battle.mp3\" type mpegvideo alias battle"), NULL, 0, NULL);

			 player.ready = false;
			 player.canMove = false;
			 enemy_thread_handler.stopMoving();
			 player.battlemode = true;
			 clear();
			 std::shared_ptr<Enemy> enemy;
			 bool havefound = false;
			 for (auto& i : map.rooms) {
				 for (int j = 0; j < (i->get_enemies())->size(); j++) {
					 std::pair<int, int> l_object = { player.player_coords->first - 1,player.player_coords->second}, d_object = { player.player_coords->first,player.player_coords->second+1 }, u_object = { player.player_coords->first,player.player_coords->second-1 }, r_object ={ player.player_coords->first + 1,player.player_coords->second };
					 std::shared_ptr<Enemy> enemy_temp = (*(i->get_enemies()))[j];
					 if (enemy_temp->get_coords() == l_object || enemy_temp->get_coords() == r_object || enemy_temp->get_coords() == d_object || enemy_temp->get_coords() == u_object) {
						 enemy = enemy_temp;
						 havefound = true;
						 break;
					 }
				 }
				 if (havefound) break;

			 }
			 std::stringstream description;
			 description << u8"Однажды вы шли спокойно по тихой дороге подземелья. НО ТУТ ПОЯВЛЯЕТСЯ ";
			 switch (enemy->type) {
			 case BAT:
				 if (rand() % 2 == 1) {
					 description << u8"НЕВЫНОСИМАЯ ЛЕТУЧАЯ МЫШЬ";
					 enemy->hp = rand()%10 + 10;
				 }
				 else {
					 description << u8"ЛЕТУЧАЯ МЫШЬ-ПЕРЕКАЧ. Удачи вам сбежать от неё! Если доживёте конечно...";
					 enemy->hp = rand() % 20 + 20;
				 }
				 break;
			 case ICE_GOLEM:
				 description << u8"ЛЕДЕНЮЩИЙ ЛЕДЯНОЙ ГОЛЕМ";
				 enemy->hp = rand() % 9 + 15;
				 break;
			 case ORK:
				 if (rand() % 4 == 1) {
					 description << u8"орк,который ругается матом.Кого-то он вам напоминает...";
				 }
				 else {
					 description << u8"ЗЕЛЁНЫЙ И ГРЯЗНЫЙ ОРК";
				 }
				 enemy->hp = rand() % 15 + 15;
				 break;

			 case ZOMBIE:
				 if (rand() % 4 == 1) {
					 description << u8"зомби с квадратной головой(???). Он идёт прямо на вас,циклично издавая звуки,похожие на вздох";
				 }
				 else {
					 description << u8"ЗАГНИВАЮЩИЙ НА ХОДУ ЗОМБИ. ОН ТАК И НОРОВИТ ВАС ЗАРАЗИТЬ!!!!";
				 }
				 enemy->hp = 20;
				 break;

			 case SKELETON:
				 if (rand() % 4 == 1) {
					 description << u8"скелет с квадратной головой(???). Он идёт прямо на вас,циклично издавая звуки,похожие на хруст костей";
				 }
				 else {
					 description << u8"СКЕЛЕТ. О УЖАС, ОН ИДЁТ ПРЯМО НА ВАС!!!";
				 }
				 break;

			 case THEBOSS:
				 description << u8"ОГРОМНОЕ МОХНАТОЕ НЕЧТО С ЩУПАЛЬЦАМИ. НАДЕЙТЕСЬ, ЧТО ЭТО НЕ КТУЛХУ!!!!";
				 enemy->hp = 100;
				 break;

			 }
			 std::cout << description.str();
			 bm.enemy = enemy;
			 player.ready = false;
			 player.canMove = false;
			 player.battlemode = true;
			 std::this_thread::sleep_for(std::chrono::seconds(1));
			 clear();
			 mciSendString(TEXT("play battle repeat"), NULL, 0, NULL);
			 bm.InitializeUI();
			 player.ready = true;
		 }

	 }
	 
	 if (win_game) {
		 clear();
		 SetXY(0, 0);
		 std::cout << u8"После битвы с недоКтулху вы проснулись";
		 std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		 SetXY(0, 1);
		 std::cout << u8"Вы случайно заснули у компьютера, пока играли в Dead Cells.";

		 std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		 SetXY(0, 3);
		 std::cout << u8"Надо же было такому присниться...";
		 std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		 clear();
		 std::ifstream file("records.txt");
		 int first_place = 0, second_place = 0, third_place = 0;
		 if (file.is_open()) {
			 std::string line;
			 if (getline(file, line)) first_place = stoi(line);
			 if (getline(file, line)) second_place = stoi(line);
			 if (getline(file, line)) third_place = stoi(line);
		 }
		 int player_score = player.exp * 100 + player.money;
		 if (player_score > first_place) {
			 
			 third_place = second_place;
			 second_place = first_place;
			 first_place = player_score;
		 }
		 else if (player_score > second_place) {

			 third_place = second_place;
			 second_place = player_score;
		 }
		 else if (player_score > third_place) {
			 third_place = player_score;
		 }
		 std::ofstream file_w("records.txt");
		 file_w << first_place << std::endl;
		 file_w << second_place << std::endl;
		 file_w << third_place << std::endl;
		 map.CleanALL();
		 enemy_thread_handler.stop();
		 enemy_thread.join();
		 clear();

	}
	 if (emitter["exit"]) {

		 enemy_thread_handler.stop();
		 enemy_thread.join();
		 map.CleanALL();
		 clear();
		 save_game();
		 exit(0);
	 }
	}
	
void Game::redraw_map(bool regenerate) {

	if (regenerate) {
		map.generate(true);
		*(player.player_coords) = map.spawn_player();
	}
	for (int i = 0; i < map.map_width; i++) {
		for (int j = 0; j < map.map_height; j++) {
			switch (map.generated_map[j][i]) {
			case 'R':
				SetConsoleTextAttribute(hout, (WORD)(2 << 4 | 15));
				SetXY(i, j);
				std::cout << map.generated_map[j][i];
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				break;
			case '$':
				SetXY(i, j);
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 14));
				std::cout << '$';
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				break;
			case 'S':
				SetXY(i, j);
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 3));
				std::cout <<"S";
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				break;
			case 'P':
				SetXY(i, j);
				std::cout << u8"\u263A";
				break;
			case 'E':
				SetXY(i, j);
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 4));
				if (IsWindows11()) std::cout << u8"🕱";
				else std::cout << "E";
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				break;
			case '#':
				SetXY(i, j);
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 8));
				std::cout << u8"▒";
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				break;
			default:
				SetXY(i, j);
				std::cout << map.generated_map[j][i];
				break;
			}
		}
		SetXY(0, map.map_height + 1);
		std::stringstream HUD;
		HUD << u8"ИНВЕНТАРЬ[I] ";
		HUD << u8"АТК/ЛВК/ЗАЩ:" << player.attack << "/" << player.dexterity << "/" << player.defense << " ";
		HUD << u8"ОЗ:" << player.hp << " " << u8"ДЕНЬГИ:" << player.money<<u8" ЭТАЖ:"<<this->current_etage;
		std::cout << HUD.str();
	}

	
}
void Game::redraw_start_screen(int choose) {
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		clear();
		switch (choose) {
		case 0:
			SetXY(0, 0);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			std::cout << u8"1.СТАРТ";
			SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
			SetXY(0, 1);
			std::cout << u8"2.ТАБЛИЦА РЕКОРДОВ";
			SetXY(0, 2);
			std::cout << u8"3.ВЫХОД";
			break;
		case 1:
			SetXY(0, 0);
			std::cout << u8"1.СТАРТ";
			SetXY(0, 1);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			std::cout << u8"2.ТАБЛИЦА РЕКОРДОВ";
			SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
			SetXY(0, 2);
			std::cout << u8"3.ВЫХОД";
			break;
		case 2:
			SetXY(0, 0);
			std::cout << u8"1.СТАРТ";
			SetXY(0, 1);
			std::cout << u8"2.ТАБЛИЦА РЕКОРДОВ";
			SetXY(0, 2);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			std::cout << u8"3.ВЫХОД";
			break;
		}
	}
	
	void Game::draw_start_screen() {
		SetXY(0, 0);
		SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
		std::cout << u8"1.СТАРТ";
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		SetXY(0, 1);
		std::cout << u8"2.ТАБЛИЦА РЕКОРДОВ";
		SetXY(0, 2);
		std::cout << u8"3.ВЫХОД";
		int choose = 0;
		int key;
		bool StartShouldShow = true;
		while (StartShouldShow)
		{
			if (_kbhit()) {
				window = GetForegroundWindow();
				key = _getch();
				if (key == 224) {
					int second_key = _getch();
					if (second_key == 72) { // стрелка вверх
						if (choose == 0) choose = 2;
						else choose--;
						redraw_start_screen(choose);
					}
					else if (second_key == 80) { //стрелка вниз
						if (choose == 2) choose = 0;
						else choose++;
						redraw_start_screen(choose);
					}
				}
				else if (key == 13 && GetAsyncKeyState(VK_RETURN)&0x8000) {
					SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));

					switch (choose) {
					case 0:
						StartShouldShow = false;
						clear();
						break;
					case 1:
						clear();
						ShowRecords();
						redraw_start_screen(choose);
						break;
					case 2:
						clear();
						exit(0);
						break;
					}
				}


			}
		}
	}

	void Game::Initialize()
	{
		while (true) {
			if (!game_started) {
				
				SetConsoleCP(CP_UTF8); SetConsoleOutputCP(CP_UTF8);

				// Титульник(введение,название игры)
				SetConsoleTitle(TEXT("Живые клетки"));
			}
			mciSendString(TEXT("open \"intro.mp3\" type mpegvideo alias intro"), NULL, 0, NULL);
			mciSendString(TEXT("play intro repeat"), NULL, 0, NULL);
			mciSendStringA("setaudio intro volume to 80", nullptr, 0, nullptr);

			CONSOLE_CURSOR_INFO     cursorInfo;
			GetConsoleCursorInfo(hout, &cursorInfo);
			cursorInfo.bVisible = DEBUG; // видимость курсора
			SetConsoleCursorInfo(hout, &cursorInfo);

			std::cout << start_screen;
			Sleep(1000);
			clear();
			// МЕНЮ
			draw_start_screen();
			clear();
			std::ifstream file("player.sav", std::ios::binary);
			if (file.is_open()) {
				load_game_choice(file);
				file.close();
			}
			// основная игра
			draw_game();
		}
		
	}
	void Game::load_game(std::ifstream &file) {

			cereal::BinaryInputArchive ia(file);
			ia(player, this->current_etage);
	}
	void Game::load_game_choice(std::ifstream& file) {
		SetXY(0, 0);
		SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
		std::cout << u8"1.Продолжить последнюю игру";
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		SetXY(0, 1);
		std::cout << u8"2.Начать заново";
		int choose = 0;
		int key;
		bool LoadShouldShow = true;
		while (LoadShouldShow)
		{
			if (_kbhit()) {
				key = _getch();
				if (key == 224) {
					int second_key = _getch();
					if (second_key == 72) { // стрелка вверх
						switch (choose) {
						case 0:
							SetXY(0, 0);
							SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
							std::cout << u8"1.Продолжить последнюю игру";
							break;
						case 1:
							SetXY(0, 1);
							SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
							std::cout << u8"2.Начать заново";
							break;
						}
						if (choose == 0) choose = 1;
						else choose--;
						switch (choose) {
						case 0:
							SetXY(0, 0);
							SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
							std::cout << u8"1.Продолжить последнюю игру";
							SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));

							break;
						case 1:
							SetXY(0, 1);
							SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
							std::cout << u8"2.Начать заново";
							SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
							break;
						}
					}
					else if (second_key == 80) { //стрелка вниз
						switch (choose) {
						case 0:
							SetXY(0, 0);
							SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
							std::cout << u8"1.Продолжить последнюю игру";
							break;
						case 1:
							SetXY(0, 1);
							SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
							std::cout << u8"2.Начать заново";
							break;
						}
						if (choose == 2) choose = 0;
						else choose++;
						switch (choose) {
						case 0:
							SetXY(0, 0);
							SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
							std::cout << u8"1.Продолжить последнюю игру";
							SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));

							break;
						case 1:
							SetXY(0, 1);
							SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
							std::cout << u8"2.Начать заново";
							SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
							break;
						}
					}
				}
				else if (key == 13) {
					SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
					switch (choose) {
					case 0:
						LoadShouldShow = false;
						load_game(file);
						break;
					case 1:
						LoadShouldShow = false;
						this->current_etage = 0;
						player.reinitialize();
						save_game();
						break;
					}
				}


			}
		}
	}
	

	void Game::save_game() {
		std::ofstream ofs("player.sav", std::ios::binary);
		cereal::BinaryOutputArchive oa(ofs);
		oa(player, this->current_etage);
	}
int main()
{
	

		Game instance = Game();
		instance.Initialize();
	return 0;
}
void Game::ChangeInventory(Item* item) {
	int choice = 0;
	SetXY(0, 0);
	std::cout << u8"Главные оружия";
	if (item->item_type == MAIN_WEAPON) {
		SetXY(30, 5);
		std::cout << "<-";
	}
	else {
		SetXY(77, 7);
		std::cout << "<-";
	}
	draw_frame(0, 1, player.first_weapon.get());
	draw_frame(0, 10, player.second_weapon.get());
	draw_frame(0, 19, player.third_weapon.get());
	SetXY(50, 0);
	std::cout << u8"Второстепенные предметы";
	draw_frame(50, 2, &player.fs_weapon);
	draw_frame(50, 11, &player.ss_weapon);
	
	SetXY(56, 27);
	std::cout << u8"Вы получили " << shop.GetDescription(item)<<"\n\n";
	SetXY(15, 33);
	std::cout << u8"Нажмите ESC,чтобы отказаться от всех изменений";
	bool HasNotChanged = false;
	while (!HasNotChanged) {
		if (_kbhit()) {
			if (item->item_type == MAIN_WEAPON) {
				if (GetAsyncKeyState(VK_UP) & 0x8000) {
					switch (choice) {
					case 0:
						SetXY(30, 5);
						std::cout << "  ";
						break;
					case 1:
						SetXY(30, 15);
						std::cout << "  ";
						break;
					case 2:
						SetXY(30, 24);
						std::cout << "  ";
						break;
					
					}
					if (choice == 0) choice = 2;
					else choice--;
					switch (choice) {
					case 0:
						SetXY(30, 5);
						std::cout << "<-";
						break;
					case 1:
						SetXY(30, 15);
						std::cout << "<-";
						break;
					case 2:
						SetXY(30, 24);
						std::cout << "<-";
						break;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				}
				else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
					switch (choice) {
					case 0:
						SetXY(30, 5);
						std::cout << "  ";
						break;
					case 1:
						SetXY(30, 15);
						std::cout << "  ";
						break;
					case 2:
						SetXY(30, 24);
						std::cout << "  ";
						break;
					
					}
					if (choice == 2) choice = 0;
					else choice++;
					switch (choice) {
					case 0:
						SetXY(30, 5);
						std::cout << "<-";
						break;
					case 1:
						SetXY(30, 15);
						std::cout << "<-";
						break;
					case 2:
						SetXY(30, 24);
						std::cout << "<-";
						break;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				}
				else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
					switch (choice) {
					case 0: {
						MainWeapon* weapon = (dynamic_cast<MainWeapon*>(item));
						if (weapon->type == SWORD || weapon->type == BOW) {
							player.first_weapon = std::make_unique<Weapon>(*(static_cast<Weapon*>(weapon)));

						}
						else {
							player.first_weapon = std::make_unique<Shield>(*(static_cast<Shield*>(weapon)));

						}

						break;
					}
					case 1: {
						MainWeapon* weapon = (dynamic_cast<MainWeapon*>(item));
						if (weapon->type == SWORD || weapon->type == BOW) {
							player.second_weapon = std::make_unique<Weapon>(*(static_cast<Weapon*>(weapon)));

						}
						else {
							player.second_weapon = std::make_unique<Shield>(*(static_cast<Shield*>(weapon)));

						}
						break;
					}

					case 2:
					{
						MainWeapon* weapon = (dynamic_cast<MainWeapon*>(item));
						if (weapon->type == SWORD || weapon->type == BOW) {
							player.third_weapon = std::make_unique<Weapon>(*(static_cast<Weapon*>(weapon)));

						}
						else {
							player.third_weapon = std::make_unique<Shield>(*(static_cast<Shield*>(weapon)));

						}
						break;
					}
					}
					HasNotChanged = true;
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				}
				else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
					HasNotChanged = true;
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
			}

			else {
				if (GetAsyncKeyState(VK_UP) & 0x8000) {
					switch (choice) {
					case 0:
						SetXY(77, 7);
						std::cout << "  ";
						break;
					case 1:
						SetXY(77, 16);
						std::cout << "  ";
						break;
					case 2:
						SetXY(30, 33);
						std::cout << "  ";
						break;
					}
					if (choice == 0) choice = 2;
					else choice--;
					switch (choice) {
					case 0:
						SetXY(77, 7);
						std::cout << "<-";
						break;
					case 1:
						SetXY(77, 16);
						std::cout << "<-";
						break;
					case 3:
						SetXY(20, 33);
						std::cout << "<-";
						break;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				}
				else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
					switch (choice) {
					case 0:
						SetXY(77, 7);
						std::cout << "  ";
						break;
					case 1:
						SetXY(77, 16);
						std::cout << "  ";
						break;
					case 2:
						SetXY(30, 33);
						std::cout << "  ";
						break;
					}
					if (choice == 2) choice = 0;
					else choice++;
					switch (choice) {
					case 0:
						SetXY(77, 7);
						std::cout << "<-";
						break;
					case 1:
						SetXY(77, 16);
						std::cout << "<-";
						break;
					case 2:
						SetXY(20, 33);
						std::cout << "<-";
						break;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				}

				else if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
					switch (choice) {
					case 0:
						player.fs_weapon = *(static_cast<SecondaryWeapon*>(item));
						break;
					case 1:
						player.ss_weapon = *(static_cast<SecondaryWeapon*>(item));
						break;
					case 2:
						HasNotChanged = true;
						break;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
					HasNotChanged = true;
				}
				else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
					HasNotChanged = true;
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				}
			}


		}
	}
	clear();
}