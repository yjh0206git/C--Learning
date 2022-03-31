#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
using namespace std;
#include"wall.h"
#include"snake.h"
#include"food.h"

void gotoxy(HANDLE hOut, int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
	srand((unsigned int)time(NULL));
	bool isDead = false;
	char preKey = NULL;

	Wall wall;
	wall.initWall();
	wall.drawWall();

	Food food(wall);
	food.setFood();

	Snake snake(wall,food);
	snake.initSnake();

	gotoxy(hOut, 0, Wall::ROW);
	cout << "得分:" << snake.getScore() << "分" << endl;

	while (!isDead) {
		char key = _getch();
		if (preKey==NULL&&key == snake.LEFT) {
			continue;
		}
		do {
			if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT) {
				if ((key == snake.LEFT && preKey == snake.RIGHT) ||
					(key == snake.RIGHT && preKey == snake.LEFT) ||
					(key == snake.UP && preKey == snake.DOWN) ||
					(key == snake.DOWN && preKey == snake.UP)) {
					key = preKey;
				}
				else {
					preKey = key;
				}
				if (snake.move(key)) {
					//system("cls");
					//wall.drawWall();
					gotoxy(hOut, 0, Wall::ROW);
					cout << "得分:" << snake.getScore() << "分" << endl;
					Sleep(snake.getSleepTime());
				}
				else {
					isDead = true;
					break;
				}
			}
			else {
				key = preKey; //强制把按键变为上一次按键
			}
		} while (!_kbhit());
	}
	system("pause");
	return EXIT_SUCCESS;
}