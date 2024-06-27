#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <ctime>

// йнд вюярхвмн ядекюм я онлныэч CHATGPT
// ме днбепърэ!!!

using namespace std;
struct BSPNode {
	int x, y, width, height;
	BSPNode* left;
	BSPNode* right;
	bool isLeaf;

	BSPNode(int x, int y, int width, int height)
		: x(x), y(y), width(width), height(height), left(nullptr), right(nullptr), isLeaf(true) {}
};
class Map {
    friend class Game;
private:
    const int MAX_MAP_WIDTH = 60;
    const int MAX_MAP_HEIGHT = 20;
    const int minRoomSize = 9;
    const int maxRoomSize = 12;
    // { 1:{enemies:{ {1,2},{2,3} },width_and_height:{{20,30}},chests:{{20,30},{30,40},exits:{1,2}} 2:{} 3:{}}

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
                        if (y == 19) {
                            cout << x << y <<" "<< node->width << node->height<<endl;
                        }
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
        }
        else {
            if (node->left) createRooms(node->left, minRoomSize, maxRoomSize);
            if (node->right) createRooms(node->right, minRoomSize, maxRoomSize);
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
        generated_map = map;



        }


    };