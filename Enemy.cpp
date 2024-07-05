#include "Enemy.h"
#include "Item.h"
#include "Map.h"
Enemy::Enemy(pair<int, int> coords, vector<vector<char>>* map, BSPNode* room) {
    *(this->coords) = coords;
    this->map = map;
    this->room = room;
    this->type = static_cast<ENEMY_TYPES>(rand() % static_cast<int>(THEBOSS - 1));
}
pair<int, int> Enemy::Move(pair<int, int>& player_coords) {
    pair<int, int>& coords = *(this->coords);
    // нужно проверить видимость игрока в пределах комнаты
    if ((player_coords.first >= room->x + 1) && (player_coords.first <= room->x + room->width - 1) && (player_coords.second >= room->y - 1) && (player_coords.second <= room->y + room->height + 1))
    {
        //должны выстроить траекторию к нему и идти ПО ОДНОЙ КЛЕТКЕ
        // НЕЛЬЗЯ ИДТИ ЕСЛИ ВПЕРЕДИ ОБЪЕКТ

        if (player_coords.first > coords.first && coords.first + 1 < MAX_MAP_WIDTH && ((*this->map)[coords.second][coords.first + 1] == '.' && coords.first+1<=room->x+room->width)) {
            coords.first += 1;

        }
        else if (player_coords.first < coords.first && coords.first - 1 > 0 && ((*this->map)[coords.second][coords.first - 1] == '.')) {
            coords.first -= 1;

        }
        if (player_coords.second > coords.second && coords.second + 1 < MAX_MAP_HEIGHT && ((*this->map)[coords.second + 1][coords.first] == '.')) {
            coords.second += 1;
        }
        else if (player_coords.second < coords.second && coords.second - 1 > 0 && ((*this->map)[coords.second - 1][coords.first] == '.')) {
            coords.second -= 1;
        }
        return coords;
    }
    // иначе просто в рандомную позицию идти(В ПРЕДЕЛАХ КОМНАТЫ)
    else {
        int rand_num = rand();
        if (rand_num % 4 == 0 && (*map)[coords.second + 1][coords.first] == '.' && coords.second + 1 <= room->y+room->height) {
            coords.second += 1;
        }
        else if (rand_num % 4 == 1 && (*map)[coords.second][coords.first + 1] == '.'  && coords.first + 1 <= room->x +room->width) {
            coords.first += 1;
        }
        else if (rand_num % 4 == 2 && (*map)[coords.second - 1][coords.first] == '.' && coords.second - 1 >= room->y) {
            coords.second -= 1;
        }
        else if (rand_num % 4 == 3 && (*map)[coords.second][coords.first - 1] == '.' && coords.first - 1 >= room->x) {
            coords.first -= 1;
        }
        return coords;
    }


}
pair<int, int> Enemy::get_coords() { return *(this->coords); }
Enemy::~Enemy() {
    delete coords;
}
