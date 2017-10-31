#include<iostream>
#include<string>
#include<conio.h>
#include<ctime>
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
void Item::drawItem(){
	gotoxy(posX, posY);
	cout << mapChar[itemType];
}
void Item::down(){
	
	deleteX = posX;
	deleteY = posY;

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
