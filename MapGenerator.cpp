#include "Map.h"
#include "Enemy.h"







 


Room::Room(BSPNode* node) {
        this->node = node;
    }
void Room::generate(bool exit, bool chest, bool enemy,std::vector<std::vector<char>> *map,bool boss)
    {
    //генерация содержимого комнаты(выход,сундук, противник)
        if (exit) {
            this->exit.first = rand() % (node->width-1 ) + node->x+1;
            this->exit.second = rand() % (node->height-1) + node->y + 1;
           
        }
        
        if (chest) {
            this->chest.first = rand() % (node->width - 1) + node->x + 1;
            this->chest.second = rand() % (node->height - 1) + node->y + 1;
            if (this->chest == this->exit) this->chest.second + 1;
        }
        
        if (enemy) {
            std::pair<int, int> enemy_coords;
            enemy_coords.first = rand() % (node->width - 1) + node->x + 1;
            enemy_coords.second = rand() % (node->height - 1) + node->y + 1;

            std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>(Enemy(enemy_coords, map, this->node, boss));
            enemies.push_back(enemy);
            if (rand() % 4 == 3) {
                std::pair<int, int> enemy2_coords;
                enemy2_coords.first = rand() % (node->width - 1) + node->x + 1;
                enemy2_coords.second = rand() % (node->height - 1) + node->y + 1;
                

                if (enemy_coords != enemy2_coords) {
                    std::shared_ptr<Enemy> enemy2 = std::make_shared<Enemy>(Enemy(enemy_coords, map, this->node, false));
                    enemies.push_back(enemy2);
                }
            }
        }
        

    }
std::vector<std::shared_ptr<Enemy>>* Room::get_enemies() { return &this->enemies; }
std::pair<int, int> Room::get_chest() { return this->chest; }
std::pair<int, int> Room::get_exit() { return this->exit; }
BSPNode* Room::get_node() { return this->node; }



    
void Map::connectRooms(BSPNode* node, std::vector<std::vector<char>>& map) {
        if (!node->isLeaf) {
            if (node->left) connectRooms(node->left, map);
            if (node->right) connectRooms(node->right, map);

            if (node->left && node->right) {
                BSPNode* leftRoom = getLeafRoom(node->left);
                BSPNode* rightRoom = getLeafRoom(node->right);
                //получаем конечные комнаты и начинаем соединять их коридорами

                int startX = leftRoom->x + leftRoom->width / 2;
                int startY = leftRoom->y + leftRoom->height / 2;
                int endX = rightRoom->x + rightRoom->width / 2;
                int endY = rightRoom->y + rightRoom->height / 2;
                //соединяем от центра одной комнаты до центра другой комнаты
                while (startX != endX) {
                    map[startY][startX] = '.';//соединяем точками
                    startX += (endX - startX) / abs(endX - startX);
                }

                while (startY != endY) {
                    map[startY][startX] = '.';
                    startY += (endY - startY) / abs(endY - startY);
                }
            }
        }
    }
void Map::drawRooms(BSPNode* node, std::vector<std::vector<char>>& map) {
        if (node->isLeaf) {
            for (int y = node->y; y < node->y + node->height; ++y) {
                for (int x = node->x; x < node->x + node->width; ++x) {
                    if ( (y==node->y)|| (y == node->y-node->height)|| (x == node->x) || (x == node->x+node->width)){//условие для границы комнаты
                        map[y][x] = '#';//ставим стенку
                        
                    }
                    else {
                    
                        map[y][x] = '.';//ставим пустое пространство
                    }
                }
            }
        }
        else {
            if (node->left) drawRooms(node->left, map);
            if (node->right) drawRooms(node->right, map);
        }
    }
BSPNode* Map::getLeafRoom(BSPNode* node) {
        //эта функция рекурсивно ищет конечную комнату( у которой параметр isLeaf==true)
        if (node->isLeaf) return node;
        BSPNode* leftRoom = getLeafRoom(node->left);
        BSPNode* rightRoom = getLeafRoom(node->right);
        return (leftRoom ? leftRoom : rightRoom);
    }
bool Map::split(BSPNode* node, int minRoomSize) {
        if (node->width <= minRoomSize * 2 && node->height <= minRoomSize * 2) {// если комнату делить уже нельзя
            return false;
        }

        bool splitH = rand() % 2 == 0;// определяем как её делить
        if (node->width > node->height && node->width / node->height >= 1.25) {// если комната шире,то горизонтально делить не стоит
            splitH = false;
        }
        else if (node->height > node->width && node->height / node->width >= 1.25) {// если комната выше, то вертикально делить не стоит
            splitH = true;
        }

        int max = (splitH ? node->height : node->width) - minRoomSize;// определяем, можно ли делить дальше
        if (max <= minRoomSize) {// если максимум оказался меньше минимального размера комнаты, то делить нельзя
            return false;
        }

        int splitPos = rand() % (max - minRoomSize) + minRoomSize;//определяем на какой позиции будем делить
        //делим
        if (splitH) {
            node->left = new BSPNode(node->x, node->y, node->width, splitPos);
            node->right = new BSPNode(node->x, node->y + splitPos, node->width, node->height - splitPos);
        }
        else {
            node->left = new BSPNode(node->x, node->y, splitPos, node->height);
            node->right = new BSPNode(node->x + splitPos, node->y, node->width - splitPos, node->height);
        }

        node->isLeaf = false;
        //делим левый и правый узел
        split(node->left, minRoomSize);
        split(node->right, minRoomSize);

        return true;
    }
void Map::createRooms(BSPNode* node, int minRoomSize, int maxRoomSize) {
        if (node->isLeaf) {//комната конечная значит можно делить
            int roomWidth = rand() % (maxRoomSize - minRoomSize + 1) + minRoomSize;
            int roomHeight = rand() % (maxRoomSize - minRoomSize + 1) + minRoomSize;
            int roomX, roomY;
            //проверка на неправильность генерации ширины и высоты комнаты
            if ((node->width - roomWidth + 1) != 0 && (node->height - roomHeight + 1)!=0) {
                //определяем координаты верхнего левого угла комнаты
                roomX = node->x + rand() % (node->width - roomWidth + 1);
                roomY = node->y + rand() % (node->height - roomHeight + 1);
            }
            
            else
            {
                //определяем координаты верхнего левого угла комнаты
                roomX = node->x;
                roomY = node->y;
            }

            node->x = roomX;
            node->y = roomY;
            // проверка комнаты на выход за пределы карты
            if ((roomWidth + roomX) > MAX_MAP_WIDTH) node->width = MAX_MAP_WIDTH - roomX - 1;
            else if ((roomWidth + roomX) == MAX_MAP_WIDTH-1 || (roomWidth + roomX) == MAX_MAP_WIDTH)  node->width = roomWidth - 1;
            else node->width = roomWidth;
            if ((roomHeight + roomY) > MAX_MAP_HEIGHT) node->height = MAX_MAP_HEIGHT-roomY-1;
            else if ((roomHeight + roomY) == MAX_MAP_HEIGHT-1 || (roomHeight + roomY) == MAX_MAP_HEIGHT)  node->height = roomHeight - 1;
            else node->height = roomHeight;
            
            nodes_of_rooms.push_back(node);// добавляем этот узел(из него потом гененрируются комнаты)
        }
        else {
            //если комната не конечная, ищем дальше
            if (node->left) createRooms(node->left, minRoomSize, maxRoomSize);
            if (node->right) createRooms(node->right, minRoomSize, maxRoomSize);
        }
    }
void Map::CreateRoomContents(std::vector<std::vector<char>>& map) {
        rooms.push_back(new Room(nodes_of_rooms[0]));
        //создаём содержимое комнат
        for (int i = 1; i < nodes_of_rooms.size();i++) {
                
                Room* room = new Room(nodes_of_rooms[i]);
                bool chest=false, enemy=false, exit=false;
                
                BSPNode* node = room->get_node();
                if (this->enemies_number < MAX_ENEMY_NUMBER) {
                    if ((rand() % static_cast<int>((enemy_veroyatnost * 2))) == 0) { enemy = true; this->enemies_number++; }
                }
                if (this->chests_number < MAX_CHEST_NUMBER) {
                    if ((rand() % static_cast<int>((chest_veroyatnost * 2))) == 0) {chest = true; this->chests_number++;}
                }
                if (this->exits_number < MAX_EXIT_NUMBER) {
                    if ( ((rand() % static_cast<int>((exit_veroyatnost * 2))) == 0) || this->exits_number==0) { exit = true; this->exits_number++; }
                }
                std::vector<std::vector<char>>* map_ptr = &generated_map;
                if (!chest && !enemy && !exit) {
                    //Спецкомната
                    if ((rand() % static_cast<int>(shop_veroyatnost * 2) == 0)&&!shop_exists) { map[node->y + node->height / 2][node->x + node->width / 2] = 'S'; shop_exists = true; }
                }
                else {
                    //если на 6 этаже не существует босса, то нужно его сгенерировать
                    if (current_etage == 6 && !boss_exists) {
                        room->generate(false, chest, true, map_ptr,true);
                        boss_exists = true;
                    }
                    else {
                        //иначе нет
                        //также проверяем не 6 этаж ли это.(6 этаж лишён выходов)
                        room->generate((current_etage==6)?false:exit, chest, enemy, map_ptr, false);
                    }
                }
                rooms.push_back(room);//добавляем в комнаты
                //добавляем содержимое комнаты на карту
                std::pair<int, int> exit_coords = room->get_exit();
                std::pair<int, int> chest_coords = room->get_chest();
                std::vector<std::shared_ptr<Enemy>>* enemies = room->get_enemies();
                if (exit_coords.first!=0 && exit_coords.second!=0) map[exit_coords.second][exit_coords.first] = 'R';
                if (chest_coords.first!=0 && chest_coords.second!=0) map[chest_coords.second][chest_coords.first] = '$';
                for (auto& enemy : (*enemies)) {

                    std::pair<int, int> enemy_coord = (*enemy).get_coords();
                    if (enemy_coord.first != 0 && enemy_coord.second != 0) {
                        if (map[enemy_coord.second][enemy_coord.first] == 'R') {
                            enemy_coord.second++;
                        }
                        if (enemy->type == THEBOSS) {
                            map[enemy_coord.second][enemy_coord.first] = 'B';
                        }
                        else map[enemy_coord.second][enemy_coord.first] = 'E';
                        
                    }
                }


            

        }
        
    }
    
   
void Map::CleanALL() {
    //удаляем всё динамически выделенное
    DeleteBSPNode(root_node);
    for (auto& room : rooms) {
        room->get_enemies()->clear();
        delete room;
    }
    nodes_of_rooms.clear();
    rooms.clear();
    //сбрасываем количество
    exits_number = 0;
    chests_number = 0;
    enemies_number = 0;
    shop_exists = false;
}

void Map::generate(bool regenerate) {
    //генерация карты
    if (regenerate) {
        CleanALL();//очищаем всё при регенерации
     }
        srand(static_cast<unsigned>(time(nullptr)));// учитываем время при рандомизации
        std::vector<std::vector<char>> map(MAX_MAP_HEIGHT, std::vector<char>(MAX_MAP_WIDTH, '#'));//пустая карта
        BSPNode* root = new BSPNode(0, 0, MAX_MAP_WIDTH, MAX_MAP_HEIGHT);// комната размером во всю карту, которую мы будем делить на маленькие
        root_node = root;
        split(root, minRoomSize);//делим root_node
        createRooms(root, minRoomSize, maxRoomSize);//создаём комнаты
        drawRooms(root, map);//отрисовываем их на карте
        connectRooms(root, map);//соединяем коридорами
        CreateRoomContents(map);//создаём содержимое комнаты
        generated_map = map;//карта сгенерирована



        }
Map::Map(int& current_etage_ad):current_etage(current_etage_ad) {
    this->map_width = MAX_MAP_WIDTH;
    this->map_height = MAX_MAP_HEIGHT;
}
void Map::DeleteBSPNode(BSPNode* node) {
    if (node->left) DeleteBSPNode(node->left);
    if (node->right) DeleteBSPNode(node->right);
    delete node;
}

std::pair<int, int> Map::spawn_player() {//создаём игрока
        BSPNode* node = nodes_of_rooms[0];
        std::pair<int, int> player_coords = { node->x + node->width / 2,node->y + node->height / 2 };
        SetXY(player_coords.first, player_coords.second);
        std::cout << u8"\u263A";
        generated_map[player_coords.second][player_coords.first] = 'P';
        return player_coords;
    }




    
    