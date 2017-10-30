#include<iostream>
#include "Bar.h"

using namespace std;

extern void gotoxy(int x, int y);

Bar::Bar()
{
	posX = 0;
	posY = 0;
	length = 0;
	frameWidth = 0;
}
Bar::Bar(int width, int height, int length)
{
	posX = new int[length];
	if (width % 2 == 0)
		width -= 1;
	int value = (length - 1) * -1;
	for (int i = 0; i < length; i++){
		posX[i] = width + value;
		value += 2;
	}
	posY = height - 2;
	this->length = length;
	frameWidth = width;
	drawBar();
}

Bar::~Bar()
{
	if (posX!=0)
		delete[] posX;
}

int Bar::getLength(){
	return this->length;
}

int * Bar::getPositionX(){
	return posX;
}
	
void Bar::drawBar(){
	if (posX != 0){

		gotoxy(posX[0], posY);

		cout << "¢·";
		for (int i = 1; i < length - 1; i++)
			cout << "¡à";
		cout << "¢¹";
	}

	//gotoxy(frameWidth * 2 + 10, posY - 2);
	//cout << "posX[0] = " << posX[0];
	//gotoxy(frameWidth * 2 + 10, posY - 1);
	//cout << "posX[length-1] = " << posX[length - 1];
	//gotoxy(frameWidth * 2 + 10, posY);
	//printf("%d", beforeX);
}

void Bar::setBar(int width, int height, int length){
	posX = new int[length];
	if (width % 2 == 0)
		width -= 1;
	int value = (length - 1) * -1;
	for (int i = 0; i < length; i++){
		posX[i] = width + value;
		value += 2;
	}
	posY = height - 1;
	this->length = length;
	frameWidth = width;

	drawBar();
}

void Bar::moveLeft(){
	// todo ÁÂÇ¥ °æ°è
	if (posX[0] > 3){
		beforeX = posX[length - 1];
		for (int i = 0; i < length; i++){
			posX[i] -= 2;
		}


	}


}
void Bar::moveRight(){
	// todo ÁÂÇ¥ °æ°è
	//cout << posX[length-1]<< "<"<<frameWidth * 2 -4;
	if (posX[length - 1] < frameWidth * 2 -2){
		beforeX = posX[0];
		for (int i = 0; i < length; i++){
			posX[i] += 2;
		}

	}
}

void Bar::removeBeforeX(){
	gotoxy(beforeX, posY);
	printf("  ");
}

void Bar::crushBar(int x, int y){



}
