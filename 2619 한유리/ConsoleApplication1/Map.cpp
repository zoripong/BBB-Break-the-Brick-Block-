#include<iostream>
#include<string>
#include<conio.h>
#include<Windows.h>
#include<ctime>

#include "Map.h"

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

extern void gotoxy(int x, int y);


// count 1 2 4 5 6
int Map::blockCount[10] = { 0,};

string Map::mapChar[11] = { "  ", "□", "▣", "★", "■", "■", "■", "↔", "↕", "◎", "▩" };
const char* Map::mapFileName[15] = {
	"./map/stage_01.txt", "./map/stage_02.txt", "./map/stage_03.txt", "./map/stage_04.txt", "./map/stage_05.txt",
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

	// 초기화
	for (int i = 0; i < 10; i++){
		blockCount[i] = 0;
	}


	fp = fopen(mapFileName[stage], "r");

	if (fp != NULL){
		for (int i = 0; i < height; i++){
			for (int j = 0; j < width; j++){
				number = fgetc(fp) - 48;
				blockCount[number]++;
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

	// 호롤로 여기다
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
	for (int i = 0; i < 3; i++){
		gotoxy(width * 2 + 6, 3 + i);
		for (int j = 0; j < 10; j++)
			cout << "  ";
	}

	gotoxy(this->width * 2 + 8, 3);
	cout <<"     "<< str << "님";
	gotoxy(this->width * 2 + 8, 4);
	cout <<"     "<<score << "점";
	gotoxy(this->width * 2 + 8, 5);
	cout << "  남은 목숨 " << count << "개";

	int* a = getBlock();

	gotoxy(0, 0);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
	for (int i = 0; i < 3; i++){
		gotoxy(width * 2 + 6, 7+i);

		for (int j = 0; j < 10; j++){
			cout << "  ";
		}
	}
		


	gotoxy(width * 2 + 8, 7);
	cout << "기본 상자 : " << a[1] + a[4] <<"  ";
	gotoxy(width * 2 + 8, 8);
	cout << "보물 상자 : " << a[5] + a[2] << "  ";
	gotoxy(width * 2 + 8, 9);
	cout << "아이템 상자 : " << a[6] << " ";


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);


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

	if (blockType == 1 || blockType == 2 || blockType == 6){
		//DELETE BLOCK
		coordInfo[y][x] = 0;
		blockCount[blockType]--;
	}
	else if (blockType == 4 || blockType == 5){
		//NOTE : BLOCK SETTING		
		blockCount[coordInfo[y][x]]--;
		blockCount[coordInfo[y][x] - 3]++;

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
	cout << endl;
	cout << "보물 개수 : " << treasureCount;

}

void Map::updateMap(int type, int x, int y){
	gotoxy(x*2 +1, y +1);
	cout << mapChar[type];
}


int Map::getTreasureCount(){
	return blockCount[2] + blockCount[5];
}

int* Map::getBlock(){
	return blockCount;
}
void Map::showNextStage(){
	if (stage == 14)
		return;
	stage++;
	readMap();
	drawMap();

}

void Map::showPreviousStage(){
	if (stage == 0)
		return;

	stage--;
	readMap();
	drawMap();
}
int Map::getStage(){
	return stage;
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
void Map::showInner(){
	for (int i = 0; i < getHeight(); i++){
		for (int j = 0; j < getWidth(); j++){
			if (coordInfo[i][j] == 4){
				blockCount[4]--;
				blockCount[1]++;
				coordInfo[i][j] = 1;
			}
			else if (coordInfo[i][j] == 5){
				blockCount[5]--;
				blockCount[2]++;
				coordInfo[i][j] = 2;
			}
		}
	}
}

void Map::drawRect(int x, int y, int width, int height){

	gotoxy(x, y);

	for (int i = 0; i < height; i++){
		gotoxy(x, y + i);
		for (int j = 0; j < width; j++){
			if (i == 0){
				// 첫번째 줄
				if (j == 0)
					cout << "┌";
				else if (j == width - 1)
					cout << "┐";
				else
					cout << "─";
			}
			else if (i == height - 1){
				// 마지막 줄
				if (j == 0)
					cout << "└";
				else if (j == width - 1)
					cout << "┘";
				else
					cout << "─";
			}
			else{
				//가운데
				if (j == 0)
					cout << "│";
				else if (j == width - 1){
					gotoxy(x + (width - 1) * 2 - 1, y + i);
					cout << "│";
				}
				else
					j = width - 2;
			}
		}

	}

}



void Map::drawInit(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	gotoxy(getWidth() * 2 + 7, 14);
	cout << "   ↖   ↑   ↗    │";
	gotoxy(getWidth() * 2 + 7, 15);
	cout << "   q    w   e";
	gotoxy(getWidth() * 2 + 7, 16);
	cout << "  START : [space]";

	gotoxy(getWidth() * 2 + 7, 18);
	cout << " 방향을 선택하고";
	gotoxy(getWidth() * 2 + 7, 19);
	cout << "스페이스바를 꾸욱!";
	gotoxy(getWidth() * 2 + 7, 20);
	cout << "    미 선택 시";
	gotoxy(getWidth() * 2 + 7, 21);
	cout << " 자동 출발합니다.";


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	drawRect(getWidth() * 2 + 5, 12, 12, 12);
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 95);

	gotoxy(getWidth() * 2 + 11, 12);
	cout << " key 안내";

	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(0, 0);

}

void Map::bombMap(int x, int y){

	int coordSX = x - 2;

	int startX = x - 1;
	int startY = y - 1;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){

			//cout << coordInfo[startY + i - 1][startX / 2 + j - 1] << " : ";
			//cout << startY + i -1<< "/" << startX / 2 + j -1<< endl;
			blockCount[coordInfo[startY + i - 1][startX / 2 + j - 1]]--;
			coordInfo[startY + i - 1][startX / 2 + j - 1] = 0;
			gotoxy(coordSX + j * 2, startY + i);
			cout << "  ";
		}
	}

}

void Map::drawBlock(int index){
	cout << mapChar[index];
}