#pragma once
#ifndef MAP_H
#define MAP_H
#include "ConsoleFunctions.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <thread>
#include <Windows.h>
#include "Item.h"
/*
����������

���������� ���� ����� �������� � std::pair<int,int>, ��� first- ��� ���������� x, � second - ���������� y

*/
class Enemy;

const int MAX_MAP_WIDTH = 100; // ������ �����
const int MAX_MAP_HEIGHT = 28; // ������ �����
const int minRoomSize = 13; // ����������� �����/������ �������
const int maxRoomSize = 17;// ������������ �����/������ �������
const int MAX_EXIT_NUMBER = 1;// ������������ ����� ������� �� �����
const int MAX_CHEST_NUMBER = 4;// ������������ ����� �������� �� �����
const short MAX_ENEMY_NUMBER = 15;// ������������ ����� ������ �� �����



// ���������, ����������� ���� ������ BSP
/*
BSP ������ ������ ��� ���������� ������������ �� �������
*/
struct BSPNode {
    int x, y, width, height; // x,y - ���������� ������ �������� ���� �������, width,height - ������ � ������ �������
    BSPNode* left; // ��������� �� ���� �����(���� ��� ����� ��������� �������)
    BSPNode* right; // ��������� �� ���� ������(���� ��� ����� ��������� �������)
    bool isLeaf; // ��������, ����������� ��������� �� ������� �� �����(������ ������ ������).

    BSPNode(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height), left(nullptr), right(nullptr), isLeaf(true) {}
};




class Room {
    // �����, ����������� �������
private:
    std::vector<std::shared_ptr<Enemy>> enemies;// ������ ���������� �� ������
    std::pair<int, int> chest; // ���������� �������
    std::pair<int, int> exit; // ���������� ������
    BSPNode* node; // ����� ���� �������� �� ��� �������

public:
    Room(BSPNode* node); // �����������
    void generate(bool exit, bool chest, bool enemy, std::vector<std::vector<char>>* map,bool boss); // ����� ��� ��������� ����������� �������
    std::vector<std::shared_ptr<Enemy>>* get_enemies(); // ����� ��� ����, ����� ������� ��������� �� ������
    std::pair<int, int> get_chest(); // ����� ��� ����,����� ������� ���������� �������
    std::pair<int, int> get_exit();  // ����� ��� ����,����� ������� ���������� ������
    BSPNode* get_node(); // ����� ��� ����������� ���� �������
};

class Map {
    friend class Game;
    friend class Player;
    friend class EnemyThreadHandler;
private:
    BSPNode* root_node; // ����� ���� �������� �� ��� �����
    bool shop_exists = false; // ���������� �� ������� �� ������� �����
    int& current_etage; // ������ �� ������� ����
    bool boss_exists = false;// ���������� �� ���� �� ������� �����
    float chest_veroyatnost = 5.25, enemy_veroyatnost = 1.25, exit_veroyatnost = 1, shop_veroyatnost = 2.5;   // ����������� ��������� �������,�����,������,��������
    std::vector<Room*> rooms;// ������ �� ���������� �� �������
    std::vector<BSPNode*> nodes_of_rooms; // ������ �� ���������� �� ����
    short exits_number = 0; // ���������� ������� �� ������ �����
    short chests_number = 0; // ���������� �������� �� ������ �����
    short enemies_number = 0; // ���������� ������ �� ������ �����
    std::vector<std::vector<char>> generated_map; // ��������������� �����
    int map_width, map_height; // ������ � ������ �����(��������� � MAX_MAP_WIDTH,MAX_MAP_HEIGHT). ������ ��� ��������� � ���� ������� ������ Game
    void connectRooms(BSPNode* node, std::vector<std::vector<char>>& map);
    /*
    ����� ��� ���������� ������ ����������
    node : BSPnode* - ��������� �� ���� ������
    map : std::vector<std::vector<char>>& - ������ �� ����� ����
    */
    void drawRooms(BSPNode* node, std::vector<std::vector<char>>& map); // ��������� ������
    BSPNode* getLeafRoom(BSPNode* node); // ��������� �������� �������( � ������� �������� IsLeaf ��������)
    bool split(BSPNode* node, int minRoomSize); // ���������� ������ �� ������������ �������
    void createRooms(BSPNode* node, int minRoomSize, int maxRoomSize); // �������� ������
    void CreateRoomContents(std::vector<std::vector<char>>& map); // �������� ����������� ������
    void DeleteBSPNode (BSPNode* node); // �������� ���� ������ BSP(��� ������������)
public:
    Map(int& current_etage_ad);//����������� ������ Map
    void CleanALL();// ������� ���������� ������� ������ Map
    void generate(bool regenerate=false);// (��)��������� �������
    std::pair<int, int> spawn_player();// ����� ������ �� �����. ���������� ���������� ������(������� ���� � ����� ������ �������)
    
};

#endif // MAP_H