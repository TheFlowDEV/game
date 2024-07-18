#pragma once
#include "Serialization.h"
#include <Windows.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <map>
#include "Map.h"
#include "Shop.h"
#include "BattleManager.h"
#include "Player.h"
#include "Enemy_Thread_Handler.h"
#include "ConsoleFunctions.h"
#include <mutex>
std::mutex console_mutex; // ���������� ������� ��� ������������� ������� ��� ��������� � �������
#pragma comment(lib, "Winmm.lib")

void draw_frame(short x,short y);
/*
	������� ��� ��������� ����� ��� �������� � ���������
	x:short - ���������� X ������ �������� ���� ����
	y:short - ���������� Y ������ �������� ���� ����
*/
void draw_frame(short x, short y,MainWeapon* weapon);
/*
	������� ��� ��������� ������ � ����� � ���������
	x:short - ���������� X ������ �������� ���� ����
	y:short - ���������� Y ������ �������� ���� ����
	weapon:MainWeapon* - ��������� �� ������ ������ MainWeapon. ��� �������� ������ ������
*/

void draw_frame(short x, short y, SecondaryWeapon* weapon);
/*
	������� ��� ��������� ������ � ����� � ���������
	x:short - ���������� X ������ �������� ���� ����
	y:short - ���������� Y ������ �������� ���� ����
	weapon:SecondaryWeapon* - ��������� �� ������ ������ SecondaryWeapon. ��� ��������������� ������ ������
	*/
class Game
{
private:
	std::map<std::string, bool> emitter{ {"special",false},{"chest",false},{"regen",false},{"exit",false},{"shop",false},{"inventory",false},{"battle_end",false} }; // ������ ������ map, ������� �������� � ��������, � �������� ������������ �����, ��������� �������� �����
	std::map<std::string, std::pair<int, int>>coords_emitter{ {"chest",{0,0}}}; // ������ ������ map, ������� �������� � ����������� ������������(�� ������ ������ ������ ������)
	BattleManager bm = BattleManager(player);// ������ ������ BattleManager, ������� �������� �� ����� ������ � �����������
	bool game_started = false; // ����������, ������� ������ ��� ����,����� ����������, ��� ���� ��� ��������
	Player player = Player(console_mutex,emitter,coords_emitter,bm); // ������ ������ Player(�����)
	int current_etage = 0;// ������� ����
	Map map = Map(current_etage);// ������ ������ Map(�����)
	Shop shop= Shop(current_etage);// ������ ������ Shop(�������)
	long long seed= (clock() * rand()) + (clock() * (rand() + clock()));// ����������, ���������� �� ����������� ��������� ��������� � ��������
	void ShowRecords();
	/*
	������� ��� ��������� ��������
	*/
	void draw_game();
	/*
	������� ��� ��������� �������� ����

	*/
	void redraw_start_screen(int choose);
	/*
	������� ��� ����������� ���������� ����
	choose:int - ����� ����� ���� ����� ������

	*/
	void draw_start_screen();
	/*
	������� ��� ��������� ���������� ����

	*/
	void redraw_map(bool regenerate);
	/*
	������� ��� ��������� ����� ����
	regenerate:bool - ����� �� ����������������

	*/
	void load_game(std::ifstream &file);
	/*
	������� ��� �������� ���� �� ����������
	file:std::ifstream& - ������ �� ���� ����������
	*/
	void load_game_choice(std::ifstream &file);
	/*
	������� ��� ��������� ���� � �������� ����
	file:std::ifstream& - ������ �� ���� ����������
	*/
	void save_game();
	/*
	������� ��� ���������� ����
	*/
	void ChangeInventory(Item* item);
	/*
	������� ��� ��������� ����� ��������� ��� �������� ������� ��� �������
	item:Item* - ��������� �� �������, �� ������� ����� ������� ������� �� ���������
	
	*/

public:
	void Initialize();
	/*
	������� ��� ������������� ����

	*/
};
int main();