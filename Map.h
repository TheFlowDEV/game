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
Примечание

Координаты чаще всего хранятся в std::pair<int,int>, где first- это координата x, а second - координата y

*/
class Enemy;

const int MAX_MAP_WIDTH = 100; // ширина карты
const int MAX_MAP_HEIGHT = 28; // высота карты
const int minRoomSize = 13; // минимальная длина/высота комнаты
const int maxRoomSize = 17;// максимальная длина/высота комнаты
const int MAX_EXIT_NUMBER = 1;// максимальное число выходов на карте
const int MAX_CHEST_NUMBER = 4;// максимальное число сундуков на карте
const short MAX_ENEMY_NUMBER = 15;// максимальное число врагов на карте



// Структура, описывающая узел дерева BSP
/*
BSP дерево служит для разделения пространства на комнаты
*/
struct BSPNode {
    int x, y, width, height; // x,y - координаты левого верхнего угла комнаты, width,height - ширина и высота комнаты
    BSPNode* left; // Указатель на узел слева(если ещё можно разделить комнату)
    BSPNode* right; // Указатель на узел справа(если ещё можно разделить комнату)
    bool isLeaf; // Параметр, указывающий разделена ли комната до конца(нельзя делить дальше).

    BSPNode(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height), left(nullptr), right(nullptr), isLeaf(true) {}
};




class Room {
    // Класс, описывающий комнату
private:
    std::vector<std::shared_ptr<Enemy>> enemies;// массив указателей на врагов
    std::pair<int, int> chest; // координаты сундука
    std::pair<int, int> exit; // координаты выхода
    BSPNode* node; // какой узел отвечает за эту комнату

public:
    Room(BSPNode* node); // конструктор
    void generate(bool exit, bool chest, bool enemy, std::vector<std::vector<char>>* map,bool boss); // метод для генерации содержимого комнаты
    std::vector<std::shared_ptr<Enemy>>* get_enemies(); // метод для того, чтобы вернуть указатели на врагов
    std::pair<int, int> get_chest(); // метод для того,чтобы вернуть координаты сундука
    std::pair<int, int> get_exit();  // метод для того,чтобы вернуть координаты выхода
    BSPNode* get_node(); // метод для возвращения узла комнаты
};

class Map {
    friend class Game;
    friend class Player;
    friend class EnemyThreadHandler;
private:
    BSPNode* root_node; // какой узел отвечает за всю карту
    bool shop_exists = false; // существует ли магазин на текущем этаже
    int& current_etage; // ссылка на текущий этаж
    bool boss_exists = false;// существует ли босс на текущем этаже
    float chest_veroyatnost = 5.25, enemy_veroyatnost = 1.25, exit_veroyatnost = 1, shop_veroyatnost = 2.5;   // вероятности появления сундука,врага,выхода,магазина
    std::vector<Room*> rooms;// Вектор из указателей на комнаты
    std::vector<BSPNode*> nodes_of_rooms; // Вектор из указателей на узлы
    short exits_number = 0; // количество выходов на данной карте
    short chests_number = 0; // количество сундуков на данной карте
    short enemies_number = 0; // количество врагов на данной карте
    std::vector<std::vector<char>> generated_map; // сгенерированная карты
    int map_width, map_height; // ширина и высота карты(СОВПАДАЕТ С MAX_MAP_WIDTH,MAX_MAP_HEIGHT). Служит для обращения к нему объекта класса Game
    void connectRooms(BSPNode* node, std::vector<std::vector<char>>& map);
    /*
    Метод для соединения комнат коридорами
    node : BSPnode* - указатель на узел дерева
    map : std::vector<std::vector<char>>& - ссылка на карту игры
    */
    void drawRooms(BSPNode* node, std::vector<std::vector<char>>& map); // отрисовка комнат
    BSPNode* getLeafRoom(BSPNode* node); // получение конечной комнаты( у которой параметр IsLeaf истинный)
    bool split(BSPNode* node, int minRoomSize); // разделение комнат до минимального размера
    void createRooms(BSPNode* node, int minRoomSize, int maxRoomSize); // создание комнат
    void CreateRoomContents(std::vector<std::vector<char>>& map); // создание содержимого комнат
    void DeleteBSPNode (BSPNode* node); // Удаление узла дерева BSP(они динамические)
public:
    Map(int& current_etage_ad);//конструктор класса Map
    void CleanALL();// очистка параметров объекта класса Map
    void generate(bool regenerate=false);// (ре)генерация комнаты
    std::pair<int, int> spawn_player();// спавн игрока на карту. Возвращает координаты игрока(Обязаны быть в самой первой комнате)
    
};

#endif // MAP_H