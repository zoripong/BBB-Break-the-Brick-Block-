#include<iostream>
#include<conio.h>
#include<Windows.h>
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

Ball::Ball(int x, int y, int life, char * symbol, int mapWidth, int mapHeight){
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

	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
}

void Ball::drawBall(){
	gotoxy(drawX, drawY);
	cout << symbol;
}

void Ball::setBall(int x, int y, int life, char *symbol, int mapWidth, int mapHeight){
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

	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
}

int Ball::moveBall(){
	deleteX = drawX;
	deleteY = drawY;
	drawX = calX;
	drawY = calY;
	
	//DEBUG
	//cout << drawX << ", " << drawY <<"       ";
	// 좌표 계산
	calculateCoord();

	return 0;
}

void Ball::dieBall(){
	// TODO
	//DEBUG

	this->life--;


}

int Ball::crushFrame(){
	if (drawX < 5 || drawX > (mapWidth-2)*2){
		crushSide();
	}
	else if (calY < 2){
		crushUpDown();
	}
	else if (drawY  > mapHeight-2){
		//DEBUG
		system("color 4F");
		Sleep(200);
		system("color 0F");
		
		dieBall();
		crushUpDown();
		return life;

	}
	return -1;
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

void Ball::crushBar(){

	switch (this->direction)
	{
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
		if (calY >= 2)
			calY--;
		break;
	case RIGHT_TOP:
		if (calX <= (mapWidth-2) * 2)
			calX += 2;
		if (calY >= 2)
			calY--;
		break;
	case RIGHT_DOWN:
		if (calX <= (mapWidth - 2) * 2)
			calX += 2;
		if (calY <= mapHeight - 2)
			calY++;
		break;
	case DOWN:
		if (calY <= mapHeight - 2)
			calY++;
		break;
	case LEFT_DOWN:
		if (calX >= 5)
			calX -= 2;
		if (calY  <= mapHeight - 2)
			calY++;
		break;
	case LEFT_TOP:
		if (calX >= 5)
		calX -= 2;
		if (calY  >= 2)
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


// TODO 범위지정
void Ball::setDirection(DIRECTION direction){
	this->direction = direction;
	
	switch (direction){
	case TOP:
		calX = drawX;
		if (drawY > 2)
			calY = drawY - 1;
		break;
	case RIGHT_TOP:
		calX = drawX + 2;
		if (drawY  > 2)
			calY = drawY - 1;
		break;
	case LEFT_TOP:
		calX = drawX - 2;
		if (drawY  > 2)
			calY = drawY - 1;
		break;
	case DOWN:
		calX = drawX;
		if (drawY+1 <= mapHeight - 2)
			calY = drawY + 1;
		break;
	case RIGHT_DOWN:
		calX = drawX + 2;
		if (drawY + 1 <= mapHeight - 2)
			calY = drawY + 1;
		break;
	case LEFT_DOWN:
		calX = drawX - 2;
		if (drawY + 1 <= mapHeight - 2)
			calY = drawY + 1;
		break;
	}
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

void Ball::moveRight(int crushX, int frameWidth){
	if (drawX < frameWidth * 2 - (5-crushX+1)*2){
		gotoxy(drawX, drawY);
		cout << "  ";
		deleteX = drawX;
		deleteY = drawY;
		drawX += 2;
		calX += 2;
	}

}

void Ball::moveLeft(int crushX){
	if (drawX > 3+crushX*2){
		gotoxy(drawX, drawY);
		cout << "  ";
		deleteX = drawX;
		deleteY = drawY;
		drawX -= 2;
		calX -= 2;
	}

}
	

void Ball::ballInit(int width, int height){
	gotoxy(drawX, drawY);
	cout << "  ";
	int x = width;
	int y = height - 2;
	drawX = x;
	if (drawX % 2 == 0)
		drawX -= 1;
	drawY = y;

	direction = TOP;

	calX = drawX;
	calY = drawY;
	calculateCoord();

	deleteX = -1;
	deleteY = -1;

}

int Ball::getLife(){
	return this->life;
}

void Ball::setLife(int life){
	this->life = life;
}