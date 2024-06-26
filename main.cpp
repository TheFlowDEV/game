#include <Windows.h>
#include <conio.h>
#include <string>
#include <iostream>

using namespace std;
HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

string start_screen = "*************************************************************\n*                                                           *\n*                                                           *\n*                        ТЕТРИС                             *\n*                                                           *\n*                                                           *\n*                                                           *\n*************************************************************";
void clear() {
	system("cls");
}
void SetXY(short X, short Y) {
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hout, coord);
}
// Функция меняет цвет фона выбора на белый


class Game
{
private:
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
public:
	void Initialize()
	{
		setlocale(LC_ALL, "Russian");
		SetConsoleTitle(TEXT("TETRIS: The Game"));
		cout << start_screen;
		Sleep(1000);

		clear();
		// МЕНЮ
		COORD coord;
		SetXY(0, 0);
		SetConsoleTextAttribute(hout, (WORD)(8 << 4 | 15));
		cout << "1.СТАРТ";
		SetConsoleTextAttribute(hout, (WORD)(0<<4|15));
		SetXY(0, 1);
		cout << "2.ТАБЛИЦА РЕКОРДОВ";
		SetXY(0, 2);
		cout << "3.ВЫХОД";
		int choose = 0;
		int key;
		while (true)
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
				

			}



		}
	}

};

int main()
{
	Game instance = Game();
	instance.Initialize();
}