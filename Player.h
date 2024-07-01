#pragma once
#include <map>
#include <utility>
#include <Windows.h>
#include <vector>
using namespace std;
class Player {
private:
	pair<int, int> coords;
	vector<vector<char>>* map;
public:
	Player(vector<vector<char>>* map_ptr, pair<int, int> coords);
	void Move(int move);
};