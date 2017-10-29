#ifndef __MAP_H__
#define __MAP_H__

using namespace std;

class Map{
private:
	int width;
	int height;
	int **coordInfo;
	static string mapChar[11];
	static const char * mapFileName[15];
	static int itemType[4];

	void dropItem();
	int changeBlock(int blockType, int x, int y);
public:
	Map();
	Map(int width, int height);
	~Map();
	int getWidth();
	int getHeight();
	void drawFrame();
	void readMap(int stage);
	void setMap(int width, int height);
	void drawInfo(string str, int score);
	void drawMap();
	int getCoodrInfo(int x, int y);
	int checkTop(int x, int y);
	int checkRight(int x, int y);
	int checkLeft(int x, int y);
	int checkDown(int x, int y);
	int checkDiagonal(int direction, int x, int y);
};

#endif