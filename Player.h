#pragma once

#include <graphics.h>
#include "Animation.h"

class Player
{
public:

	Player();
	~Player();
	void ProcessEvent(const ExMessage& msg);
	void move();
	void Draw(int delta);
	const POINT& GetPosition() const;

	

public:
	static constexpr int PLAYER_SPEED = 3; // 玩家速度
	static constexpr int PLAYER_WIDTH = 80; // 玩家宽度
	static constexpr int PLAYER_HEIGHT = 80; // 玩家高度
	static constexpr int SHADOW_WIDTH = 32; // 阴影宽度
	static constexpr int PLAYER_ANIM_NUM = 6;
	static constexpr int WINDOW_WIDTH = 1280;
	static constexpr int WINDOW_HEIGHT = 720;

private:
	POINT player_pos = { 500,500 };
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;
	int dir_x = 0;
	int dir_y = 0;
	//int dir_x = is_move_right - is_move_left;
	//int dir_y = is_move_down - is_move_up;
	//int idx_current_anim = 0;
	/*IMAGE img_player_left[PLAYER_ANIM_NUM];
	IMAGE img_player_right[PLAYER_ANIM_NUM];*/
};

