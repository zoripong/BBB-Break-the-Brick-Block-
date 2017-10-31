#ifndef __ITEM_H__
#define __ITEM_H__

using namespace std;

class Item{
private:
	int itemType;
	int posX, posY;
	int deleteX, deleteY;
	static string mapChar[4];

public:
	Item(int itemType, int x, int y);
	void drawItem();
	void down();
	void removeBefore();
	int getPosX();
	int getPosY();
	int removeIt();
	void randomBomb();
	void increaseLife();
};

#endif