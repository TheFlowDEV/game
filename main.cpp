#include "Main.h"

HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

#define DEBUG false

string start_screen = "*************************************************************\n*                                                           *\n*                                                           *\n*                      Живые клетки                         *\n*                                                           *\n*                                                           *\n*                                                           *\n*************************************************************";


void Game::ShowRecords() {
		ifstream file("records.txt");
		int first_place=0, second_place=0, third_place=0;
		if (file.is_open()) {
			string line;
			if (getline(file, line)) first_place = stoi(line);
			if (getline(file, line)) second_place = stoi(line);
			if (getline(file, line)) third_place = stoi(line);
		}
		SetXY(0, 0);
		std::cout << "Рекорды";
		SetXY(0, 1);
		std::cout << "1." << first_place;
		SetXY(0, 2);
		std::cout << "2."<<second_place;
		SetXY(0, 3);
		std::cout << "3."<<third_place;
		SetXY(0, 5);
		SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
		std::cout << "Выход";
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		while (true) {
			if (_kbhit()) {
				int key = _getch();
				if (key == 13) break;
			}
		}

	}
void Game::draw_game(bool first_start=true) {
	if (first_start) {
		seed = (clock() * rand()) + (clock() * (rand() + clock()));
	}
	 
	

	if (first_start) map.generate();
	else map.generate(true);

	 for (int i = 0; i < map.map_width; i++) {
		 for (int j = 0; j < map.map_height; j++) {
			 switch (map.generated_map[j][i]) {
			 case 'R':
				 SetConsoleTextAttribute(hout, (WORD)(2 << 4 | 15));
				 SetXY(i, j);
				 cout << map.generated_map[j][i];
				 SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
				 break;

			 default:
				 SetXY(i, j);
				 cout << map.generated_map[j][i];
				 break;
			 }
		 }
	 }
	 pair<int, int> player_coords;
	 
	 player_coords = map.spawn_player();
	 player.UpdateMap(&map, &player_coords); 
	 
	 EnemyThreadHandler enemy_thread_handler = EnemyThreadHandler(&map,console_mutex);
	 thread enemy_thread(&EnemyThreadHandler::handle_enemies, &enemy_thread_handler, std::ref(*(player.player_coords)));
	 bool needStop = false;
	 player.canMove = true;
	 while (!needStop) {
		 if (_kbhit()) {
			 player.HandleKeyboardEvents();
		 }
		 if (emitter["special"]) {
			 enemy_thread_handler.stopMoving();
			 player.canMove = false;
			 if (emitter["regen"]) {
				 current_etage++;
				 emitter["special"] = false;
				 emitter["regen"] = false;
				 clear();
				 redraw_map(true);
				 player.canMove = true;
				 enemy_thread_handler.startMoving();

			 }
			 else if (emitter["chest"]) {
				 clear();
				 map.generated_map[coords_emitter["chest"].second][coords_emitter["chest"].first] = '.';
				 coords_emitter["chest"] = { 0,0 };
				 emitter["special"] = false;
				 emitter["chest"] = false;
				 redraw_map(false);
				 player.canMove = true;
				 enemy_thread_handler.startMoving();

			 }
			 else if (emitter["shop"]) {
				 clear();
				 emitter["special"] = false;
				 emitter["shop"] = false;
				 redraw_map(false);
				 player.canMove = true;
				 enemy_thread_handler.startMoving();
			 }
		 }
		 //if (player.EnemyNearThePlayer()) player.canMove = false; и вход в битву

	 }
	 
	
	 if (emitter["exit"]) {
		 enemy_thread_handler.stop();
		 enemy_thread.join();
		 map.CleanALL();
		 clear();
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
				cout << map.generated_map[j][i];
				SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15)); 
				break;

			default:
				SetXY(i, j);
				cout << map.generated_map[j][i];
				break;
			}
		}
	}
	
}
void Game::redraw_start_screen(int choose) {
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		clear();
		switch (choose) {
		case 0:
			SetXY(0, 0);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			std::cout << "1.СТАРТ";
			SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
			SetXY(0, 1);
			std::cout << "2.ТАБЛИЦА РЕКОРДОВ";
			SetXY(0, 2);
			std::cout << "3.ВЫХОД";
			break;
		case 1:
			SetXY(0, 0);
			std::cout << "1.СТАРТ";
			SetXY(0, 1);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			std::cout << "2.ТАБЛИЦА РЕКОРДОВ";
			SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
			SetXY(0, 2);
			std::cout << "3.ВЫХОД";
			break;
		case 2:
			SetXY(0, 0);
			std::cout << "1.СТАРТ";
			SetXY(0, 1);
			std::cout << "2.ТАБЛИЦА РЕКОРДОВ";
			SetXY(0, 2);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			std::cout << "3.ВЫХОД";
			break;
		}
	}
	
	void Game::draw_start_screen() {
		SetXY(0, 0);
		SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
		std::cout << "1.СТАРТ";
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		SetXY(0, 1);
		std::cout << "2.ТАБЛИЦА РЕКОРДОВ";
		SetXY(0, 2);
		std::cout << "3.ВЫХОД";
		int choose = 0;
		int key;
		bool StartShouldShow = true;
		while (StartShouldShow)
		{
			if (_kbhit()) {
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
				else if (key == 13) {
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
		setlocale(LC_ALL, "Russian");
		// Титульник(введение,название игры)
		SetConsoleTitle(TEXT("Живые клетки"));
		CONSOLE_CURSOR_INFO     cursorInfo;
		GetConsoleCursorInfo(hout, &cursorInfo);
		cursorInfo.bVisible = DEBUG; // set the cursor visibility
		SetConsoleCursorInfo(hout, &cursorInfo);
		
			cout << start_screen;
			Sleep(1000);
			clear();
			// МЕНЮ
			draw_start_screen();
			clear();
			// основная игра
			draw_game();
		
	}
	


int main()
{
	Game instance = Game();
	instance.Initialize();
	return 0;
}