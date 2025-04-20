#pragma once
#include <graphics.h>
#include "Animation.h"
#include "Bullet.h"
#include "Player.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	bool CheckBulletCollision(const Bullet& bullet);
	bool CheckPlayerCollision(const Bullet& bullet);
	void Move(const Player& player);
	void Draw(int delta);
	enum class SpawnEdge
	{
		Up = 0,
		Down,
		Left,
		Right
	};
private:
	const int SPEED = 2;
	static constexpr int FRAME_WIDTH = 80; // 玩家宽度
	static constexpr int FRAME_HEIGHT = 80; // 玩家高度
	static constexpr int SHADOW_WIDTH = 32; // 阴影宽度
	static constexpr int WINDOW_WIDTH = 1280;
	static constexpr int WINDOW_HEIGHT = 720;
private:
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	POINT position = { 0,0 };
	bool facing_left = false;
	int dir_x = 0;
	int dir_y = 0;
};

