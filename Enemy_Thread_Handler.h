#pragma once
#ifndef EN_THD_H
#define EN_THD_H
#include "Map.h"
#include <mutex>

class EnemyThreadHandler {
    /*
    Класс, который обслуживает перемещение противников в отдельном потоке
    */
private:
    bool condition_to_stop_enemy_thread = false;// условие для окончания потока
    Map* mapgen; // указатель на объект класса Map (СМОТРИ Map.h)
    
    std::mutex& console_mutex; // ссылка на консольный мьютекс из Main.h
    bool stopMoving_cond=false; // Условие для остановки противников
    bool Windows11 = IsWindows11(); // Windows 11 или ниже? Это условие влияет на отрисовку противником
public:
    EnemyThreadHandler(Map* mapgen, std::mutex& console_mutexss); // Конструктор для инициализации мьютекса и указатель на объект класса Map
    void handle_enemies(std::pair<int, int>& ptr_to_player_coords); // Обработчик движения противников, принимает ссылку на координаты игрока
    void stop();// Останавливает поток(после этого поток освобождается)
    void stopMoving(); // Останавливает движение противников(поток остаётся)
    void startMoving(); // Возобновляет движение противников(поток остаётся)
};
#endif