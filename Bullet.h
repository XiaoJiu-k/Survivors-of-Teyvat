#pragma once
#include <windef.h>
#include <graphics.h>
class Bullet
{
public:
	POINT position = { 0,0 };
public:
	Bullet();
	~Bullet();

	void Draw();
private:
	const int RADIUS = 10;
};

