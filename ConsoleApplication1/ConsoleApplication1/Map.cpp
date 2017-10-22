#include<iostream>
#include<string>
#include<conio.h>
#include "Map.h"

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

extern void gotoxy(int x, int y);

//Map();
//~Map();
//int getWidth();
//int getHeight();
//void drawFrame();

//int width;
//int height;
//int **coordInfo;
string Map::mapChar[11] = { "  ", "¡à", "¢Ã", "¡Ú", "¡á", "¡á", "¡á", "¡ê", "¢Õ", "¡Ý", "¢Ì"};
const char* Map::mapFileName[15] = { 
	"./map/stage_01.txt", "./map/stage_02.txt", "./map/stage_03.txt", "./map/stage_04.txt", "./map/stage_05.txt",
	"./map/stage_06.txt", "./map/stage_07.txt", "./map/stage_08.txt", "./map/stage_09.txt", "./map/stage_10.txt",
	"./map/stage_11.txt", "./map/stage_12.txt", "./map/stage_13.txt", "./map/stage_14.txt", "./map/stage_15.txt" 
};

Map::Map(){
	width = 0;
	height = 0;
	coordInfo = 0;
};

Map::Map(int width, int height){
	this->width = width;
	this->height = height;

	coordInfo = new int*[height];
	for (int i = 0; i < height; i++)
		coordInfo[i] = new int[width];
}

Map::~Map(){
	if (coordInfo != 0){
		for (int i = 0; i < height; i++)
			delete[] coordInfo[i];
		delete[] coordInfo;
	}
}

int Map::getWidth(){
	return width;
}

int Map::getHeight(){
	return height;
}

void Map::drawFrame(){
	gotoxy(1, 1);
	//_getch();
	cout << "¢Ì";
	for (int i = 0; i < width - 2; i++)
		cout << "¢Ì";
	cout << "¢Ì";
	//_getch();
	//
	for (int i = 1; i <= height - 1; i++)
	{
		gotoxy(1, i + 1);
		cout << "¢Ì";
		for (int j = 0; j < width - 2; j++)
			cout << "  ";
		cout << "¢Ì";
	}
	//
	gotoxy(1, height + 1);
	cout << "¢Ì";

	for (int i = 0; i < width - 2; i++)
		cout << "¢Ì";
	cout << "¢Ì";

	printf("\n");

}

void Map::readMap(int stage){
	FILE *fp;
	int number;
	
	fp = fopen(mapFileName[stage - 1], "r");

	if (fp != NULL){
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				number = fgetc(fp)-48;
				if (number == 9)
					coordInfo[i][j] = -1;
				else coordInfo[i][j] = number;

			}
		}

	}

}	

void Map::drawMap(){
	gotoxy(1, 1);
		
	if (coordInfo != 0 && coordInfo[0][0] == -1){
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				if (coordInfo[i][j] == -1)
					cout << mapChar[10];
				else
					cout << mapChar[coordInfo[i][j]];
			}
			cout << endl;
		}
	}
}

void Map::setMap(int width, int height){
	this->width = width;
	this->height = height;

	coordInfo = new int*[height];
	for (int i = 0; i < height; i++)
		coordInfo[i] = new int[width];
}

void Map::drawInfo(string str, int score){
	gotoxy(this->width * 2 + 7, 3);
	cout << str << "´Ô";
	gotoxy(this->width * 2 + 8, 5);
	cout << score << "Á¡";
}

int Map::getCoodrInfo(int x, int y){
	if (coordInfo)
		return coordInfo[x][y];
	else
		return -2;
}