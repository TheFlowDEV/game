#pragma once
#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ctime>
#include <thread>
#include <Windows.h>

using namespace std;

void SetXYMG(short X, short Y);

struct BSPNode {
    int x, y, width, height;
    BSPNode* left;
    BSPNode* right;
    bool isLeaf;

    BSPNode(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height), left(nullptr), right(nullptr), isLeaf(true) {}
};

class Enemy {
private:
    pair<int, int>* coords= new pair<int,int>;
    vector<vector<char>>* map;
    BSPNode* room;

public:
    Enemy(pair<int, int> coords, vector<vector<char>>* map, BSPNode* room);
    pair<int, int> Move(pair<int, int>& player_coords);
    pair<int, int> get_coords();
    ~Enemy();
};

class Room {
private:
    vector<Enemy*> enemies;
    pair<int, int> chest;
    pair<int, int> exit;
    BSPNode* node;

public:
    Room(BSPNode* node);
    void generate(bool exit, bool chest, bool enemy, vector<vector<char>>* map);
    vector<Enemy*>* get_enemies();
    pair<int, int> get_chest();
    pair<int, int> get_exit();
    BSPNode* get_node();
};

class Map {
    friend class Game;
private:
    
    bool shop_exists = false;
    float chest_veroyatnost = 5.25, enemy_veroyatnost = 1.25, exit_veroyatnost = 1, shop_veroyatnost = 2.5;    vector<Room*> rooms;
    vector<BSPNode*> nodes_of_rooms;
    short exits_number = 0;
    short chests_number = 0;
    short enemies_number = 0;
    vector<vector<char>> generated_map;
    int map_width, map_height;
    void connectRooms(BSPNode* node, std::vector<std::vector<char>>& map);
    void drawRooms(BSPNode* node, std::vector<std::vector<char>>& map);
    BSPNode* getLeafRoom(BSPNode* node);
    bool split(BSPNode* node, int minRoomSize);
    void createRooms(BSPNode* node, int minRoomSize, int maxRoomSize);
    void CreateRoomContents(vector<vector<char>>& map);
public:
    Map();
    void generate();
    pair<int, int> spawn_player();
    
};

#endif // MAP_H