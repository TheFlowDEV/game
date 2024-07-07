#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "utility"
#include "vector"
class Map;
struct BSPNode;
enum TYPES;
enum ENEMY_TYPES { ICE_GOLEM, ORK, BAT, ZOMBIE, SKELETON, THEBOSS };
class Enemy {
private:
    ENEMY_TYPES type;
    std::pair<int, int>* coords = new std::pair<int, int>;
    std::vector<std::vector<char>>* map;
    BSPNode* room;
    int hp;
public:
    friend class Map;
    Enemy(std::pair<int, int> coords, std::vector<std::vector<char>>* map, BSPNode* room);
    std::pair<int, int> Move(std::pair<int, int>& player_coords);
    std::pair<int, int> get_coords();
    void GetDamage(TYPES type_of_weapon, int damage);
    ~Enemy();
};
#endif