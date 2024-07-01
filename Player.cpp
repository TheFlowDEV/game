#include "Player.h"
enum Moves{UP,DOWN,LEFT,RIGHT};
void Player::Move(int move) {
	
}
Player::Player(vector<vector<char>>* map_ptr, pair<int, int> coords) {
	this->coords = coords;
	this->map = map_ptr;
}