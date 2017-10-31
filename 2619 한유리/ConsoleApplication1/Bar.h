#ifndef __BAR_H__
#define __BAR_H__

using namespace std;

class Bar{
private:
	int *posX; // Bar¿« ¡ﬂΩ…
	int posY;
	int length;
	int beforeX;
	int frameWidth;
public:
	Bar();
	Bar(int width, int height, int length);
	~Bar();

	int getLength();
	int* getPositionX();
	void drawBar();
	void setBar(int width, int height, int length);
	void removeBeforeX();

	void moveLeft();
	void moveRight();
	
	int crushBar(int x, int y);

	void barInit(int width, int height);

	int checkX(int x);
};


#endif