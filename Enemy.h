#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "utility"
#include "vector"
class Map;
struct BSPNode;
enum TYPES;
enum ENEMY_TYPES { ICE_GOLEM, ORK, BAT, ZOMBIE, SKELETON, THEBOSS }; // “ипы противников
class Enemy {
private:
    std::pair<int, int> coords; // координаты противника
    std::vector<std::vector<char>>* map; // указатель на карту
    BSPNode* room; // указатель на комнату, в которой находитс€ противник
public:
    friend class Map;
    friend class Game;
    ENEMY_TYPES type; // “ип противника из ENEMY_TYPES
    Enemy(std::pair<int, int> coords, std::vector<std::vector<char>>* map, BSPNode* room,bool boss);
    /*
     онструктор класса Enemy
    ѕринимает на вход
    coords : std::pair<int,int> - координаты противника
    map : std::vector<std::vector<char>>* - указатель на карту
    room : BSPNode* - указатель на BSPNode*, который €вл€етс€ комнатой дл€ противника
    boss:bool - должен ли этот противник быть боссом
    */
    int hp; // очки здоровь€ врага
    std::pair<int, int> Move(std::pair<int, int>& player_coords);
    /*
    ћетод дл€ передвижени€ противника по игровой карте
    player_coords : std::pair<int,int>& - ссылка на координаты игрока

    ≈сли игрок по€вл€етс€ в поле зрени€ противника(внутри комнаты), противник идЄт к игроку
    */
    std::pair<int, int> get_coords(); // ћетод, который возвращает текущие координаты
    bool GetDamage(TYPES type_of_weapon, int damage);
    /*
    ћетод дл€ получени€ урона противником от оружи€
    type_of_weapon:TYPES - тип оружи€, которым бьют противника
    damage:int - принимаемый урон

    ”рон по врагу зависит также и от типа самого врага

    ¬озвращает true, если противник умер
    */
    int UseDamage(int turn);
    /*
   ћетод дл€ нанесени€ урона противником
   
   turn:int - текущий урон

   возвращает наносимый урон противником

    аждый третий ход противник проводит суператаку
   */
    bool GetDamageByPotion(int damage);
    /*
    ћетод дл€ получени€ урона противником от «≈Ћ№я
    damage:int - получаемый урон

    возвращает true, если противник умер
    */
    
};
#endif