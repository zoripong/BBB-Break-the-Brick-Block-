#include<iostream>
#include<conio.h>
#include<Windows.h>
#include <string>
#include "Bar.h"
#include "Map.h"
#include "Ball.h"


using namespace std;

const int ORIGIN_BAR_LENGTH = 5;
const int INIT_LIFE = 3;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void gotoxy(int x, int y);
void setCursorType(CURSOR_TYPE c);

void mainScreen();
void explainScreen();
void showRecord(string user); // TODO
void startGame(string user); // TODO
void inputInfo(int type);
void setSelecter(int x, int y);
void printB(int x, int y, char * symbol);
void init(string & user, Map & map, Bar & bar, Ball & ball);
void update(Ball & ball, Map & map);
void render(Ball & ball, Map & map, Bar & bar);
void release();


int main(){

	setCursorType(NOCURSOR);
	mainScreen();
	return 0;

}

// hide the cursor
void setCursorType(CURSOR_TYPE c){
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

// control the coord
void gotoxy(int x, int y){
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 화면 컨트롤
void mainScreen(){
	system("mode con:cols=82 lines=31");

	system("color 2F");
	//system("color 0E");

	system("title BBB");

	printB(17, 5, "■");
	printB(15, 4, "□");

	printB(35, 7, "■");
	printB(33, 6, "□");

	printB(53, 4, "■");
	printB(51, 3, "□");

	gotoxy(25, 20);
	for (int i = 0; i < 30; i++)
		printf("=");

	gotoxy(32, 22);
	printf("GAME START");
	gotoxy(32, 24);
	printf("HOW TO PLAY");
	gotoxy(32, 26);
	printf("SHOW THE RECORD");
	gotoxy(25, 28);
	for (int i = 0; i < 30; i++)
		printf("=");
	setSelecter(50, 22);
}

void explainScreen(){
	system("cls");
	system("color 0E");

	// TODO : kbhit()과 함께 자동으로 게임 모습 실행
	printB(17, 5, "■");
	printB(15, 4, "□");

	printB(35, 7, "■");
	printB(33, 6, "□");

	printB(53, 4, "■");
	printB(51, 3, "□");

	gotoxy(23, 23);
	cout << "맵 속에 숨겨진 보물 벽돌을 깨라!▽";
	_getch();
	gotoxy(23, 23);
	cout << "                                         ";

	gotoxy(22, 23);
	cout << "BBB에 찾아오신 여러분, 안녕하세요.▽";
	_getch();
	gotoxy(22, 23);
	cout << "                                         ";

	gotoxy(20, 23);
	cout << "여러분들이 어렸을 적 자주 했던 블럭깨기▽";
	_getch();
	gotoxy(20, 23);
	cout << "                                         ";

	gotoxy(33, 23);
	cout << "기억나시나요?▽";
	_getch();
	gotoxy(33, 23);
	cout << "                                         ";

	gotoxy(26, 23);
	cout << "BBB 역시 똑같이 진행됩니다.▽";
	_getch();
	gotoxy(26, 23);
	cout << "                                         ";

	gotoxy(26, 23);
	cout << "먼저 여러분은 ■을 깨주세요.▽";
	_getch();
	gotoxy(26, 23);
	cout << "                                         ";

	gotoxy(23, 23);
	cout << "그럼 ■속 또다른 블럭이 나타납니다.▽";
	_getch();
	gotoxy(20, 23);
	cout << "                                         ";

	gotoxy(17, 23);
	cout << "□는 일반 블럭입니다. 깨도 그만 안 깨도 그만이죠▽";
	_getch();
	gotoxy(17, 23);
	cout << "                                         ";

	gotoxy(10, 23);
	cout << "▣는 보물 블럭입니다! 깨지못하면 다음 스테이지로 넘어갈 수 없어요.▽";
	_getch();
	gotoxy(10, 23);
	cout << "                                                                     ";

	gotoxy(18, 23);
	cout << "보물블럭이 몇 개 숨겨져 있는지는 비밀입니다.▽";
	_getch();
	gotoxy(18, 23);
	cout << "                                                ";

	gotoxy(20, 23);
	cout << "하나하나 블럭을 깨며 쾌감을 느껴보세요.▽";
	_getch();
	gotoxy(20, 23);
	cout << "                                           ";

	gotoxy(17, 23);
	cout << "블럭을 깨다보면 아이템이 하나하나 떨어질거예요.▽";
	_getch();
	gotoxy(17, 23);
	cout << "                                                 ";

	gotoxy(30, 23);
	cout << "아이템 역시 복불복!▽";
	_getch();
	gotoxy(30, 23);
	cout << "                                           ";

	gotoxy(24, 23);
	cout << "↔ 이동 막대가 연장/단축 됩니다!▽";
	_getch();
	gotoxy(24, 23);
	cout << "                                           ";

	gotoxy(24, 23);
	cout << "↕ 맵의 길이가 연장/단축 됩니다!▽";
	_getch();
	gotoxy(24, 23);
	cout << "                                           ";

	gotoxy(26, 23);
	cout << "★ 주변 블럭이 파괴됩니다!▽";
	_getch();
	gotoxy(26, 23);
	cout << "                                           ";

	gotoxy(24, 23);
	cout << "@ 공의 개수가 임시로 추가됩니다!▽";
	_getch();
	gotoxy(24, 23);
	cout << "                                           ";

	gotoxy(17, 23);
	cout << "◁□□□▷ 여러분에게 주어진 것은 이동막대 뿐!▽";
	_getch();
	gotoxy(17, 23);
	cout << "                                                 ";

	gotoxy(17, 23);
	cout << "모든 보물을 찾아 스테이지를 모두 해결해보세요!▽";
	_getch();
	gotoxy(17, 23);
	cout << "                                                 ";

	gotoxy(24, 23);
	cout << "여러분의 기록이 쌓여가고 있답니다.▽";
	_getch();
	gotoxy(24, 23);
	cout << "                                                 ";

	mainScreen();
}

void showRecord(string user){
	system("cls");
	system("color 0E");
	cout << user;
}

void startGame(string user){
	int width = 16;
	int height = width * 3 / 2;

	Map map(width, height);
	Ball mainBall;
	Bar mvBar;

	init(user, map, mvBar, mainBall);

	//DEBUG
	_getch();
	system("cls");
	for (int i = 0; i < map.getHeight(); i++){
		for (int j = 0; j < map.getWidth(); j++){
			cout << map.getCoodrInfo(i, j) << " ";
		}
		cout << endl;
	}


	mainBall.setDirection(RIGHT_TOP);
	char nKey = 0;

	while (1)
	{
		if (_kbhit()){
			nKey = _getch();
			switch (nKey){
				// ←
			case 75:
				mvBar.moveLeft();
				break;
				// →
			case 77:
				mvBar.moveRight();
				break;
				// SPACE
			case 32:
				break;
			}

			mvBar.removeBeforeX();
			mvBar.drawBar();
		}
		Sleep(100);
		update(mainBall, map);
		render(mainBall, map, mvBar);
	}
	release();
}

void inputInfo(int type){
	system("cls");

	system("color 70");
	system("mode con:cols=24 lines=12");

	gotoxy(6, 5);
	printf("ID : ");

	gotoxy(5, 8);
	printf("Press the Enter");

	//DEBUG
	//setCursorType(SOLIDCURSOR);

	string user;
	do{
		gotoxy(11, 5);
		cout << "                  ";
		gotoxy(11, 5);

		getline(cin, user);
		if (user.length() > 8){
			gotoxy(8, 7);
			cout << "최대 8Byte";
		}
	} while (user.compare("") == 0 || user.length() > 8);

	setCursorType(NOCURSOR);
	if (type == 22)
		startGame(user);
	else if (type == 26)
		showRecord(user);

}

void setSelecter(int x, int y){
	int posX = x;
	int posY = y;

	gotoxy(posX, posY);

	printf("◁");

	char input;

	do{
		input = _getch();
		switch (input){
			// Enter
		case 13:
			if (posY == 22 || posY == 26)
				inputInfo(posY);
			else if (posY == 24)
				explainScreen();
			break;
			// ↑
		case 72:
			if (posY > 22){
				gotoxy(posX, posY);
				printf("  ");
				posY -= 2;
				gotoxy(posX, posY);
				printf("◁");
			}
			break;
			// ↓
		case 80:
			if (posY < 26){
				gotoxy(posX, posY);
				printf("  ");
				posY += 2;
				gotoxy(posX, posY);
				printf("◁");
			}
			break;

		}
	} while (input != 27 && input != 13);
}

void printB(int x, int y, char * symbol){
	//int x = 15;
	//int y = 4;
	//char * test = "□";
	const char * block = symbol;

	gotoxy(x, y);
	for (int i = 0; i < 4; i++)
		printf(block);

	gotoxy(x, y + 1);
	printf(block);
	gotoxy(x + 8, y + 1);
	printf(block);

	for (int i = 2; i <= 6; i++){
		if (i == 5){
			gotoxy(x, y + 5);
			for (int i = 0; i < 5; i++)
				printf(block);
		}
		else{
			gotoxy(x, y + i);
			printf(block);
			gotoxy(x + 10, y + i);
			printf(block);
		}
	}

	for (int i = 7; i <= 9; i++){
		gotoxy(x, y + i);
		printf(block);
		gotoxy(x + 12, y + i);
		printf(block);

	}

	gotoxy(x, y + 10);
	for (int i = 0; i < 6; i++)
		printf(block);
}


void init(string & user, Map & map, Bar & bar, Ball & ball){
	setCursorType(NORMALCURSOR);
	system("cls");
	system("color 0F");
	system("mode con:cols=60 lines=30");

	bar.setBar(map.getWidth(), map.getHeight(), ORIGIN_BAR_LENGTH);
	ball.setBall(map.getWidth(), map.getHeight() - 2, INIT_LIFE, "○");

	int stage = 1;
	map.readMap(stage);
	map.drawMap();
	map.drawInfo(user, 100);

	bar.drawBar();
	ball.drawBall();

}

void update(Ball & ball, Map & map){

	// DEBUG
	/*system("cls");
	for (int i = 0; i < map.getHeight(); i++){
	for (int j = 0; j < map.getWidth(); j++){
	cout << map.getCoodrInfo(i, j) << " ";
	}
	cout << endl;
	}*/

	// 공 위치 업데이트
	// DEBUG
	gotoxy(map.getWidth() * 2 + 9, 16);
	cout << "이후 이동 좌표" << endl;
	gotoxy(map.getWidth() * 2 + 10, 16);
	cout << "drawXY (" << ball.getDrawX() << ", " << ball.getDrawY() << ")";
	gotoxy(map.getWidth() * 2 + 10, 17);
	cout << "calXY (" << ball.getCalX() << ", " << ball.getCalY() << ")";

	gotoxy(map.getWidth() * 2 + 5, 18);
	//


	ball.crushFrame();

	int direction = ball.getDirection();
	if (direction >= TOP && direction <= LEFT_TOP){
		if (map.checkTop(ball.getDrawX(), ball.getDrawY()))
			ball.crushUpDown();
		gotoxy(map.getWidth() * 2 + 2, 19);
		if (direction == RIGHT_TOP){
			if (map.checkRight(ball.getDrawX(), ball.getDrawY()))
				ball.crushSide();
			map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY());
		}
		else if (direction == LEFT_TOP){
			if (map.checkLeft(ball.getDrawX(), ball.getDrawY()))
				ball.crushSide();
			map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY());

		}
	}
	else if (direction >= DOWN && direction <= LEFT_DOWN){
		if (map.checkDown(ball.getDrawX(), ball.getDrawY()))
			ball.crushUpDown();
		gotoxy(map.getWidth() * 2 + 2, 19);
		if (direction == LEFT_DOWN){
			if (map.checkLeft(ball.getDrawX(), ball.getDrawY()))
				ball.crushSide();
			if(map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY()))
				ball.crushDiagonal();

		}
		else if (direction == RIGHT_DOWN){
			if (map.checkRight(ball.getDrawX(), ball.getDrawY()))
				ball.crushSide();
			if(map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY()))
				ball.crushDiagonal();

		}
	}
	//DEBUG
	gotoxy(map.getWidth() * 2 + 9, 21);
	switch (ball.getDirection()){
	case 0:
		cout << "TOP        ";
		break;
	case 1:
		cout << "RIGHT_TOP  ";
		break;
	case 2:
		cout << "LEFT_TOP  ";
		break;
	case 3:
		cout << "DOWN       ";
		break;
	case 4:
		cout << "RIGHT_DOWN  ";
		break;
	case 5:
		cout << "LEFT_DOWN   ";
		break;
	}


	//int blockType = map.getCoodrInfo(ball.getCalY() - 1, ball.getCalX() / 2 + 1);
	//cout << "배열 좌표 (" << ball.getCalY() - 1 << ", " << ball.getCalX() / 2 + 1 << ") = " << blockType;

	gotoxy(map.getWidth() * 2 + 5, 19);

	ball.moveBall();
	_getch();

}

void render(Ball & ball, Map & map, Bar & bar){
	// 맵 출력
	//DEBUG
	//map.drawMap();

	// 공 출력
	ball.removeBefore();
	ball.drawBall();

	// 바 출력
	bar.drawBar();
}

void release(){

}


/*
COORD getXY()
{
COORD pos;
CONSOLE_SCREEN_BUFFER_INFO buf;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&buf);
pos.X = buf.dwCursorPosition.X;
pos.Y = buf.dwCursorPosition.Y;
return pos;
}

*/

/*
BAR TEST
int width = 16;
int height = width * 3 / 2;
drawFrame(width, height);
Bar b(width, height, 5);
int * test = b.getPositionX();

for (int i = 0; i < b.getLength(); i++)
cout << *(test + i) << endl;

b.drawBar();

_getch();*/
