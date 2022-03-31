#include "snake.h"
#include<Windows.h>

void gotoxy1(HANDLE hOut1, int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut1, pos);
}
HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);


Snake::Snake(Wall& tempWall,Food& tempFood):
	wall(tempWall),food(tempFood){
	pHead = nullptr;
	isRoop = false;
}

void Snake::initSnake(){
	destroyPoint();
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);
}

void Snake::destroyPoint(){
	Point* pCur = pHead;
	if (pHead != nullptr) {
		pCur = pHead->next;
		delete pHead;
		pHead = pCur;
	}
}

void Snake::addPoint(int x,int y){
	Point* newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	newPoint->next = nullptr;

	if (pHead != nullptr) {
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy1(hOut1, pHead->y * 2, pHead->x);
		cout << "=";
	}
	newPoint->next = pHead;
	pHead = newPoint;
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy1(hOut1, pHead->y * 2, pHead->x);
	cout << "@";
}

void Snake::deletePoint(){
	if (pHead == nullptr || pHead->next == nullptr) {
		return;
	}

	Point* pCur = pHead->next;
	Point* pPre = pHead;

	while (pCur->next != nullptr) {
		pPre = pPre->next;
		pCur = pCur->next;
	}
	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy1(hOut1, pCur->y * 2, pCur->x);
	cout << " ";

	delete pCur;
	pCur = nullptr;
	pPre->next = nullptr;
}

bool Snake::move(char key){
	int x = pHead->x;
	int y = pHead->y;

	switch (key) {
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	Point* pCur = pHead->next;
	Point* pPre = pHead;

	while (pCur->next != nullptr) {
		pPre = pPre->next;
		pCur = pCur->next;
	}
	if (pCur->x == x && pCur->y == y) {
		isRoop = true;
	}
	else {
		if(wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=') {
			addPoint(x, y);
			deletePoint();
			system("cls");
			wall.drawWall();
			cout << "µÃ·Ö:" << getScore() << "·Ö" << endl;
			cout << "Game Over!" << endl;
			return false;
		}
	}
	if (wall.getWall(x, y) == '#') {
		addPoint(x, y);
		food.setFood();
	}
	else {
		addPoint(x,y);
		deletePoint();
		if (isRoop) {
			wall.setWall(x, y, '@');
			gotoxy1(hOut1, y * 2, x);
			cout << "@";
		}
	}
	return true;
}

int Snake::getSleepTime(){
	int sleepTime = 0;
	int size = countList();
	size -= 3;
	if (size <= 5) {
		sleepTime = 300;
	}
	else if (size > 5 && size <= 8) {
		sleepTime = 200;
	}
	else {
		sleepTime = 100;
	}
	return sleepTime;
}

int Snake::countList(){
	int size = 0;
	Point* curPoint = pHead;
	while (curPoint != nullptr) {
		size++;
		curPoint = curPoint->next;
	}
	return size;
}

int Snake::getScore()
{
	int size = countList();
	size -= 3;
	int score;
	if (size <=5) {
		score = size * 100;
	}
	else if (size >5 && size <= 8) {
		score = 500 + (size - 5) * 200;
	}
	else {
		score = 1100 + (size - 8) * 300;
	}
	return score;
}
