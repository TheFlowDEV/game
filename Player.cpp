#include "Player.h"
void Player::Move(int move) {
	
}

Player::Player(Map* map_ptr, pair<int, int>* coords,mutex &mutexss):console_mutex(mutexss) {
	this->player_coords = coords;
	this->mapGen = map_ptr;
}
void Player::HandleKeyboardEvents() {
	int key;
	key = _getch();
	if (canMove) {
		pair<int, int>& player_coords = *(this->player_coords);
		if (key == 224) {
			int second_key = _getch();
			if (second_key == 72) { // стрелка вверх
				if (player_coords.second - 1 > 0 && mapGen->generated_map[player_coords.second - 1][player_coords.first] == '.') {

					console_mutex.lock();
					SetXY(player_coords.first, player_coords.second);
					mapGen->generated_map[player_coords.second][player_coords.first] = '.';
					cout << '.';

					SetXY(player_coords.first, player_coords.second - 1);
					player_coords.second -= 1;
					mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
					cout << 'P';
					console_mutex.unlock();
				}
			}
			else if (second_key == 80) { //стрелка вниз
				if (player_coords.second + 1 < mapGen->map_height && mapGen->generated_map[player_coords.second + 1][player_coords.first] == '.') {
					console_mutex.lock();
					SetXY(player_coords.first, player_coords.second);
					mapGen->generated_map[player_coords.second][player_coords.first] = '.';
					cout << '.';
					SetXY(player_coords.first, player_coords.second + 1);
					player_coords.second += 1;
					mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
					cout << 'P';
					console_mutex.unlock();

				}
			}
			else if (second_key == 75) { // влево
				if (player_coords.second - 1 > 0 && mapGen->generated_map[player_coords.second][player_coords.first - 1] == '.') {
					console_mutex.lock();
					SetXY(player_coords.first, player_coords.second);
					mapGen->generated_map[player_coords.second][player_coords.first] = '.';
					cout << '.';
					SetXY(player_coords.first - 1, player_coords.second);
					player_coords.first -= 1;
					mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
					cout << 'P';
					console_mutex.unlock();

				}
			}
			else if (second_key == 77) { // вправо
				if (player_coords.first + 1 < mapGen->map_width && mapGen->generated_map[player_coords.second][player_coords.first + 1] == '.') {
					console_mutex.lock();
					SetXY(player_coords.first, player_coords.second);
					mapGen->generated_map[player_coords.second][player_coords.first] = '.';
					cout << '.';
					player_coords.first += 1;
					mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
					mapGen->generated_map[player_coords.second][player_coords.first] = 'P';
					SetXY(player_coords.first, player_coords.second);
					cout << 'P';
					console_mutex.unlock();

				}
			}
		}


	}
}