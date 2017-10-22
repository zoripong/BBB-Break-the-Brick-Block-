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
	printf("��");
	for (int i = 0; i < barLength - 2; i++)
		printf("��");
	printf("��");

	printBall(width / 2 + barLength + 3, height - 2, "��");
}

void drawFrame(int width, int height){
	system("cls"); 

	cout << "��";
	for (int i = 0; i < width - 2; i++)
		cout << "��";
	cout << "��";
	//
	for (int i = 1; i <= height - 1; i++)
	{
		gotoxy(1, i + 1);
		cout << "��";
		for (int j = 0; j < width - 2; j++)
			cout << "  ";
		cout << "��";
	}
	//
	gotoxy(1, height + 1);
	cout << "��";

	for (int i = 0; i < width - 2; i++)
		cout << "��";
	cout << "��";

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
	// �� ��ġ ������Ʈ
}

void render(){
	// �� ���
	// move bar ���
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
	//		szChoice = _getch();   //�Է°� �ϳ��� �����´�. �� �Լ��� ������ ���ѷ����� ������ �ȴ�.
	//		switch (szChoice)   //���ڰ��� �Է��� ������
	//		{
	//		case 'a':   //a�� ������ ��µǰ�
	//			cout << "a ������!!" << endl;
	//			break;

	//		default:   //a�� �ƴ� ���� ������ ��µȴ�.
	//			cout << "I don't know!!" << endl;
	//			break;

	//		}
	//	}
	//	cout << "Ű���尡 �� ������ ���� ��µǿ�!" << endl;
	//	Sleep(300);
	//	system("cls");
	//}


	char nKey = 0;

	while (1)
	{
		if (_kbhit()){
			nKey = _getch();
			switch(nKey){
			// ��
			case 75:
				cout << "left" << endl;
				break;
			// ��
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
		////cout << "�̵�" << endl;
	}
	release();
	return 0;
}