#include<iostream>
#include<conio.h>
#include<Windows.h>
#include <string>
#include "Bar.h"
#include "Map.h"
#include "Ball.h"
#include "Player.h"


using namespace std;

const int ORIGIN_BAR_LENGTH = 5;
const int INIT_LIFE = 3;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void gotoxy(int x, int y);
void setCursorType(CURSOR_TYPE c);

void mainScreen();
void explainScreen();
void showRecord(string player); // TODO
void startGame(Player player); 
void inputInfo(int type);
void setSelecter(int x, int y);
void printB(int x, int y, char * symbol);
void init(Player & user, Map & map, Bar & bar, Ball & ball);
void update(Ball & ball, Map & map, Player & player);
void render(Ball & ball, Map & map, Bar & bar, Player & player);
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

// ȭ�� ��Ʈ��
void mainScreen(){
	system("mode con:cols=82 lines=31");

	system("color 2F");
	//system("color 0E");

	system("title BBB");

	printB(17, 5, "��");
	printB(15, 4, "��");

	printB(35, 7, "��");
	printB(33, 6, "��");

	printB(53, 4, "��");
	printB(51, 3, "��");

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

	// TODO : kbhit()�� �Բ� �ڵ����� ���� ��� ����
	printB(17, 5, "��");
	printB(15, 4, "��");

	printB(35, 7, "��");
	printB(33, 6, "��");

	printB(53, 4, "��");
	printB(51, 3, "��");

	gotoxy(23, 23);
	cout << "�� �ӿ� ������ ���� ������ ����!��";
	_getch();
	gotoxy(23, 23);
	cout << "                                         ";

	gotoxy(22, 23);
	cout << "BBB�� ã�ƿ��� ������, �ȳ��ϼ���.��";
	_getch();
	gotoxy(22, 23);
	cout << "                                         ";

	gotoxy(20, 23);
	cout << "�����е��� ����� �� ���� �ߴ� �������";
	_getch();
	gotoxy(20, 23);
	cout << "                                         ";

	gotoxy(33, 23);
	cout << "��ﳪ�ó���?��";
	_getch();
	gotoxy(33, 23);
	cout << "                                         ";

	gotoxy(26, 23);
	cout << "BBB ���� �Ȱ��� ����˴ϴ�.��";
	_getch();
	gotoxy(26, 23);
	cout << "                                         ";

	gotoxy(26, 23);
	cout << "���� �������� ���� ���ּ���.��";
	_getch();
	gotoxy(26, 23);
	cout << "                                         ";

	gotoxy(23, 23);
	cout << "�׷� ��� �Ǵٸ� ���� ��Ÿ���ϴ�.��";
	_getch();
	gotoxy(20, 23);
	cout << "                                         ";

	gotoxy(17, 23);
	cout << "��� �Ϲ� ���Դϴ�. ���� �׸� �� ���� �׸����ҡ�";
	_getch();
	gotoxy(17, 23);
	cout << "                                         ";

	gotoxy(10, 23);
	cout << "�ô� ���� ���Դϴ�! �������ϸ� ���� ���������� �Ѿ �� �����.��";
	_getch();
	gotoxy(10, 23);
	cout << "                                                                     ";

	gotoxy(18, 23);
	cout << "�������� �� �� ������ �ִ����� ����Դϴ�.��";
	_getch();
	gotoxy(18, 23);
	cout << "                                                ";

	gotoxy(20, 23);
	cout << "�ϳ��ϳ� ���� ���� �谨�� ����������.��";
	_getch();
	gotoxy(20, 23);
	cout << "                                           ";

	gotoxy(17, 23);
	cout << "���� ���ٺ��� �������� �ϳ��ϳ� �������ſ���.��";
	_getch();
	gotoxy(17, 23);
	cout << "                                                 ";

	gotoxy(30, 23);
	cout << "������ ���� ���Һ�!��";
	_getch();
	gotoxy(30, 23);
	cout << "                                           ";

	gotoxy(24, 23);
	cout << "�� �̵� ���밡 ����/���� �˴ϴ�!��";
	_getch();
	gotoxy(24, 23);
	cout << "                                           ";

	gotoxy(24, 23);
	cout << "�� ���� ���̰� ����/���� �˴ϴ�!��";
	_getch();
	gotoxy(24, 23);
	cout << "                                           ";

	gotoxy(26, 23);
	cout << "�� �ֺ� ���� �ı��˴ϴ�!��";
	_getch();
	gotoxy(26, 23);
	cout << "                                           ";

	gotoxy(24, 23);
	cout << "@ ���� ������ �ӽ÷� �߰��˴ϴ�!��";
	_getch();
	gotoxy(24, 23);
	cout << "                                           ";

	gotoxy(17, 23);
	cout << "�����ࢹ �����п��� �־��� ���� �̵����� ��!��";
	_getch();
	gotoxy(17, 23);
	cout << "                                                 ";

	gotoxy(17, 23);
	cout << "��� ������ ã�� ���������� ��� �ذ��غ�����!��";
	_getch();
	gotoxy(17, 23);
	cout << "                                                 ";

	gotoxy(24, 23);
	cout << "�������� ����� �׿����� �ִ�ϴ�.��";
	_getch();
	gotoxy(24, 23);
	cout << "                                                 ";

	mainScreen();
}

void showRecord(string player){
	system("cls");
	system("color 0E");
	cout << player;
}

void startGame(Player player){
	int width = 16;
	int height = width * 3 / 2;

	Map map(width, height);
	Ball mainBall;
	Bar mvBar;

	init(player, map, mvBar, mainBall);
	mainBall.setDirection(RIGHT_TOP);
	char nKey = 0;

	while (1)
	{
		if (_kbhit()){
			nKey = _getch();
			switch (nKey){
				// ��
			case 75:
				mvBar.moveLeft();
				break;
				// ��
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
		update(mainBall, map, player);
		render(mainBall, map, mvBar, player);
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

	string user;
	do{
		gotoxy(11, 5);
		cout << "                  ";
		gotoxy(11, 5);

		getline(cin, user);
		if (user.length() > 8){
			gotoxy(8, 7);
			cout << "�ִ� 8Byte";
		}
	} while (user.compare("") == 0 || user.length() > 8);

	setCursorType(NOCURSOR);
	if (type == 22){
		Player p(user, 0);
		startGame(p);
	}
	else if (type == 26)
		showRecord(user);

}

void setSelecter(int x, int y){
	int posX = x;
	int posY = y;

	gotoxy(posX, posY);

	printf("��");

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
			// ��
		case 72:
			if (posY > 22){
				gotoxy(posX, posY);
				printf("  ");
				posY -= 2;
				gotoxy(posX, posY);
				printf("��");
			}
			break;
			// ��
		case 80:
			if (posY < 26){
				gotoxy(posX, posY);
				printf("  ");
				posY += 2;
				gotoxy(posX, posY);
				printf("��");
			}
			break;

		}
	} while (input != 27 && input != 13);
}

void printB(int x, int y, char * symbol){
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


void init(Player & user, Map & map, Bar & bar, Ball & ball){
	system("cls");
	system("color 0F");
	system("mode con:cols=60 lines=30");

	setCursorType(NORMALCURSOR);

	bar.setBar(map.getWidth(), map.getHeight(), ORIGIN_BAR_LENGTH);
	ball.setBall(map.getWidth(), map.getHeight() - 2, INIT_LIFE, "��");

	int stage = 1;
	map.readMap(stage);
	map.drawMap();
	map.drawInfo(user.getName(), user.getScore());

	bar.drawBar();
	ball.drawBall();

}

void update(Ball & ball, Map & map, Player & player){
	ball.crushFrame();

	int blockType;
	int direction = ball.getDirection();
	if (direction >= TOP && direction <= LEFT_TOP){
		if (blockType = map.checkTop(ball.getDrawX(), ball.getDrawY())){
			ball.crushUpDown();
			player.increaseScore(blockType);
			return;
		}
		if (direction == RIGHT_TOP){
			if (blockType = map.checkRight(ball.getDrawX(), ball.getDrawY())){
				ball.crushSide();
				player.increaseScore(blockType);
				return;
			}
			else if (blockType = map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY())){
				ball.crushDiagonal();
				player.increaseScore(blockType);
				return;
			}
		}
		else if (direction == LEFT_TOP){
			if (blockType = map.checkLeft(ball.getDrawX(), ball.getDrawY())){
				ball.crushSide();
				player.increaseScore(blockType);
				return;
			}
			else if (blockType = map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY())){
				ball.crushDiagonal();
				player.increaseScore(blockType);
				return;
			}

		}
	}
	else if (direction >= DOWN && direction <= LEFT_DOWN){
		if (blockType = map.checkDown(ball.getDrawX(), ball.getDrawY())){
			ball.crushUpDown();
			player.increaseScore(blockType);
			return;
		}
		if (direction == LEFT_DOWN){
			if (blockType = map.checkLeft(ball.getDrawX(), ball.getDrawY())){
				ball.crushSide();
				player.increaseScore(blockType);
				return;
			}
			else if (blockType = map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY())){
				ball.crushDiagonal();
				player.increaseScore(blockType);
				return;
			}

		}
		else if (direction == RIGHT_DOWN){
			if (blockType = map.checkRight(ball.getDrawX(), ball.getDrawY())){
				ball.crushSide();
				player.increaseScore(blockType);
				return;
			}
			else if (blockType = map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY())){
				ball.crushDiagonal();
				player.increaseScore(blockType);
				return;
			}
		}
	}







	ball.moveBall();
	
	//DEBUGU
	//_getch();

}

void render(Ball & ball, Map & map, Bar & bar, Player & player){
	// �� ���
	//DEBUG
	//map.drawDebugingMap();
	
	// ���� ���
	map.drawInfo(player.getName(), player.getScore());


	// �� ���
	ball.removeBefore();
	ball.drawBall();

	// �� ���
	bar.drawBar();
}

void release(){

}
