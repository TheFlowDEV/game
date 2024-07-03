#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "utility"
#include "vector"
using namespace std;
struct BSPNode;
enum TYPES;
enum ENEMY_TYPES { ICE_GOLEM, ORK, BAT, ZOMBIE, SKELETON, THEBOSS };
class Enemy {
private:
    ENEMY_TYPES type;
    pair<int, int>* coords = new pair<int, int>;
    vector<vector<char>>* map;
    BSPNode* room;

public:
    Enemy(pair<int, int> coords, vector<vector<char>>* map, BSPNode* room);
    pair<int, int> Move(pair<int, int>& player_coords);
    pair<int, int> get_coords();
    void GetDamage(TYPES type_of_weapon, int damage);
    ~Enemy();
};
#endif