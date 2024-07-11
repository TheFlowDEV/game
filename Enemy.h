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
    std::pair<int, int> coords;
    std::vector<std::vector<char>>* map;
    BSPNode* room;
public:
    friend class Map;
    friend class Game;
    ENEMY_TYPES type;
    Enemy(std::pair<int, int> coords, std::vector<std::vector<char>>* map, BSPNode* room,bool boss);
    int hp;
    std::pair<int, int> Move(std::pair<int, int>& player_coords);
    std::pair<int, int> get_coords();
    bool GetDamage(TYPES type_of_weapon, int damage);
    int UseDamage(int turn);
    bool GetDamageByPotion(int damage);
};
#endif