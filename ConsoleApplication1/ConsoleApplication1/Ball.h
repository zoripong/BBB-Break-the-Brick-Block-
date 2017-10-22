#ifndef __BALL_H__
#define __BALL_H__

using namespace std;

typedef enum DIRECTION{
	TOP = 0, RIGHT_TOP, RIGHT_DOWN, DOWN, LEFT_TOP, LEFT_DOWN
}DIRECTION;

class Ball{
private:
	int moving;
	int life;
	int posX, posY;
	int beforeX, beforeY;
	int nextX, nextY;
	DIRECTION direction;
	char * symbol;
	//clock_t moveTime;
	//clock_t oldTime;

public:
	Ball();
	Ball(int x, int y, int life, char * symbol);
	
	void drawBall();
	void setBall(int x, int y, int life, char *symbol);
	void moveBall();
	void removeBefore();
	void dieBall();

	//setters and getters
	void setX(int x);
	int getX();
	void setY(int y);
	int getY();
	void setMoving(int moving);
	int isMoving();
	void setLife(int life);
	int getLife();
	void setDirection(DIRECTION direction);
	DIRECTION getDirection();
	int getNextX();
	int getNextY();

};


#endif

