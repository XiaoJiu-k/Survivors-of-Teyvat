#include "Enemy.h"
#include "putimage_alpha.h"
#include <string>
#include "Atlas.h"
#include "globals.h"
Enemy::Enemy()
{
	loadimage(&img_shadow, _T("img/shadow_enemy.png"));
	anim_left = new Animation(atlas_enemy_left,45);
	anim_right = new Animation(atlas_enemy_right,45);

	//让敌人随机生成在边界
	SpawnEdge edge = (SpawnEdge)(rand() % 4);
	switch (edge)
	{
	case Enemy::SpawnEdge::Up:
		position.x = rand() % WINDOW_WIDTH;
		position.y = -FRAME_HEIGHT;
		break;
	case Enemy::SpawnEdge::Down:
		position.x = rand() % WINDOW_WIDTH;
		position.y = FRAME_HEIGHT;
		break;
	case Enemy::SpawnEdge::Left:
		position.x = -FRAME_WIDTH;
		position.y = rand() % WINDOW_WIDTH;
		break;
	case Enemy::SpawnEdge::Right:
		position.x = FRAME_WIDTH;
		position.y = rand() % WINDOW_WIDTH;
		break;
	default:
		break;
	}
}

Enemy::~Enemy()
{
	delete anim_left;
	delete anim_right;

}

bool Enemy::CheckBulletCollision(const Bullet& bullet)
{
	//子弹判断
	bool is_overlap_x = bullet.position.x >= position.x && bullet.position.x <= position.x + FRAME_WIDTH;
	bool is_overlap_y = bullet.position.y >= position.y && bullet.position.y <= position.y + FRAME_HEIGHT;
	return is_overlap_x && is_overlap_y;
}

bool Enemy::CheckPlayerCollision(const Player& player)
{
	//判断玩家是否在物体内
	POINT chek_position = { position.x + FRAME_WIDTH / 2, position.y + FRAME_HEIGHT / 2 };
	// 获取玩家的位置
	POINT playerPos = player.GetPosition();
	bool is_overlap_x = chek_position.x >= playerPos.x && chek_position.x <= playerPos.x + FRAME_WIDTH;
	bool is_overlap_y = chek_position.y >= playerPos.y && chek_position.y <= playerPos.y + FRAME_HEIGHT;
	return is_overlap_x && is_overlap_y;
}

void Enemy::Move(const Player& player)
{
	const POINT& player_position = player.GetPosition();
	int dir_x = player_position.x - position.x;
	int dir_y = player_position.y - position.y;
	double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (len_dir != 0) {
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		position.x += (int)(SPEED * normalized_x);
		position.y += (int)(SPEED * normalized_y);
	}
	if (dir_x < 0)
		facing_left = true;
	else if (dir_x > 0)
		facing_left = false;
}

void Enemy::Draw(int delta)
{
	int pos_shadow_x = position.x + (FRAME_WIDTH / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = position.y + FRAME_HEIGHT - 8;
	putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);
	 
	if (facing_left)
		anim_left->Play(position.x, position.y, delta);
	else
		anim_right->Play(position.x, position.y, delta);
}

void Enemy::Hurt()
{
	alive = false;
}

bool Enemy::CheckAlive()
{
	return alive;
}


