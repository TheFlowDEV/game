﻿#include "Enemy_Thread_Handler.h"
#include "Enemy.h"

EnemyThreadHandler::EnemyThreadHandler(Map* mapgen,std::mutex& console_mutexss):console_mutex(console_mutexss) {
    this->mapgen = mapgen;
    }
void EnemyThreadHandler::handle_enemies(std::pair<int, int>& ptr_to_player_coords) {
        while (!this->condition_to_stop_enemy_thread) {
            if (!stopMoving_cond) {
                //Ищем все комнаты и выбираем всех противников
                for (Room* room_ptr : this->mapgen->rooms) {
                    Room& room = *(room_ptr);
                    std::vector<std::shared_ptr<Enemy>>* enemies = room.get_enemies();
                    for (std::shared_ptr<Enemy> enemy : (*enemies)) {
                        //И переставляем противников со старых координат на новые
                        std::pair<int, int> old_coords = enemy->get_coords();
                        std::pair<int, int> new_coords = enemy->Move(ptr_to_player_coords);
                        HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
                        console_mutex.lock();// закрываем мьютекс,чтобы поток игрока не помешал выводить противников
                        SetXY(old_coords.first, old_coords.second);
                        std::vector<std::vector<char>>& map = (this->mapgen->generated_map);
                        map[old_coords.second][old_coords.first] = '.';
                        std::cout << '.';
                        SetXY(new_coords.first, new_coords.second);
                        // учитываем также тип противника
                        if (enemy->type!=THEBOSS)map[new_coords.second][new_coords.first] = 'E';
                        else map[new_coords.second][new_coords.first] = 'E';
                        SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 4));
                       //при отрисовке тоже самое
                        if (enemy->type != THEBOSS) {

                            if (Windows11)std::cout << u8"🕱";
                            else std::cout << "E";
                        }
                        else std::cout << "B";
                        SetConsoleTextAttribute(hout, (WORD)(0 << 4 | 15));

                        console_mutex.unlock();//открываем мьютекс
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(350));
        }
    }
void EnemyThreadHandler::stop() {
        this->condition_to_stop_enemy_thread = true;


    }
void EnemyThreadHandler::stopMoving() {
    this->stopMoving_cond = true;
}
void EnemyThreadHandler::startMoving() {
    this->stopMoving_cond = false;
}