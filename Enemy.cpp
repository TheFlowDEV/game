#include "Enemy.h"
#include "Item.h"
#include "Map.h"
Enemy::Enemy(std::pair<int, int> coords, std::vector<std::vector<char>>* map, BSPNode* room,bool boss_spawn) {
    (this->coords) = coords;
    this->map = map;
    this->room = room;

    this->type = boss_spawn?THEBOSS:static_cast<ENEMY_TYPES>(rand() % static_cast<int>(THEBOSS - 1));
}

std::pair<int, int> Enemy::Move(std::pair<int, int>& player_coords) {
    std::pair<int, int>& coords = (this->coords);
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
std::pair<int, int> Enemy::get_coords() { return (this->coords); }
bool Enemy::GetDamageByPotion(int damage) {
    this->hp -= damage * 2;
    if (hp <= 0) return true;
    else return false;
}
int Enemy::UseDamage(int turn) {
    if (turn % 3 == 0) {
        switch (type) {
        case ICE_GOLEM:
            return rand() % 6 + 1;
            break;
        case ORK:
            return rand() % 10 + 1;
            break;
        case BAT:
            return rand() % 4 + 1;
            break;
        case ZOMBIE:
            return rand() % 7 + 1;
            break;
        case SKELETON:
            return rand() % 5 + 1;
            break;
        case THEBOSS:
            return rand() % 13 + 1;
            break;
        }
    }
    else {
        switch (type) {
        case ICE_GOLEM:
            return rand() % 3 + 1;
            break;
        case ORK:
            return rand() % 7 + 1;
            break;
        case BAT:
            return rand() % 2 + 1;
            break;
        case ZOMBIE:
            return rand() % 4 + 1;
            break;
        case SKELETON:
            return rand() % 5 + 1;
            break;
        case THEBOSS:
            return rand() % 8 + 1;
            break;
    }
    }
}
bool Enemy::GetDamage(TYPES type_of_weapon,int damage) {
    switch (type) {
    case ICE_GOLEM:
        if (type_of_weapon == SWORD) {
            this->hp -= 2 * damage;
        }
        else {
            this->hp -= damage;
        }
        break;
    case ORK:
        if (type_of_weapon == SWORD) {
            this->hp -= 3 * damage;
        }
        else {
            this->hp -= damage;
        }
        break;
    case BAT:
        if (type_of_weapon == SWORD) {
            this->hp -= damage;
        }
        else {
            this->hp -= 2*damage;
        }
        break;
    case ZOMBIE:
        if (type_of_weapon == SWORD) {
            this->hp -= 3 * damage;
        }
        else {
            this->hp -= damage;
        }
        break;
    case SKELETON:
        if (type_of_weapon == SWORD) {
            this->hp -= damage;
        }
        else {
            this->hp -=2* damage;
        }
        break;
    case THEBOSS:
        if (type_of_weapon == SWORD) {
            this->hp -= 4 * damage;
        }
        else {
            this->hp -= damage;
        }
        break;
    }
    if (this->hp <= 0) return true;
    else return false;
}