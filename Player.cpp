#include "Player.h"

void Player::Move(Moves move) {
	pair<int, int>& player_coords = *(this->player_coords);
	switch (move) {
	case UP:
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
		else {
			switch (mapGen->generated_map[player_coords.second - 1][player_coords.first])
			{
			case '$':
				coords_emitter["chest"] = { player_coords.first,player_coords.second - 1 };
				emitter["chest"] = true;
				emitter["special"] = true;
				break;
			case 'R':
				emitter["regen"] = true;
				emitter["special"] = true;
				break;
			case 'S':
				emitter["shop"] = true;
				emitter["special"] = true;
				break;
			}
		}
		break;
	case DOWN:
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
		else {
			switch (mapGen->generated_map[player_coords.second + 1][player_coords.first])
			{
			case '$':
				coords_emitter["chest"] = { player_coords.first,player_coords.second + 1 };
				emitter["chest"] = true;
				emitter["special"] = true;
				break;
			case 'R':
				emitter["regen"] = true;
				emitter["special"] = true;
				break;
			case 'S':
				emitter["shop"] = true;
				emitter["special"] = true;
				break;
			}
		}
		break;

	case LEFT:
		if (player_coords.second > 0 && mapGen->generated_map[player_coords.second][player_coords.first - 1] == '.') {
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
		else {
			switch (mapGen->generated_map[player_coords.second][player_coords.first - 1])
			{
			case '$':
				coords_emitter["chest"] = { player_coords.first - 1,player_coords.second };
				emitter["chest"] = true;
				emitter["special"] = true;
				break;
			case 'R':
				emitter["regen"] = true;
				emitter["special"] = true;
				break;
			case 'S':
				emitter["shop"] = true;
				emitter["special"] = true;
				break;
			}
		}
		break;
	case RIGHT:
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
		else {
			switch (mapGen->generated_map[player_coords.second][player_coords.first + 1])
			{
			case '$':
				coords_emitter["chest"] = { player_coords.first + 1,player_coords.second };
				emitter["chest"] = true;
				emitter["special"] = true;
				break;
			case 'R':
				emitter["regen"] = true;
				emitter["special"] = true;
				break;
			case 'S':
				emitter["shop"] = true;
				emitter["special"] = true;
				break;
			}
			break;
		}
	}
}

Player::Player(mutex& mutexss, std::map<string, bool>& emit,std::map<string,pair<int,int>>& coords_emit) :console_mutex(mutexss), emitter(emit),coords_emitter(coords_emit) {
	
}
void Player::UpdateMap(Map* map_ptr, pair<int, int>* coords) {
	this->player_coords = coords;
	this->mapGen = map_ptr;
}
void Player::HandleKeyboardEvents() {
	int key;
	key = _getch();
	if (canMove) {
		if (shouldntStop()) {
			pair<int, int>& player_coords = *(this->player_coords);
			if (key == 224) {
				int second_key = _getch();
				if (second_key == 72) { // стрелка вверх
					Move(UP);
					
				}
				else if (second_key == 80) { //стрелка вниз
					Move(DOWN);
				}
				else if (second_key == 75) { // влево
					Move(LEFT);
				}
				else if (second_key == 77) { // вправо
					Move(RIGHT);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
			else if (key == 27) {
				canMove = false;
				emitter["exit"] = true;
				emitter["special"] = true;
			}
		}


	}

}
void Player::GoToBattle() {
	this->canMove = false;
	// условие битвы для handleKeyboardEvents и отрисовка её
}
bool Player::shouldntStop() {
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> elapsed = now - last_move_time;
	if (elapsed.count() >= move_interval) {
		last_move_time = now;
		return true;
	}
	return false;
}
void Player::LevelUp() {

}

bool Player::EnemyNearThePlayer() {
	//что вблизи игрока
	int x = this->player_coords->first;
	int y = this->player_coords->second;
	vector<vector<char>> map = this->mapGen->generated_map;
	char l_object=map[y][x-1], d_object = map[y+1][x], u_object =map[y-1][x], r_object = map[y][x+1];
	if (l_object == 'E' || d_object == 'E' || r_object == 'E' || u_object == 'E') return true;
	return false;


	
}
