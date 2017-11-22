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
string Item::mapChar[4] = { "¡Ù",  "¡Ý", "¢½", "¢½"};


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
	if (!(ball.getDrawX() == posX && ball.getDrawY() == posY)||itemType == 0){
		cout << mapChar[itemType];
	}

}
void Item::down(Map & map, Ball & ball){
	
	deleteX = posX;
	deleteY = posY;

	if (deleteX == ball.getDrawX() && deleteY == ball.getDrawY()){
		deleteX = -1;
		deleteY = -1;
	}

	posY++;


}
void Item::removeBefore(Map & map){
	if (deleteX != -1 && deleteY != -1){
		gotoxy(deleteX, deleteY);

		//cout << deleteX/2 << "&" << deleteY - 1 << " : " ;
		//cout << map.getCoodrInfo(deleteY - 1, deleteX / 2);
		map.drawBlock(map.getCoodrInfo(deleteY - 1, deleteX / 2));
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

int Item::getType(){
	return itemType;
}