#pragma once
#ifndef EN_THD_H
#define EN_THD_H
#include "Map.h"
#include <mutex>

class EnemyThreadHandler {
private:
    bool condition_to_stop_enemy_thread = false;
    vector<Room*>* rooms;
    vector<vector<char>>* map;
    std::mutex& console_mutex;
public:
    EnemyThreadHandler(vector<Room*>* room_ptr, vector<vector<char>>* map_ptr, std::mutex& console_mutexss);
    void handle_enemies(pair<int, int>& ptr_to_player_coords);
    void stop();

};
#endif