#include<iostream>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<ctime>

#include "Map.h"

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

extern void gotoxy(int x, int y);


string Map::mapChar[11] = { "  ", "□", "▣", "★", "■", "■", "■", "↔", "↕", "◎", "▩" };
const char* Map::mapFileName[15] = {
	"./map/stage_02.txt", "./map/stage_02.txt", "./map/stage_03.txt", "./map/stage_04.txt", "./map/stage_05.txt",
	"./map/stage_06.txt", "./map/stage_07.txt", "./map/stage_08.txt", "./map/stage_09.txt", "./map/stage_10.txt",
	"./map/stage_11.txt", "./map/stage_12.txt", "./map/stage_13.txt", "./map/stage_14.txt", "./map/stage_15.txt"
};
int itemType[4] = { 3, 7, 8, 9 };

Map::Map(int stage){
	width = 0;
	height = 0;
	coordInfo = 0;
	treasureCount = 0;
	this->stage = stage;
	srand((unsigned int)time(NULL));

};

Map::Map(int stage, int width, int height){
	this->stage = stage;
	this->width = width;
	this->height = height;
	treasureCount = 0;
	coordInfo = new int*[height];
	for (int i = 0; i < height; i++)
		coordInfo[i] = new int[width];

	srand((unsigned int)time(NULL));
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
	cout << "▩";
	for (int i = 0; i < width - 2; i++)
		cout << "▩";
	cout << "▩";
	//_getch();
	//
	for (int i = 1; i <= height - 1; i++)
	{
		gotoxy(1, i + 1);
		cout << "▩";
		for (int j = 0; j < width - 2; j++)
			cout << "  ";
		cout << "▩";
	}
	//
	gotoxy(1, height + 1);
	cout << "▩";

	for (int i = 0; i < width - 2; i++)
		cout << "▩";
	cout << "▩";

	printf("\n");

}

void Map::readMap(){
	FILE *fp;
	int number;

	fp = fopen(mapFileName[stage], "r");

	if (fp != NULL){
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				number = fgetc(fp) - 48;
				if (number == 9)
					coordInfo[i][j] = -1;
				else {
					if (number == 5 || number == 2){
						treasureCount++;
					}
					coordInfo[i][j] = number;
				}
			}
		}

	}

}

void Map::drawMap(){
	system("cls");
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

void Map::drawInfo(string str, int score, int count){
	gotoxy(this->width * 2 + 7, 3);
	cout << str << "님";
	gotoxy(this->width * 2 + 8, 4);
	cout << score << "점";
	gotoxy(this->width * 2 + 8, 5);
	cout << "남은 목숨 " << count << "개";

}

int Map::getCoodrInfo(int x, int y){
	if (coordInfo){
		if (x >= 0 && x < getHeight() && y >= 0 && y < getWidth())
			return coordInfo[x][y];
		else
			return -2;
	}
	else
		return -2;
}

int Map::changeBlock(int blockType, int x, int y){

	if (blockType == 1){
		//DELETE BLOCK
		coordInfo[y][x] = 0;
	}
	else if(blockType == 2){
		coordInfo[y][x] = 0;
		treasureCount--;
	}
	else if (blockType == 6){
		//NOTE : DROP THE ITEM
		coordInfo[y][x] = 0;

	}
	else if (blockType == 4 || blockType == 5){
		//NOTE : BLOCK SETTING		
		coordInfo[y][x] = coordInfo[y][x] - 3;

	}
	else{
		return 0;
	}
	updateMap(coordInfo[y][x], x, y);
	return blockType;
}

int Map::checkTop(int x, int y){
	// type, coord X, coord Y
	return changeBlock(getCoodrInfo(y - 2, x / 2), x / 2, y - 2);
}
int Map::checkRight(int x, int y){
	return changeBlock(getCoodrInfo(y - 1, (x + 2) / 2), (x + 2) / 2, y - 1);
}
int Map::checkLeft(int x, int y){
	return changeBlock(getCoodrInfo(y - 1, (x - 2) / 2), (x - 2) / 2, y - 1);

}
int Map::checkDown(int x, int y){
	return changeBlock(getCoodrInfo(y, x / 2), x / 2, y);
}

int Map::checkDiagonal(int direction, int x, int y){

	switch (direction){

	case 1: // RIGHT_TOP
		return changeBlock(getCoodrInfo(y - 2, (x + 2) / 2), (x + 2) / 2, y - 2);
	case 2: // LEFT_TOP
		return changeBlock(getCoodrInfo(y - 2, (x - 2) / 2), (x - 2) / 2, y - 2);
	case 4: // RIGHT_DOWN
		return changeBlock(getCoodrInfo(y, (x + 2) / 2), (x + 2) / 2, y);
	case 5: // LEFT_DOWN
		return changeBlock(getCoodrInfo(y, (x - 2) / 2), (x - 2) / 2, y);
	}
	return 0;
}

void Map::drawDebugingMap(){
	gotoxy(1, 1);

	for (int i = 0; i < getHeight(); i++){
		for (int j = 0; j < getWidth(); j++){
			cout << getCoodrInfo(i, j) << " ";
		}
		cout << endl;
	}

	cout << endl;
	cout << endl;
	cout << "보물 개수 : " << treasureCount;

}

void Map::updateMap(int type, int x, int y){
	gotoxy(x*2 +1, y +1);
	cout << mapChar[type];
}

void Map::treasureRemove(){
	(this->treasureCount)--;
}

int Map::getTreasureCount(){
	return treasureCount;
}

void Map::nextStage(){
	stage++;
	system("cls");
	drawFrame();
	gotoxy(width-5, height-11);
	cout << "NEXT  STAGE";
	
	system("color 3F");
	Sleep(1000);
	system("color 0F"); 
	readMap();
	drawMap();
}
void Map::randomBomb(){
	for (int i = 0; i < 5; i++){
		int x = rand() % height;
		int y = rand() % width/2;
		coordInfo[x][y] = 0;
	}
}