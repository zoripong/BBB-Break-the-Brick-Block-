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

};

#endif