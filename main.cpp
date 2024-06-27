#include <Windows.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <map>
#include "MapGenerator.cpp"

#define DEBUG true
using namespace std;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
string start_screen = "*************************************************************\n*                                                           *\n*                                                           *\n*                      Живые клетки                         *\n*                                                           *\n*                                                           *\n*                                                           *\n*************************************************************";
void clear() {
	system("cls");
}
void SetXY(short X, short Y) {
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hout, coord);
}

class Game
{
private:
	void ShowRecords() {
		ifstream file("records.txt");
		int first_place=0, second_place=0, third_place=0;
		if (file.is_open()) {
			string line;
			if (getline(file, line)) first_place = stoi(line);
			if (getline(file, line)) second_place = stoi(line);
			if (getline(file, line)) third_place = stoi(line);
		}
		SetXY(0, 0);
		cout << "Рекорды";
		SetXY(0, 1);
		cout << "1."<<first_place;
		SetXY(0, 2);
		cout << "2."<<second_place;
		SetXY(0, 3);
		cout << "3."<<third_place;
		SetXY(0, 5);
		SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
		cout << "Выход";
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		while (true) {
			if (_kbhit()) {
				int key = _getch();
				if (key == 13) break;
			}
		}

	}
	void draw_game() {
	 long long seed = (clock() * rand()) + (clock()*(rand()+clock()));

	}
	
	void redraw_start_screen(int choose) {
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		clear();
		switch (choose) {
		case 0:
			SetXY(0, 0);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			cout << "1.СТАРТ";
			SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
			SetXY(0, 1);
			cout << "2.ТАБЛИЦА РЕКОРДОВ";
			SetXY(0, 2);
			cout << "3.ВЫХОД";
			break;
		case 1:
			SetXY(0, 0);
			cout << "1.СТАРТ";
			SetXY(0, 1);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			cout << "2.ТАБЛИЦА РЕКОРДОВ";
			SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
			SetXY(0, 2);
			cout << "3.ВЫХОД";
			break;
		case 2:
			SetXY(0, 0);
			cout << "1.СТАРТ";
			SetXY(0, 1);
			cout << "2.ТАБЛИЦА РЕКОРДОВ";
			SetXY(0, 2);
			SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
			cout << "3.ВЫХОД";
			break;
		}
	}
	
	void draw_start_screen() {
		SetXY(0, 0);
		SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
		cout << "1.СТАРТ";
		SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));
		SetXY(0, 1);
		cout << "2.ТАБЛИЦА РЕКОРДОВ";
		SetXY(0, 2);
		cout << "3.ВЫХОД";
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
public:
	void Initialize()
	{
		setlocale(LC_ALL, "Russian");
		// Титульник(введение,название игры)
		SetConsoleTitle(TEXT("Живые клетки"));
		if (!DEBUG) {
			cout << start_screen;
			Sleep(1000);
			clear();
			// МЕНЮ
			draw_start_screen();
			clear();
			// основная игра
			draw_game();
		}
		else {
			Map map = Map();
			map.generate();
			for (int i = 0; i < map.MAX_MAP_WIDTH; i++) {
				for (int j = 0; j < map.MAX_MAP_HEIGHT; j++) {
					SetXY(i, j);
					cout << map.generated_map[j][i];


				}
			}
		}




	}

};

int main()
{
	Game instance = Game();
	instance.Initialize();
}