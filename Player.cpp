#include "Player.h"
#include <iostream>
#include "Animation.h"
#include "putimage_alpha.h"

Player::Player()
{
	loadimage(&img_shadow, _T("img/shadow_player.png"));
	//anim_left = new Animation(_T("img/player_left_%d.png"), 6, 45);
	//anim_right = new Animation(_T("img/player_left_%d.png"), 6, 45);
	anim_left = new Animation(_T("img/player_left_%d.png"), PLAYER_ANIM_NUM, 45);
	anim_right = new Animation(_T("img/player_right_%d.png"), PLAYER_ANIM_NUM, 45);

}

Player::~Player()
{
	delete anim_left;
	delete anim_right;
}

void Player::ProcessEvent(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN) {
		switch (msg.vkcode)
		{
		case VK_UP:
			is_move_up = true;
			break;
		case VK_DOWN:
			is_move_down = true;
			break;
		case VK_LEFT:
			is_move_left = true;
			break;
		case VK_RIGHT:
			is_move_right = true;
			break;
		}
	}
	else if (msg.message == WM_KEYUP) {
		switch (msg.vkcode)
		{
		case VK_UP:
			is_move_up = false;
			break;
		case VK_DOWN:
			is_move_down = false;
			break;
		case VK_LEFT:
			is_move_left = false;
			break;
		case VK_RIGHT:
			is_move_right = false;
			break;
		}
	}
	dir_x = is_move_right - is_move_left;
	dir_y = is_move_down - is_move_up;
}
/**
 * 人物移动.
 * 
 */
void Player::move()
{

	double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (len_dir != 0)
	{
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		player_pos.x += (int)(PLAYER_SPEED * normalized_x);
		player_pos.y += (int)(PLAYER_SPEED * normalized_y);
	}

	//边界
	if (player_pos.x < 0) player_pos.x = 0;
	if (player_pos.y < 0) player_pos.y = 0;
	if (player_pos.x + PLAYER_WIDTH > WINDOW_WIDTH) player_pos.x = WINDOW_WIDTH - PLAYER_WIDTH;
	if (player_pos.y + PLAYER_HEIGHT > WINDOW_HEIGHT) player_pos.y = WINDOW_HEIGHT - PLAYER_HEIGHT;
}

void Player::Draw(int delta)
{
	int pos_shadow_x = player_pos.x + (PLAYER_HEIGHT / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = player_pos.y + PLAYER_HEIGHT - 8;
	//putimage_alpha(player_pos.x, player_pos.y, &img_player_left[idx_current_anim]);
	putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

	static bool facing_left = false;
	if (dir_x < 0)
		facing_left = true;
	else if (dir_x > 0)
		facing_left = false;

	if (facing_left)
		anim_left->Play(player_pos.x, player_pos.y, delta);
	else
		anim_right->Play(player_pos.x, player_pos.y, delta);
}

const POINT& Player::GetPosition() const
{
	// TODO: 在此处插入 return 语句
	return player_pos;
}
