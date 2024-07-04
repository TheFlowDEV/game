#pragma once
#ifndef EN_THD_H
#define EN_THD_H
#include "Map.h"
#include <mutex>

class EnemyThreadHandler {
private:
    bool condition_to_stop_enemy_thread = false;
    Map* mapgen;
    
    std::mutex& console_mutex;
    bool stopMoving_cond=false;
public:
    EnemyThreadHandler(Map* mapgen, std::mutex& console_mutexss);
    void handle_enemies(pair<int, int>& ptr_to_player_coords);
    void stop();
    void stopMoving();
    void startMoving();
};
#endif