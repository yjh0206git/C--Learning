#pragma once
#include<iostream>
#include"wall.h"
#include"food.h"
using namespace std;

class Snake {
public:
	Snake(Wall& tempWall,Food& tempFood);
	struct Point {
		int x, y;
		Point* next;
	};
	enum { 
		UP = 'w',DOWN = 's',
		LEFT = 'a',RIGHT = 'd'
	};
	void initSnake();
	void destroyPoint();
	void addPoint(int x,int y);
	void deletePoint();
	bool move(char key);
	int getSleepTime();
	int countList();
	int getScore();
private:
	Point* pHead;
	Wall& wall;
	Food& food;
	bool isRoop;
};