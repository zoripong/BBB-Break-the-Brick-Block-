#include<iostream>
#include <fstream>
#include<conio.h>
#include<Windows.h>
#include <string>
#include<time.h>
#include <list>

#include <mmsystem.h>    
#pragma comment(lib,"winmm.lib") 

#include "Bar.h"
#include "Map.h"
#include "Ball.h"
#include "Player.h"
#include "Item.h"
#include<MMSystem.h> // 배경음악 때문에 사용

#pragma comment(lib,"Winmm.lib") // 배경음악


using namespace std;

const int ORIGIN_BAR_LENGTH = 5;
const int INIT_LIFE = 3;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;


void gotoxy(int x, int y);
void setCursorType(CURSOR_TYPE c);

void mainScreen();
void explainScreen();
void showRecord(string player); // TODO
int showMapList();
void startGame(Player player, int stage);
void inputInfo(int type);
void setSelecter(int x, int y);
void printB(int x, int y, char * symbol);
void init(Player & user, Map & map, Bar & bar, Ball & ball);
void update(Ball & ball, Map & map, Bar & bar, Player & player);
void render(Ball & ball, Map & map, Bar & bar, Player & player);
void release(Player & player, int stage);
void itemProcess(int type, Ball & ball, Map & map);
void endGame();
void checkRecord(string user);
list<string> str_split(string str);

void showRecord(Player & player);
list<Player> readWriteFile(Player & player, int stage);
void showRanking(list<Player> & players);

void drawInitial();
list<Item> items;


void showColor(){
	for (int colour = 0x00; colour <= 0xff; colour++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
		cout << "Using colour:" << colour << endl;
		cin.get();
	}

}
int main(){
	//sndPlaySound("background.wav", SND_ASYNC | SND_LOOP);

	//showColor();
	//inputInfo(22);

	srand((unsigned int)time(NULL));

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
	cout << endl;
	cout << endl;
	cout << endl;

	printf("2619 HYR");
	
	setSelecter(50, 22);

}

void explainScreen(){
	system("cls");
	system("color 0E");

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
 
void showRecord(string player){
	system("cls");
	system("color 0E");
	cout << player;
}

void startGame(Player player, int stage){
	int width = 16;
	int height = width * 3 / 2;

	Map map(stage, width, height);
	Ball mainBall;
	Bar mvBar;

	init(player, map, mvBar, mainBall);
	mainBall.setDirection(TOP);
	char nKey = 0;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	gotoxy(map.getWidth() * 2 + 7, 14);
	cout << "   ↖   ↑   ↗    │";
	gotoxy(map.getWidth() * 2 + 7, 15);
	cout << "   q    w   e";
	gotoxy(map.getWidth() * 2 + 7, 16);
	cout << "  START : [space]";
	
	gotoxy(map.getWidth() * 2 + 7, 18);
	cout << " 방향을 선택하고";
	gotoxy(map.getWidth() * 2 + 7, 19);
	cout << "스페이스바를 꾸욱!";
	gotoxy(map.getWidth() * 2 + 7, 20);
	cout << "    미 선택 시";
	gotoxy(map.getWidth() * 2 + 7, 21);
	cout << " 자동 출발합니다.";


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	map.drawRect(map.getWidth() * 2 + 5, 12, 12, 12);
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 95);

	gotoxy(map.getWidth() * 2 + 11, 12);
	cout << " key 안내";

	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(0, 0);


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
		
		Sleep(75);
		update(mainBall, map, mvBar, player);
		render(mainBall, map, mvBar, player);

		if (mainBall.getLife() == 0){
			break;
		}
	}
	
	release(player, stage);
}

void inputInfo(int type){
	system("cls");
	setCursorType(NORMALCURSOR);
	system("color 70");
	system("mode con:cols=24 lines=12");

	gotoxy(6, 5);
	printf("ID :");

	gotoxy(6, 7); 
	printf("PW :");

	gotoxy(5, 10);
	printf("Press the Enter");

	string user;
	string password;
	do{ 
		gotoxy(11, 5);
		cout << "                  ";
		gotoxy(11, 5);
		
		getline(cin, user);
		if (user.length() > 8){
			gotoxy(8, 9);
			cout << "최대 8Byte";
		}
	} while (user.compare("") == 0 || user.length() > 8);


	do{
		gotoxy(11, 7);
		cout << "                  ";
		gotoxy(11, 7);
		getline(cin, password);
		if (password.length() > 8){
			gotoxy(8, 9);
			cout << "최대 8Byte";
		}
	} while (password.compare("") == 0 || password.length() > 8);


	setCursorType(NOCURSOR);
	if (type == 22){
		Player p(user,password, 0);
		startGame(p, showMapList());
	}
	else if (type == 26){
		checkRecord(user);
		mainScreen();
	}


}

int showMapList(){
	setCursorType(NOCURSOR);

	system("cls");
	system("color 0F");
	system("mode con:cols=32 lines=26");


	int width = 16;
	int height = width * 3 / 2;

	Map map(0, width, height);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	map.readMap();
	map.drawMap();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

	gotoxy(14, 18);
	cout << "STAGE " << map.getStage() + 1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

	gotoxy(11, 20);
	cout << "Select Stage," ;
	gotoxy(9, 21);
	cout << "Press the Enter!";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	gotoxy(29, 23);
	cout << "→";

	_getch();
	
	int key;
	while (1){

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

		key = _getch();
		if (key == 32 || key == 13)
			break;

		if (key == 77)
			map.showNextStage();
		else if (key == 75)
			map.showPreviousStage();

		if (map.getStage() != 0){
			gotoxy(3, 23);
			cout << "←";
		}
		if (map.getStage() != 14){
			gotoxy(29, 23);
			cout << "→";
		}


		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);

		gotoxy(14, 18);
		cout << "STAGE " << map.getStage()+1;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);

		gotoxy(11, 20);
		cout << "Select Stage,";
		gotoxy(9, 21);
		cout << "Press the Enter!";


	}

	system("cls");
	system("mode con:cols=60 lines=30");

	gotoxy(25, 15);
	cout << "Are You Ready?";
	
	for (int i = 0; i < 5; i++){
		system("color 0F");
		Sleep(200);
		system("color 9F");
		Sleep(200);
	}


	
	system("cls");
	system("color 3F");
	gotoxy(27, 15);
	cout << "Game Start!";
	Sleep(1500);
	return map.getStage();
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

	bar.setBar(map.getWidth(), map.getHeight(), ORIGIN_BAR_LENGTH);
	ball.setBall(map.getWidth(), map.getHeight() - 2, INIT_LIFE, "○", map.getWidth(), map.getHeight());

	map.readMap();
	map.drawMap();

	int * block = map.getBlock();
	user.setScore(block[1] * 100 + block[4] * 50 + block[6] * 30);

	map.drawInfo(user.getName(), user.getScore(), ball.getLife());

	bar.drawBar();
	ball.drawBall();
	

}

void update(Ball & ball, Map & map, Bar & bar, Player & player){

	int blockType;
	int direction = ball.getDirection();
	if (direction >= TOP && direction <= LEFT_TOP){
		if (blockType = map.checkTop(ball.getDrawX(), ball.getDrawY())){
			ball.crushUpDown();
			player.increaseScore(blockType);
			if (blockType == 6){

			Item item(rand() % 4, ball.getDrawX(), ball.getDrawY()-2);
			items.push_back(item);
			}

			return;
		}

		if (direction == RIGHT_TOP){
			if (blockType = map.checkRight(ball.getDrawX(), ball.getDrawY())){
				ball.crushSide();
				player.increaseScore(blockType);
				if (blockType == 6){

					Item item(rand() % 4, ball.getDrawX() + 2, ball.getDrawY() - 1);
					items.push_back(item);	
				}
				return;
			}
			else if (blockType = map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY())){
				ball.crushDiagonal();
				player.increaseScore(blockType);
				if (blockType == 6){

					Item item(rand() % 4, ball.getDrawX() + 2, ball.getDrawY() - 2);
					items.push_back(item);
				}
				return;
			}
		}
		else if (direction == LEFT_TOP){
			if (blockType = map.checkLeft(ball.getDrawX(), ball.getDrawY())){
				ball.crushSide();
				player.increaseScore(blockType);
				if (blockType == 6){
					Item item(rand() % 4, ball.getDrawX() - 2, ball.getDrawY() - 1);
					items.push_back(item);
				}
				return;
			}
			else if (blockType = map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY())){
				ball.crushDiagonal();
				player.increaseScore(blockType);
				if (blockType == 6){

					Item item(rand() % 4, ball.getDrawX() - 2, ball.getDrawY() - 2);
					items.push_back(item);
				}
				return;
			}

		}
	}
	else if (direction >= DOWN && direction <= LEFT_DOWN){
		if (blockType = map.checkDown(ball.getDrawX(), ball.getDrawY())){
			ball.crushUpDown();
			player.increaseScore(blockType);
			if (blockType == 6){

				Item item(rand() % 4, ball.getDrawX(), ball.getDrawY());
				items.push_back(item);
			}
			return;
		}
		if (direction == LEFT_DOWN){
			if (blockType = map.checkLeft(ball.getDrawX(), ball.getDrawY())){
				ball.crushSide();
					player.increaseScore(blockType);
					if (blockType == 6){
						Item item(rand() % 4, ball.getDrawX() - 2, ball.getDrawY() + 1);
						items.push_back(item);
					}
				return;
			}
			else if (blockType = map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY())){
				ball.crushDiagonal();
					player.increaseScore(blockType);
				if (blockType == 6){
					Item item(rand() % 4, ball.getDrawX() - 2, ball.getDrawY());
					items.push_back(item);
				}
				return;
			}

		}
		else if (direction == RIGHT_DOWN){
			if (blockType = map.checkRight(ball.getDrawX(), ball.getDrawY())){
				ball.crushSide();
				player.increaseScore(blockType);
				if (blockType == 6){

					Item item(rand() % 4, ball.getDrawX() + 2, ball.getDrawY() + 1);
					items.push_back(item);

				}
				return;
			}
			else if (blockType = map.checkDiagonal(direction, ball.getDrawX(), ball.getDrawY())){
				ball.crushDiagonal();
				player.increaseScore(blockType);
				if (blockType == 6){
					Item item(rand() % 4, ball.getDrawX() + 2, ball.getDrawY());
					items.push_back(item);
				}
				return;
			}
		}
	}

	int barCrushX = bar.crushBar(ball.getDrawX(), ball.getDrawY());
	clock_t start, end;
	start = clock();
	
	// 여기..!
	if (barCrushX != -1){
		ball.crushBar();
		end = clock();
		char ch;
		int beforeX = -1, beforeY = -1;
		
		while (1){

			list<Item>::iterator i = items.begin();
			while (i != items.end())
			{

				(*i).down(map, ball);
				(*i).removeBefore();
				

				// 3:32 여기다여기

				(*i).drawItem(map, ball);
				bar.drawBar();
				ball.drawBall();

				int valid = bar.checkX((*i).getPosX());
				if (valid != 1)
					Sleep(1000);
				int max = map.getHeight() - 2;
				if (valid)
					max = map.getHeight() - 3;

				if ((*i).getPosY() > max)
				{
					int type = (*i).removeIt();
					ball.drawBall();
					if (valid){
					itemProcess(type, ball, map);
					player.increaseScore(7);
					}

					items.erase(i++);  // alternatively, i = items.erase(i);
				}
				else
				{
					++i;
				}
			}
			if (((double)(end - start) / CLK_TCK) >= 2){
				int *posBar = bar.getPositionX();
				gotoxy(posBar[0], beforeY);
				for (int i = 0; i < bar.getLength(); i++)
					cout << "  ";

			
				break;
			}
			
			end = clock();


			if (_kbhit()){
				ch = _getch();
				if (beforeX != -1 && beforeY != -1){
					int *posBar = bar.getPositionX();
					gotoxy(posBar[0], beforeY);
					for (int i = 0; i < bar.getLength(); i++)
						cout << "  ";
				}
				beforeY = ball.getDrawY() - 1;

				if (ch == 'q' || ch == 'Q'){
					start = clock();

					beforeX = ball.getDrawX() - 2;
					gotoxy(beforeX, beforeY);
					cout << "↖";
					ball.setDirection(LEFT_TOP);

				}
				else if (ch == 'e' || ch == 'E'){
					start = clock();

					beforeX = ball.getDrawX() + 2;
					gotoxy(beforeX, beforeY);
					cout << "↗";
					ball.setDirection(RIGHT_TOP);
				}
				else if (ch == 'w' || ch == 'W'){
					start = clock();

					beforeX = ball.getDrawX();
					gotoxy(beforeX, beforeY);
					cout << "↑";
					ball.setDirection(TOP);

				}
				else if (ch == 75){
					// left
					bar.moveLeft();
					bar.removeBeforeX();

					bar.drawBar();
					ball.moveLeft(barCrushX);
					ball.drawBall();

				}
				else if (ch == 77){
					// right
					bar.moveRight();
					bar.removeBeforeX();
					bar.drawBar();
					ball.moveRight(barCrushX, map.getWidth());
					ball.drawBall();
				}

				if (ch == 32)
					break;
			}


		}
	}

	list<Item>::iterator i = items.begin();
	while (i != items.end()){
		(*i).down(map, ball);
		(*i).removeBefore();
		(*i).drawItem(map, ball);
		bar.drawBar();
		ball.drawBall();
		if ((*i).getPosY() > map.getHeight() - 2){
			int type = (*i).removeIt();
			ball.drawBall();
			itemProcess(type, ball, map);
			player.increaseScore(7);
			items.erase(i++);  // alternatively, i = items.erase(i);
		}else{
			++i;
		}
	}

	int val = ball.crushFrame();

	if (val != -1){
		map.drawInfo(player.getName(), player.getScore(), ball.getLife());
		ball.ballInit(map.getWidth(), map.getHeight());
		bar.barInit(map.getWidth(), map.getHeight());
		ball.drawBall();
		bar.drawBar();
		if (ball.getLife() != 0)
			_getch();
	}
	
	ball.moveBall();

	//DEBUGU
	//_getch();

}

void render(Ball & ball, Map & map, Bar & bar, Player & player){
	// 맵 출력
	//DEBUG
	//map.drawDebugingMap();
	
	// 스테이지 전환
	if (map.getTreasureCount() == 0){
		ball.setLife(0);
	}

	// 정보 출력
	map.drawInfo(player.getName(), player.getScore(), ball.getLife());

	// 공 출력
	ball.removeBefore();
	ball.drawBall();
	
	// 바 출력
	bar.drawBar();
}

void release(Player & player, int stage){
	system("cls");
	system("mode con:cols=60 lines=15");

	showRecord(player);
	list<Player> players = readWriteFile(player, stage);

	system("cls");
	gotoxy(25, 8);
	cout << "☆★빠밤★☆";
	system("color 05");
	Sleep(250);
	system("color 50");
	Sleep(250);
	system("color 05");
	Sleep(250);
	system("color 50");
	Sleep(250);
	system("color 05");
	Sleep(250);
	system("color 50");
	Sleep(250);

	showRanking(players);
	mainScreen();
}

void itemProcess(int type, Ball & ball, Map & map){
	switch (type){
	case 0:
	case 1:
		map.randomBomb();
		break;
	case 2:
	case 3:
		if (rand() % 2 == 0){
			int flag = rand() % 3 + 1;
			ball.setLife(ball.getLife() + flag);
		}else{
			ball.setLife(ball.getLife() - 1);
		}
		break;
	}

}

void showRecord(Player & player){
	system("cls");

	gotoxy(5, 4);
	for (int i = 0; i < 50; i++){
		cout << "$";
	}
	gotoxy(18, 7);
	cout << "☆★"<< player.getName() <<"의 최종 기록 ★☆";
	gotoxy(28, 9);

	cout << player.getScore() << "점";
	gotoxy(5, 12);

	for (int i = 0; i < 50; i++){
		cout << "$";
	}

	cout << endl;
	cout << endl;
	cout << endl;
	cout << "2619 HYR";

	_getch();
}

list<Player> readWriteFile(Player & player, int stage){
	system("cls");

	string fileName[15] = {
		"stage_1.txt", "stage_2.txt", "stage_3.txt", "stage_4.txt", "stage_5.txt",
		"stage_6.txt", "stage_7.txt", "stage_8.txt", "stage_9.txt", "stage_10.txt",
		"stage_11.txt", "stage_12.txt", "stage_13.txt", "stage_14.txt", "stage_15.txt"
	};
	string filePath = "ranking/stage/"+fileName[stage];
	//Player * player;
	list<Player> players;
	ifstream input(filePath);
	if (input.fail()){
		cout << "파일을 여는 데 실패했습니다." << endl;

	}
	string name;
	string score;
	int flag = 1;
	int cnt = 0;
	getline(input, name);

	while (!input.eof()){

		getline(input, name);
		/*if (cnt == 0)
		continue;*/
		getline(input, score);
		int iScore = atoi(score.c_str());
		cout << iScore;
		if (flag == 1 && iScore < player.getScore()){
			flag = 0;
			players.push_back(player);
		}
		list<string> list = str_split(name);
	
		string id = list.front();
		list.pop_front();
		string pw = list.front();
		cout << id << "_" << pw;
		_getch();
		Player player(id, pw, iScore);
		players.push_back(player);
	}
	if (flag == 1){
		players.push_back(player);
	}

	input.close();


	// 파일 입력 (쓰기)
	ofstream outFile(filePath);

	list<Player>::iterator i = players.begin();
	while (i != players.end())
	{
		outFile << endl;
		outFile << (*i).getName();
		outFile << endl;
		outFile << (*i).getScore();
		i++;
	}
	outFile.close();

	return players;
}

void showRanking(list<Player> & players){

	system("mode con:cols=60 lines=15");
	system("color 0F");
	system("cls");

	if (players.size() >= 5){

	gotoxy(5, 2);
	for (int i = 0; i < 50; i++){
		cout << "$";
	}
	cout << endl;

	list<Player>::iterator i = players.begin();
	for (int j = 0; j < 5; j++){
		gotoxy(25, 3+j);
		cout << (*i).getName() << " / " << (*i).getScore() << endl;
		i++;
	}
	
	gotoxy(5, 8);
	for (int i = 0; i < 50; i++){
		cout << "$";
	}

	players.reverse();
	i = players.begin();
	for (int j = 0; j < 5; j++){
		gotoxy(25, 9+j);
		cout << (*i).getName() << " / " << (*i).getScore() << endl;
		i++;
	}
	cout << endl;

	gotoxy(5, 14);
	for (int i = 0; i < 50; i++){
		cout << "$";
	}
	cout << endl;
	cout << "2619 HYR";

	gotoxy(23, 2);
	cout << " 명예의 전당 ";
	gotoxy(23, 8);
	cout << " 불명예의 전당 ";
	}
	else if (players.size() == 0){
		system("cls");
		return;
	}
	else{

		int y = 2;
		gotoxy(5, y);
		y++;
		for (int i = 0; i < 50; i++){
			cout << "$";
		}
		list<Player>::iterator i = players.begin();
		for (int j = 0; j < players.size(); j++){
			gotoxy(25, y++);
			cout << (*i).getName() << " / " << (*i).getScore() << endl;
			i++;
		}
		y++;
		gotoxy(5, y);
		for (int i = 0; i < 50; i++){
			cout << "$";
		}
	
	}




	while (1){
		int ch = _getch();
		if (ch == 13)
			break;
	}
}



void drawInitial(){
	gotoxy(0, 0);
	cout << "2619 HYR";
}

void checkRecord(string user){
	system("mode con:cols=60 lines=15");
	system("color 0F");
	system("cls");

	string filePath = "rank.txt";
	list<Player> players;
	ifstream input(filePath);
	if (input.fail()){
		cout << "파일을 여는 데 실패했습니다." << endl;

	}
	string name;
	string score;
	getline(input, name);

	while (!input.eof()){
		getline(input, name);
		if (name != user)
			continue;

		getline(input, score);
		
	
		int iScore = atoi(score.c_str());
	
		list<string> list = str_split(name);

		string id = list.front();
		list.pop_front();
		string pw = list.front();

		Player player(id, pw, iScore);
		players.push_back(player);
	}

	input.close();

	gotoxy(19, 2);
	cout << user << "의 상위 5개 기록 확인";

	int y = 4;
	gotoxy(5, y);
	for (int i = 0; i < 50; i++){
		cout << "$";
	}
	y++;
	int flag = 0;
	list<Player>::iterator i = players.begin();
	while (i != players.end())
	{
		y++;
		gotoxy(25, y);
		cout << (flag+1) << "위 - " << (*i).getScore() << endl;
		i++;
		flag++;
		if (flag > 5)
			break;
	}
	if (flag == 0)
	{
		gotoxy(25, ++y);
		cout << "기록이 없습니다." << endl;
	}
	
	gotoxy(5, y+2);

	for (int i = 0; i < 50; i++){
		cout << "$";
	}

	_getch();

}


list<string> str_split(string str){
	list<string> strlist;
	string::iterator tempit = str.begin();
	int hd, tl;
	bool goodword = true;
	for (string::iterator it = str.begin(); it != str.end(); it++){
		// 맨처음 _나 -가 나오는 경우
		if (it == str.begin() && (*it == '-' || *it == '_' || *it == '/' || *it == '.'))
		{
			tempit++;
			goodword = false;
		}// 중간에 -나 _가 나오는 경우
		else if (*it == '-' || *it == '_' || *it == '/' || *it == '.'){
			if (it != str.end() - 1){
				hd = distance(str.begin(), tempit);
				tl = distance(tempit, it);
				if (str.substr(hd, tl).length() > 0)
				{
					strlist.push_back(str.substr(hd, tl));
				}
				tempit = it + 1;
				goodword = false;

			}// 마지막에 나옴
			else{
				hd = distance(str.begin(), tempit);
				tl = distance(tempit, it);
				strlist.push_back(str.substr(hd, tl));
				goodword = false;
			}
		}//마지막에 특수문자가 안나오는 경우에는 for문을 끝내기전 남은 단어 추가
		else if (it == str.end() - 1 && !goodword){
			hd = distance(str.begin(), tempit);
			tl = distance(tempit, it + 1);
			strlist.push_back(str.substr(hd, tl));
		}
	}
	if (goodword == true && str.length() > 0){
		strlist.push_back(str);
	}
	
	return strlist;
}