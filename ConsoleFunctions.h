#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <Windows.h>
void SetXY(short X, short Y);
/*
Метод для установки курсора консоли в заданную позицию
X:short - координата X
Y:short - координата Y

Стоит учесть,что координата Y считается сверху вниз.

*/
void clear();// Метод для очистки экрана
bool IsWindows11();
/*
Метод для проверки системы на версию

В Windows 11 игра запускается в Windows Terminal, которая поддерживает новые символы Unicode

Служит для совместимости отрисовки с предыдущими системами
Возвращает true, если на ПК пользователя Windows 11
*/
#endif // !CONSOLE_H