#pragma once
#ifndef EN_THD_H
#define EN_THD_H
#include "Map.h"
#include <mutex>

class EnemyThreadHandler {
    /*
    �����, ������� ����������� ����������� ����������� � ��������� ������
    */
private:
    bool condition_to_stop_enemy_thread = false;// ������� ��� ��������� ������
    Map* mapgen; // ��������� �� ������ ������ Map (������ Map.h)
    
    std::mutex& console_mutex; // ������ �� ���������� ������� �� Main.h
    bool stopMoving_cond=false; // ������� ��� ��������� �����������
    bool Windows11 = IsWindows11(); // Windows 11 ��� ����? ��� ������� ������ �� ��������� �����������
public:
    EnemyThreadHandler(Map* mapgen, std::mutex& console_mutexss); // ����������� ��� ������������� �������� � ��������� �� ������ ������ Map
    void handle_enemies(std::pair<int, int>& ptr_to_player_coords); // ���������� �������� �����������, ��������� ������ �� ���������� ������
    void stop();// ������������� �����(����� ����� ����� �������������)
    void stopMoving(); // ������������� �������� �����������(����� �������)
    void startMoving(); // ������������ �������� �����������(����� �������)
};
#endif