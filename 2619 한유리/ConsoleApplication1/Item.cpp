#include<iostream>
#include<string>
#include<conio.h>
#include<ctime>

#include "Ball.h"
#include "Map.h"
#include "Item.h"

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

extern void gotoxy(int x, int y);

//string Item::mapChar[4] = { "¡Ú",  "¡ê", "¢Õ", "¡Ý"};
string Item::mapChar[4] = { "¡Ú",  "¡Ú", "¡Ý", "¡Ý"};


Item::Item(int itemType, int x, int y){
	this->itemType = itemType;
	this->posX = x;
	this->posY = y;
	deleteX = -1;
	deleteY = -1;
	srand((unsigned int)time(NULL));

}
void Item::drawItem(Map & map, Ball & ball){


	gotoxy(posX, posY);
	if (map.getCoodrInfo(posX, posY / 2) == 0 && !(ball.getDrawX() == posX && ball.getDrawY() == posY)){
		cout << mapChar[itemType];
	}

}
void Item::down(Map & map, Ball & ball){
	
	deleteX = posX;
	deleteY = posY;

	if (map.getCoodrInfo(deleteX, deleteY / 2 - 1) != 0){
		deleteX = -1;
		deleteY = -1;
	}
	cout << deleteX << "&" << ball.getDrawX() << "/" << deleteY << "&" << ball.getDrawY() -1;
	if (deleteX == ball.getDrawX() && deleteY == ball.getDrawY()){
		deleteX = -1;
		deleteY = -1;

	}

	posY++;


}
void Item::removeBefore(){
	if (deleteX != -1 && deleteY != -1){
		gotoxy(deleteX, deleteY);
		cout << "  ";
	}
}

int Item::getPosX(){
	return posX;
}
int Item::getPosY(){
	return posY;
}


int Item::removeIt(){
	//TODO:
	gotoxy(posX, posY);
	cout << "  ";

	return itemType;

}

void randomBomb(){

}
