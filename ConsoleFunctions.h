#pragma once
#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <Windows.h>
void SetXY(short X, short Y);
/*
����� ��� ��������� ������� ������� � �������� �������
X:short - ���������� X
Y:short - ���������� Y

����� ������,��� ���������� Y ��������� ������ ����.

*/
void clear();// ����� ��� ������� ������
bool IsWindows11();
/*
����� ��� �������� ������� �� ������

� Windows 11 ���� ����������� � Windows Terminal, ������� ������������ ����� ������� Unicode

������ ��� ������������� ��������� � ����������� ���������
���������� true, ���� �� �� ������������ Windows 11
*/
#endif // !CONSOLE_H