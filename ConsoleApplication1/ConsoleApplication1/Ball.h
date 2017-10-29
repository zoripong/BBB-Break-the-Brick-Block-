#ifndef __BALL_H__
#define __BALL_H__

using namespace std;

typedef enum DIRECTION{
	TOP = 0, RIGHT_TOP, LEFT_TOP, DOWN, RIGHT_DOWN, LEFT_DOWN
}DIRECTION;

class Ball{
private:
	int moving;
	int life;
	int calX, calY;
	int drawX, drawY;
	int deleteX, deleteY;
	DIRECTION direction;
	char * symbol;
	//clock_t moveTime;
	//clock_t oldTime;

public:
	Ball();
	Ball(int x, int y, int life, char * symbol);
	
	void drawBall();
	void setBall(int x, int y, int life, char *symbol);
	int moveBall();
	void removeBefore();
	void dieBall();

	//setters and getters
	void setCalX(int x);
	int getCalX();
	void setCalY(int y);
	int getCalY();
	void setMoving(int moving);
	int isMoving();
	void setLife(int life);
	int getLife();
	void setDirection(DIRECTION direction);
	DIRECTION getDirection();
	int getdeleteX();
	int getdeleteY();

	int getDrawX();
	int getDrawY();

	void crushFrame();
	void calculateCoord(DIRECTION direction);
	void crushSide();
	void crushUpDown();
	void crushDiagonal();

};


#endif

