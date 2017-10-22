#include<iostream>
#include<conio.h>

#include "Ball.h"

using namespace std;

extern void gotoxy(int x, int y);

Ball::Ball(){
	moving = 0;
	life = 0;
	posX = 0;
	posY = 0;
	direction =  TOP;
	symbol = "○";
	beforeX = 0;
	beforeY = 0;
	nextX = 0;
	nextY = 0;
}	

Ball::Ball(int x, int y, int life, char *symbol){
	posX = x;

	if (posX % 2 == 1)
		posX -= 1;

	posY = y;
	this->life = life;
	moving = 0;
	direction = TOP;
	this->symbol = symbol;
	beforeX = posX;
	beforeY = posY;
	nextX = posX;
	nextY = posY;
}

void Ball::drawBall(){

	gotoxy(posX, posY);
	cout << symbol;
}

void Ball::setBall(int x, int y, int life, char *symbol){
	posX = x;
	if (posX % 2 == 0)
		posX -= 1;
	posY = y;
	this->life = life;
	moving = 0;
	direction = TOP;
}

void Ball::moveBall(){
	beforeX = posX;
	beforeY = posY;

	// TODO : 어디에 맞는지역시 중요..
	if (posX < 4 || posX > 28){
		switch (direction)
		{
		case TOP:
			direction = DOWN;
			break;
		case RIGHT_TOP:
			direction = LEFT_TOP;
			break;
		case RIGHT_DOWN:
			direction = LEFT_DOWN;
			break;
		case DOWN:
			direction = TOP;
			break;
		case LEFT_TOP:
			direction = RIGHT_TOP;
			break;
		case LEFT_DOWN:
			direction = RIGHT_TOP;
			break;
		}
	}
	else if (posY< 3){
		//_getch();
		switch (direction)
		{
		case TOP:
			direction = DOWN;
			break;
		case RIGHT_TOP:
			direction = RIGHT_DOWN;
			break;
		case LEFT_TOP:
			direction = LEFT_DOWN;
			break;
		}
		//_getch();
	}
	else if (posY  > 23){
		dieBall();
	}

	

	switch (direction){
	case TOP:
		posY--;
		nextX = posX;
		nextY = posY - 1;
		break;
	case RIGHT_TOP:
		posX+=2;
		posY--;
		nextX = posX + 1;
		nextY = posY - 1;
		break;
	case RIGHT_DOWN:
		posX+=2;
		posY++;
		nextX = posX + 1;
		nextY = posY + 1;
		break;
	case DOWN:
		posY++;
		nextX = posX ;
		nextY = posY + 1;
		break;
	case LEFT_DOWN:
		posX-=2;
		posY++;
		nextX = posX - 1;
		nextY = posY + 1;
		break;
	case LEFT_TOP:
		posX-=2;
		posY--;
		nextX = posX - 1;
		nextY = posY - 1;
		break;
	}

}

void Ball::dieBall(){
	// TODO
}

void Ball::removeBefore(){
	gotoxy(beforeX, beforeY);
	printf("  ");
}

// setters and getters
void Ball::setX(int x){
	this->posX = x;
}


int Ball::getX(){
	return this->posX;
}

void Ball::setY(int y){
	this->posY = y;
}
int Ball::getY(){
	return this->posY;
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

int Ball::getNextX(){
	return this->nextX;
}
int Ball::getNextY(){
	return this->nextY;
}