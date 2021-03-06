#include<iostream>
#include<conio.h>

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
	if (posX != 0)
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

		cout << "��";
		for (int i = 1; i < length - 1; i++)
			cout << "��";
		cout << "��";
	}
}

void Bar::setBar(int width, int height, int length){
	if (posX == 0)
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
	// todo ��ǥ ���
	if (posX[0] > 3){
		beforeX = posX[length - 1];
		for (int i = 0; i < length; i++){
			posX[i] -= 2;
		}
	}
}
void Bar::moveRight(){
	// todo ��ǥ ���
	//cout << posX[length-1]<< "<"<<frameWidth * 2 -4;
	if (posX[length - 1] < frameWidth * 2 - 2){
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

int Bar::crushBar(int x, int y){

	if (y == posY - 1){
		for (int i = 0; i < length; i++){
			if (x == posX[i]){
				return i;
			}
		}
	}

	return -1;
}

void Bar::barInit(int width, int height){
	for (int i = 0; i < length; i++){
		gotoxy(posX[i], posY);
		cout << "  ";
	}
	if (width % 2 == 0)
		width -= 1;
	int value = (length - 1) * -1;
	for (int i = 0; i < length; i++){
		posX[i] = width + value;
		value += 2;
	}
	posY = height - 1;

}
int Bar::checkX(int x){

	for (int i = 0; i < length; i++){
		if (x == posX[i])
			return 1;
	}
	return 0;
}