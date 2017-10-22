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
void render(Ball & ball);
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
	
	init(user,map, mvBar, mainBall);

	//DEBUG

	//system("cls");
	//for (int i = 0; i < map.getHeight(); i++){
	//	for (int j = 0; j < map.getWidth(); j++){
	//		cout << map.getCoodrInfo(i, j) << " ";
	//	}
	//	cout << endl;
	//}

	// 
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
		update(mainBall, map);
		render(mainBall);
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

	setCursorType(SOLIDCURSOR);
	
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
	if (type == 22)
		startGame(user);
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
	//int x = 15;
	//int y = 4;
	//char * test = "��";
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
	ball.setBall(map.getWidth(), map.getHeight() - 2, INIT_LIFE, "��");

	int stage = 1;
	map.readMap(stage);
	map.drawMap();
	map.drawInfo(user, 100);

	bar.drawBar();
	ball.drawBall();

}
void update(Ball & ball, Map & map){
	// �� ��ġ ������Ʈ

	_getch();
	gotoxy(map.getWidth()*2 + 10, 16);

	cout <<"���� �� : "<< ball.getX() << "/" << ball.getY() <<"     " << endl;
	gotoxy(map.getWidth()*2 + 10, 17);

	cout << "���� �� : "<<ball.getNextX() << "/" << ball.getNextY() <<"   "<< endl;

	//int val = map.getCoodrInfo(ball.getNextX()/2, ball.getNextY());
	
	int val = map.getCoodrInfo(ball.getY()-1 , ball.getX()/2+1);
	gotoxy(map.getWidth() * 2 + 10, 18);

	cout << "(" << ball.getX() / 2 +1 << ", " << ball.getY()-1 << " )" << val << "        ";
	gotoxy(map.getWidth() * 2 + 10, 19);
	cout << "�迭 ������ " << map.getHeight() << " * " << map.getWidth();



	gotoxy(map.getWidth() * 2 + 10, 20);
	
	if (ball.getNextX() != 0 && ball.getNextY() != 0){
		if (val == 1 || val == 2){
			//DELETE BLOCK

			cout << "DELETE";
		}
		else if (val == 3){
			//NOTE : DROP THE ITEM
			cout << "DROPIT";
		}
		else if (val == 4 || val == 5 || val == 6){
			//NOTE : BLOCK SETTING		
			cout << "BLOCKS";

		}
	}
	
	ball.moveBall();
	
}

void render(Ball & ball){
	// �� ���
	ball.removeBefore();
	ball.drawBall();
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
