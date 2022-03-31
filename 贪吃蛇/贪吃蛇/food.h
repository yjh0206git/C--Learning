#pragma once
#include<iostream>
#include"wall.h"
using namespace std;

class Food {
public:
	Food(Wall& tempWall);
	void setFood();
private:
	int foodX;
	int foodY;
	Wall& wall;
};