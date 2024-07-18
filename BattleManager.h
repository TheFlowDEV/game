#pragma once
#include "ConsoleFunctions.h"
#include "Player.h"
#include "Enemy.h"
enum CHOICE {MAIN,MAINWEAPON,SECONDARYWEAPON}; // ������������, ������� ������ ��������� ����(������� ������� ��������,����� �������� ������, ����� ��������������� ������)
class BattleManager {
	/*
	��� �����, ������� "�������������" ������� �����
	*/
private:
	Player& player; // ������ �� ������
	int turn = 0; // ������� �����
	int defense_count = 0; // ������� ������ ��� ������( ���������� ����� ����� ��������� ���)
	int old_dexterity = player.dexterity, old_attack = player.attack, old_defense = player.defense; // ��������� ��� ����,����� �������� �������������� ������ � ������ ��������� ����� ���������� �����
	bool used_secondary = false; // ������������ �� �����, ������� �������� ��������������

	void enemy_turn(); // ����� ��� ���� ����������
public:
	int choice; // ��������� �� ��, ����� ����� ���� ������( ������,������ � �.�.)
	CHOICE menu = MAIN; // � ����� ������� ���� ��������� �����
	std::shared_ptr<Enemy> enemy = nullptr; // shared_ptr �� ������ ������ Enemy
	BattleManager(Player& player); // �����������, ������� �������������� ������ �� ������
	bool use_mainweapon(MainWeapon* weapon);
	/*
	����� ��� ������������� �������� ������ �� ����������(� ��������������� ����� ����)

	weapon: MainWeapon*  - ��������� �� ������� ������

	���������� true, ���� ��������� � ���������� ��� ����
	*/
	bool use_secondary_weapon(SecondaryWeapon* weapon);
	/*
	����� ��� �������������  �����(��� ����� ����)

	weapon: SecondaryWeapon*  - ��������� �� �����

	���������� true, ���� ��������� � ���������� ��� ����
	*/
	void clear_bm();// ����� ��� ������� ������� ������ BattleManager(������������ ����� ��������� �����)
	void run(); // ����� ��� ��������� '������' ������ �� �����
	void InitializeUI(); // ���������� ���� ���
	void draw_player_stats(); // ���������� ������������� ������
	void draw_enemy_stats(); // ���������� ������������� ����������
};