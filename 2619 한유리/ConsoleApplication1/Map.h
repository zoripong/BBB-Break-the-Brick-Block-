#ifndef __MAP_H__
#define __MAP_H__

using namespace std;

class Map{
private:
	int stage;
	int width;
	int height;
	int **coordInfo;
	static string mapChar[11];
	static int blockCount[10];

	static const char * mapFileName[15];
	static int itemType[4];
	int changeBlock(int blockType, int x, int y);

	int treasureCount;


public:
	Map(int stage);
	Map(int stage, int width, int height);
	~Map();
	int getWidth();
	int getHeight();
	void drawFrame();
	void readMap();
	void setMap(int width, int height);
	void drawInfo(string str, int score, int count);
	void drawMap();
	void drawDebugingMap();
	int getCoodrInfo(int x, int y);
	int checkTop(int x, int y);
	int checkRight(int x, int y);
	int checkLeft(int x, int y);
	int checkDown(int x, int y);
	int checkDiagonal(int direction, int x, int y);
	void updateMap(int type, int x, int y);

	void treasureRemove();
	int getTreasureCount();
	
	void showNextStage();
	void showPreviousStage();
	void nextStage();

	void randomBomb();
	int getStage();

	int* getBlock();

	void Map::drawRect(int x, int y, int width, int height);
};

#endif