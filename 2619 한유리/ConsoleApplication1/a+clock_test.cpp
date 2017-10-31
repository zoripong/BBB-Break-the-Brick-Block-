#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>

using namespace std;

const int ORIGIN_BAR_LENGTH = 5;

int g_nFrameCount;
void printBall(int x, int y, char * symbol);

typedef enum DIRECTION{
	TOP = 0, RIGHT_TOP, RIGHT_DOWN, DOWN, LEFT_DOWN, LEFT_TOP
}DIRECTION;

typedef struct BALL{
	int isMoving;
	int life;
	int posX, posY;
	DIRECTION direction;

	//clock_t moveTime;
	//clock_t oldTime;
}BALL;

typedef struct bar{
	int width;
	int height;
}BAR;
// control the coord
void gotoxy(int x, int y){
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setMoveBar(int width, int height, int barLength){
	gotoxy(width / 2 + barLength -1, height - 1);

	BAR bar;
	bar.width = barLength;
	printf("◁");
	for (int i = 0; i < barLength - 2; i++)
		printf("□");
	printf("▷");

	printBall(width / 2 + barLength + 3, height - 2, "○");
}

void drawFrame(int width, int height){
	system("cls"); 

	cout << "▩";
	for (int i = 0; i < width - 2; i++)
		cout << "▩";
	cout << "▩";
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

void printBall(int x, int y, char * symbol){
	gotoxy(x, y);
	cout << symbol;
}
void init(){
	//cout << user;
	int width = 16;
	int height = 16 * 3 / 2;

	drawFrame(width, height);
}

void update(){
	// 공 위치 업데이트
}

void render(){
	// 공 출력
	// move bar 출력
}

void release(){

}

int main(){
	clock_t CurTime, OldTime;
	init();

	OldTime = clock();


	//char szChoice = 0;
	//while (1){
	//	if (_kbhit()){
	//		szChoice = _getch();   //입력값 하나를 가져온다. 이 함수가 없으면 무한루프에 빠지게 된다.
	//		switch (szChoice)   //문자값을 입력을 받으면
	//		{
	//		case 'a':   //a가 눌리면 출력되고
	//			cout << "a 눌렀다!!" << endl;
	//			break;

	//		default:   //a가 아닌 값이 눌리면 출력된다.
	//			cout << "I don't know!!" << endl;
	//			break;

	//		}
	//	}
	//	cout << "키보드가 안 눌려도 저는 출력되요!" << endl;
	//	Sleep(300);
	//	system("cls");
	//}


	char nKey = 0;

	while (1)
	{
		if (_kbhit()){
			nKey = _getch();
			switch(nKey){
			// ←
			case 75:
				cout << "left" << endl;
				break;
			// →
			case 77:
				cout << "right" << endl;
				break;
			// SPACE
			case 32:
				break;

			}
		}
		
		
		update();
		render();

		//while (1){
		//	CurTime = clock();
		//	if (CurTime - OldTime > 3300){
		//		OldTime = CurTime;
		//		break;
		//	}
		//}
		//g_nFrameCount++;
		////cout << "이동" << endl;
	}
	release();
	return 0;
}