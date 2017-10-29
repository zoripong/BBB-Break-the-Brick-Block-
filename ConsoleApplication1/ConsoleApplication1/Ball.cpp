#include<iostream>
#include<conio.h>

#include "Ball.h"

using namespace std;

extern void gotoxy(int x, int y);

Ball::Ball(){
	moving = 0;
	life = 0;
	calX = 0;
	calY = 0;
	direction = TOP;
	symbol = "○";
	drawX = 0;
	drawY = 0;
	deleteX = 0;
	deleteY = 0;
}

Ball::Ball(int x, int y, int life, char *symbol){
	
	/*calX = x;
	if (calX % 2 == 1)
		calX -= 1;
	calY = y;*/

	drawX = x;
	if (drawX % 2 == 0)
		drawX -= 1;
	drawY = y;
	this->life = life;
	moving = 0;
	direction = TOP;
	this->symbol = symbol;
	
	calX = drawX;
	calY = drawY;
	calculateCoord();

	deleteX = -1;
	deleteY = -1;
}

void Ball::drawBall(){
	gotoxy(drawX, drawY);
	cout << symbol;
}

void Ball::setBall(int x, int y, int life, char *symbol){
	drawX = x;
	if (drawX % 2 == 0)
		drawX -= 1;
	drawY = y;

	this->life = life;
	moving = 0;
	direction = TOP;

	calX = drawX;
	calY = drawY;
	calculateCoord();

	deleteX = -1;
	deleteY = -1;
}

int Ball::moveBall(){
	
	// TODO 벽돌 충돌

	deleteX = drawX;
	deleteY = drawY;
	drawX = calX;
	drawY = calY;
	
	// 좌표 계산
	calculateCoord();

	return 0;
}

void Ball::dieBall(){
	// TODO
}

void Ball::crushFrame(){
	if (drawX < 4 || drawX > 28){
		crushSide();
	}
	else if (drawY< 3){
		crushUpDown();
	}
	else if (drawY  > 22){
		//DEBUG
		//dieBall();
		crushUpDown();

	}
}
void Ball::crushSide(){
	switch (this->direction)
	{
	case TOP:
		this->direction = DOWN;
		break;
	case RIGHT_TOP:
		this->direction = LEFT_TOP;
		break;
	case RIGHT_DOWN:
		this->direction = LEFT_DOWN;
		break;
	case DOWN:
		this->direction = TOP;
		break;
	case LEFT_TOP:
		this->direction = RIGHT_TOP;
		break;
	case LEFT_DOWN:
		this->direction = RIGHT_DOWN;
		break;
	}
	calX = drawX;
	calY = drawY;
	calculateCoord();

}

void Ball::crushUpDown(){
	switch (this->direction)
	{
	case TOP:
		this->direction = DOWN;
		break;
	case RIGHT_TOP:
		this->direction = RIGHT_DOWN;
		break;
	case LEFT_TOP:
		this->direction = LEFT_DOWN;
		break;
	case RIGHT_DOWN:
		this->direction = RIGHT_TOP;
		break;
	case DOWN:
		this->direction = TOP;
		break;
	case LEFT_DOWN:
		this->direction = LEFT_TOP;
		break;
	}
	calX = drawX;
	calY = drawY;
	calculateCoord();

}

void Ball::crushDiagonal(){
	switch (this->direction){
	case RIGHT_TOP:
		this->direction = LEFT_DOWN;
		break;
	case LEFT_TOP:
		this->direction = RIGHT_DOWN;
		break;
	case RIGHT_DOWN:
		this->direction = LEFT_TOP;
		break;
	case LEFT_DOWN:
		this->direction = RIGHT_TOP;
		break;
	}
	calX = drawX;
	calY = drawY;
	calculateCoord();

}

void Ball::calculateCoord(){
	switch (this->direction){
	case TOP:
		calY--;
		break;
	case RIGHT_TOP:
		calX += 2;
		calY--;
		break;
	case RIGHT_DOWN:
		calX += 2;
		calY++;
		break;
	case DOWN:
		calY++;
		break;
	case LEFT_DOWN:
		calX -= 2;
		calY++;
		break;
	case LEFT_TOP:
		calX -= 2;
		calY--;
		break;
	}

}

void Ball::removeBefore(){
	if (deleteX == -1 || deleteY == -1)
		return;
	gotoxy(deleteX, deleteY);
	printf("  ");
}

// setters and getters
void Ball::setCalX(int x){
	this->calX = x;
}

int Ball::getCalX(){
	return this->calX;
}

void Ball::setCalY(int y){
	this->calY = y;
}
int Ball::getCalY(){
	return this->calY;
}

void Ball::setMoving(int moving){
	this->moving = moving;
}

int Ball::isMoving(){
	return this->moving;
}

void Ball::setDirection(DIRECTION direction){
	this->direction = direction;
}

DIRECTION Ball::getDirection(){
	return this->direction;
}

int Ball::getdeleteX(){
	return this->deleteX;
}
int Ball::getdeleteY(){
	return this->deleteY;
}

int Ball::getDrawX(){
	return this->drawX;
}
int Ball::getDrawY(){
	return this->drawY;
}
