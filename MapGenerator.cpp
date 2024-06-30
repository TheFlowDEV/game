#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ctime>

// КОД ЧАСТИЧНО СДЕЛАН С ПОМОЩЬЮ CHATGPT
// НЕ ДОВЕРЯТЬ!!!

using namespace std;
struct BSPNode {
	int x, y, width, height;
	BSPNode* left;
	BSPNode* right;
	bool isLeaf;

	BSPNode(int x, int y, int width, int height)
		: x(x), y(y), width(width), height(height), left(nullptr), right(nullptr), isLeaf(true) {}

};
const int minRoomSize = 13;
const int maxRoomSize = 17;
const int MAX_EXIT_NUMBER = 1;
const int MAX_CHEST_NUMBER = 4;
const short MAX_ENEMY_NUMBER = 10;
class Enemy {
private:
    pair<int, int> coords;
    vector<vector<char>>* map;
    BSPNode* room;
public:
    Enemy(pair<int, int> coords, vector<vector<char>>* map, BSPNode* room) {
        this->coords = coords;
        this->map = map;
        this->room = room;
    }
    void Move(pair<int, int> player_coords) {
        // нужно проверить видимость игрока в пределах комнаты
        if ((player_coords.first > room->x + 1) && (player_coords.first < room->x + room->width - 1) && (player_coords.second > room->y - 1) && (player_coords.second < room->y + room->height + 1))
        {
            //должны выстроить траекторию к нему и идти ПО ОДНОЙ КЛЕТКЕ
            // НЕЛЬЗЯ ИДТИ ЕСЛИ ВПЕРЕДИ ОБЪЕКТ
        }
        // иначе просто в рандомную позицию идти(В ПРЕДЕЛАХ КОМНАТЫ)
        else {

        }


    }
    pair<int, int> get_coords() { return this->coords; }
};

class Room {
private:
    vector<Enemy> enemies;
    pair<int, int> chest;
    pair<int, int> exit;
    BSPNode* node;
public:
    Room(BSPNode* node) {
        this->node = node;
    }
    void generate(bool exit, bool chest, bool enemy,vector<vector<char>> *map)
    {
        if (exit) {
            this->exit.first = rand() % (node->width-1 ) + node->x+1;
            this->exit.second = rand() % (node->height-1) + node->y + 1;
           
        }
        
        if (chest) {
            this->chest.first = rand() % (node->width - 1) + node->x + 1;
            this->chest.second = rand() % (node->height - 1) + node->y + 1;
            
        }
        
        if (enemy) {
            pair<int, int> enemy_coords;
            enemy_coords.first = rand() % (node->width - 1) + node->x + 1;
            enemy_coords.second = rand() % (node->height - 1) + node->y + 1;
            Enemy enemy = Enemy(enemy_coords, map, this->node);
            enemies.push_back(enemy);
            if (rand() % 4 == 3) {
                pair<int, int> enemy2_coords;
                enemy2_coords.first = rand() % (node->width - 1) + node->x + 1;
                enemy2_coords.second = rand() % (node->height - 1) + node->y + 1;
                

                if (enemy_coords != enemy2_coords) {
                    Enemy enemy2 = Enemy(enemy2_coords, map, this->node);
                    enemies.push_back(enemy2);
                }
            }
        }
        

    }
    vector<Enemy> get_enemies() { return this->enemies; }
    pair<int, int> get_chest() { return this->chest; }
    pair<int, int> get_exit() { return this->exit; }
    BSPNode* get_node() { return this->node; }
};

class Map {
    friend class Game;
private:
    bool shop_exists = false;
    const int MAX_MAP_WIDTH = 100;
    const int MAX_MAP_HEIGHT = 28;
    float chest_veroyatnost = 5.25,enemy_veroyatnost=1.25,exit_veroyatnost=1,shop_veroyatnost = 2.5;
    vector<Room> rooms;
    // { 1:{enemies:{ {1,2},{2,3} },width_and_height:{{20,30}},chests:{{20,30},{30,40},exits:{1,2}} 2:{} 3:{}}
    short exits_number = 0;
    short chests_number = 0;
    short enemies_number = 0;
    void connectRooms(BSPNode* node, std::vector<std::vector<char>>& map) {
        if (!node->isLeaf) {
            if (node->left) connectRooms(node->left, map);
            if (node->right) connectRooms(node->right, map);

            if (node->left && node->right) {
                BSPNode* leftRoom = getLeafRoom(node->left);
                BSPNode* rightRoom = getLeafRoom(node->right);

                int startX = leftRoom->x + leftRoom->width / 2;
                int startY = leftRoom->y + leftRoom->height / 2;
                int endX = rightRoom->x + rightRoom->width / 2;
                int endY = rightRoom->y + rightRoom->height / 2;

                while (startX != endX) {
                    map[startY][startX] = '.';
                    startX += (endX - startX) / abs(endX - startX);
                }

                while (startY != endY) {
                    map[startY][startX] = '.';
                    startY += (endY - startY) / abs(endY - startY);
                }
            }
        }
    }
    void drawRooms(BSPNode* node, std::vector<std::vector<char>>& map) {
        if (node->isLeaf) {
            for (int y = node->y; y < node->y + node->height; ++y) {
                for (int x = node->x; x < node->x + node->width; ++x) {
                    if ( (y==node->y)|| (y == node->y-node->height)|| (x == node->x) || (x == node->x+node->width)){
                        map[y][x] = '#';
                        
                    }
                    else {
                    
                        map[y][x] = '.';
                    }
                }
            }
        }
        else {
            if (node->left) drawRooms(node->left, map);
            if (node->right) drawRooms(node->right, map);
        }
    }
    BSPNode* getLeafRoom(BSPNode* node) {
        if (node->isLeaf) return node;
        BSPNode* leftRoom = getLeafRoom(node->left);
        BSPNode* rightRoom = getLeafRoom(node->right);
        return (leftRoom ? leftRoom : rightRoom);
    }
    bool split(BSPNode* node, int minRoomSize) {
        if (node->width <= minRoomSize * 2 && node->height <= minRoomSize * 2) {
            return false;
        }

        bool splitH = rand() % 2 == 0;
        if (node->width > node->height && node->width / node->height >= 1.25) {
            splitH = false;
        }
        else if (node->height > node->width && node->height / node->width >= 1.25) {
            splitH = true;
        }

        int max = (splitH ? node->height : node->width) - minRoomSize;
        if (max <= minRoomSize) {
            return false;
        }

        int splitPos = rand() % (max - minRoomSize) + minRoomSize;

        if (splitH) {
            node->left = new BSPNode(node->x, node->y, node->width, splitPos);
            node->right = new BSPNode(node->x, node->y + splitPos, node->width, node->height - splitPos);
        }
        else {
            node->left = new BSPNode(node->x, node->y, splitPos, node->height);
            node->right = new BSPNode(node->x + splitPos, node->y, node->width - splitPos, node->height);
        }

        node->isLeaf = false;

        split(node->left, minRoomSize);
        split(node->right, minRoomSize);

        return true;
    }
    void createRooms(BSPNode* node, int minRoomSize, int maxRoomSize) {
        if (node->isLeaf) {
            int roomWidth = rand() % (maxRoomSize - minRoomSize + 1) + minRoomSize;
            int roomHeight = rand() % (maxRoomSize - minRoomSize + 1) + minRoomSize;
            int roomX, roomY;
            if ((node->width - roomWidth + 1) != 0 && (node->height - roomHeight + 1)!=0) {
                roomX = node->x + rand() % (node->width - roomWidth + 1);
                roomY = node->y + rand() % (node->height - roomHeight + 1);
            }
            
            else
            {
                roomX = node->x;
                roomY = node->y;
            }

            node->x = roomX;
            node->y = roomY;
            if ((roomWidth + roomX) > MAX_MAP_WIDTH) node->width = MAX_MAP_WIDTH - roomX - 1;
            else if ((roomWidth + roomX) == MAX_MAP_WIDTH-1 || (roomWidth + roomX) == MAX_MAP_WIDTH)  node->width = roomWidth - 1;
            else node->width = roomWidth;
            if ((roomHeight + roomY) > MAX_MAP_HEIGHT) node->height = MAX_MAP_HEIGHT-roomY-1;
            else if ((roomHeight + roomY) == MAX_MAP_HEIGHT-1 || (roomHeight + roomY) == MAX_MAP_HEIGHT)  node->height = roomHeight - 1;
            else node->height = roomHeight;
            Room room = Room(node);
            rooms.push_back(room);
        }
        else {
            if (node->left) createRooms(node->left, minRoomSize, maxRoomSize);
            if (node->right) createRooms(node->right, minRoomSize, maxRoomSize);
        }
    }
    void CreateRoomContents(vector<vector<char>>& map) {
        bool first_room = true;
        for (int i = 1; i < rooms.size();i++) {
                Room room = rooms[i];
                bool chest=false, enemy=false, exit=false;
                
                BSPNode* node = room.get_node();
                if (this->enemies_number < MAX_ENEMY_NUMBER) {
                    if ((rand() % static_cast<int>((enemy_veroyatnost * 2))) == 0) { enemy = true; this->enemies_number++; }
                }
                if (this->chests_number < MAX_CHEST_NUMBER) {
                    if ((rand() % static_cast<int>((chest_veroyatnost * 2))) == 0) {chest = true; this->chests_number++;}
                }
                if (this->exits_number < MAX_EXIT_NUMBER) {
                    if ( ((rand() % static_cast<int>((exit_veroyatnost * 2))) == 0) || this->exits_number==0) { exit = true; this->exits_number++; }
                }
                vector<vector<char>>* map_ptr = &generated_map;
                if (!chest && !enemy && !exit) {
                    //Спецкомната
                    if ((rand() % static_cast<int>(shop_veroyatnost * 2) == 0)&&!shop_exists) { map[node->y + node->height / 2][node->x + node->width / 2] = 'S'; shop_exists = true; }
                }
                else room.generate(exit, chest, enemy,map_ptr);
                pair<int, int> exit_coords = room.get_exit();
                pair<int, int> chest_coords = room.get_chest();
                vector<Enemy> enemies = room.get_enemies();
                if (exit_coords.first!=0 && exit_coords.second!=0) map[exit_coords.second][exit_coords.first] = 'R';
                if (chest_coords.first!=0 && chest_coords.second!=0) map[chest_coords.second][chest_coords.first] = '$';
                for (auto& enemy : enemies) {
                    pair<int, int> enemy_coord = enemy.get_coords();
                    if (enemy_coord.first != 0 && enemy_coord.second != 0) {
                        map[enemy_coord.second][enemy_coord.first] = 'E';
                        
                    }
                }


            

        }
        
    }
public:
    vector<vector<char>> generated_map;
    void generate() {
        srand(static_cast<unsigned>(time(nullptr)));
        vector<vector<char>> map(MAX_MAP_HEIGHT, vector<char>(MAX_MAP_WIDTH, '#'));
        BSPNode* root = new BSPNode(0, 0, MAX_MAP_WIDTH, MAX_MAP_HEIGHT);
        split(root, minRoomSize);
        createRooms(root, minRoomSize, maxRoomSize);
        drawRooms(root, map);
        connectRooms(root, map);
        CreateRoomContents(map);
        generated_map = map;



        }


    };
    
    