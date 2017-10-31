#include<iostream>
#include<Windows.h>
#include<fstream>

using namespace std;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void gotoxy(int x, int y);
void setcursortype(CURSOR_TYPE c);
void drawMap(int width, int height);
void drawFrame(int width, int height);

char *map = "555555555555555550000000000000055000000000000005500000000000000550000000000000055000000000000005500000000000000550000000000000055000000000000005500000000000000550000000000000055000000000000005500000000000000550000000000000055000000000000005500000000000000550000000000000055000000000000005500000000000000550000000000000055000000000000005500000000000000550000000000000055555555555555555";

int main(){
	setcursortype(NOCURSOR);







	int width = 16;
	int height = width * 3 / 2;
	drawFrame(width, height);
	drawMap(width, height);

	ifstream input("input.txt");
	if (input.fail()){
		cout << "파일을 여는 데 실패했습니다." << endl;
		return 1;
	}

	int arr[5];
	for (int i = 0; i<5; i++)
		input >> arr[i];
	for (int i = 0; i<5; i++){
		cout << "arr[" << i << "]: " << arr[i] << endl;
	}
	input.close();

}

void drawMap(int width, int height){

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			switch (map[i*width + j])
			{
			case '5':
				cout << "▩";
				break;
			case '0':
				cout << "  ";
				break;
			}

		}


		printf("\n");
	}
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
void gotoxy(int x, int y) // 좌표 이동 함수
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 직사각형을 그림
//void drawFrame(int width, int height)
//{
//	system("cls");
//	//
//	for (int i = 1; i < 12; i++)
//		b[i] = 0xa0 + i;
//	//
//	printf("%c%c", a1, b[3]);
//	for (int i = 0; i < x - 1; i++)
//		printf("%c%c", a1, b[8]);
//	printf("%c%c", a1, b[4]);
//	//
//	for (int i = 1; i <= y - 1; i++)
//	{
//		gotoxy(1, i + 1);
//		printf("%c%c", a1, b[7]);
//		for (int j = 0; j < x - 1; j++)
//			printf("%c%c", a1, b[11]);
//		printf("%c%c", a1, b[9]);
//	}
//	//
//	gotoxy(1, y + 1);
//	printf("%c%c", a1, b[6]);
//	for (int i = 0; i < x - 1; i++)
//		printf("%c%c", a1, b[10]);
//	printf("%c%c", a1, b[5]);
//
//	printf("\n");
//}
void setcursortype(CURSOR_TYPE c){ //커서 안보이게 하는 함수 
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