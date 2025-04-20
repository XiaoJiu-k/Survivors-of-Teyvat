#include <iostream>
#include <graphics.h>
#include <string>
#include <vector>
#include "Player.h"
#include "Animation.h"
#include "putimage_alpha.h"
#include "Enemy.h"
#include "Bullet.h"
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")
//生成敌人
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list) {
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}
//生成子弹
void UpdateBullets(std::vector<Bullet>& bullet_list,const Player& player) {
	const double RADIAL_SPEED = 0.0045;
	const double TANGENT_SPEED = 0.0055;
	double radian_interval = 2 * 3.14159 / bullet_list.size();
	POINT player_position = player.GetPosition();
	double radius = 100 + 25 * sin(GetTickCount() * RADIAL_SPEED);
	for (size_t i = 0; i < bullet_list.size(); i++)
	{
		double radian = GetTickCount() * TANGENT_SPEED + radian_interval * i;
		bullet_list[i].position.x = player_position.x + player.PLAYER_WIDTH / 2 + (int)(radius * sin(radian));
		bullet_list[i].position.y = player_position.y + player.PLAYER_HEIGHT / 2 + (int)(radius * cos(radian));
	}
}
//积分
void DrawPlayerScore(int score) {
	static TCHAR text[64];
	_stprintf_s(text, _T("当前玩家得分：%d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}
int main() {
	
	initgraph(1280,720);
	//加载音乐
	mciSendString(_T("open mus/bgm.mp3 alias bgm"), NULL, 0, NULL);
	mciSendString(_T("open mus/hit.wav alias hit"), NULL, 0, NULL);

	mciSendString(_T("play bgm repeat from 0"), NULL, 0, NULL);

	bool running = true;
	int score = 0;
	ExMessage msg;
	IMAGE img_background;
	std::vector<Enemy*> enemy_list;
	std::vector<Bullet> bullet_list(3);
	Player player;
	//装配图片
	loadimage(&img_background, _T("img/background.png"));
	
	BeginBatchDraw();

	while (running)
	{

		DWORD start_time = GetTickCount();
		//人物移动逻辑
		while (peekmessage(&msg))
		{
			player.ProcessEvent(msg);
		}
		player.move();
		UpdateBullets(bullet_list, player);
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
			enemy->Move(player);

		//检测敌人和玩家碰撞
		for (Enemy* enemy : enemy_list)
		{
			if (enemy->CheckPlayerCollision(player)) {
				MessageBox(GetHWnd(), _T("扣”1“观看战败CG"), _T("游戏结束"), MB_OK);
				running = false;
				break;
			}
		}
		//检测子弹和敌人碰撞
		for (Enemy* enemy : enemy_list)
		{
			for (Bullet& bullet : bullet_list)
			{
				if (enemy->CheckBulletCollision(bullet))
				{
					mciSendString(_T("play hit from 0"), NULL, 0, NULL);
					enemy->Hurt();
					score++;
				}
					
			}
		}
		//移除生命为0的敌人
		for (size_t i = 0; i < enemy_list.size(); i++)
		{
			Enemy* enemy = enemy_list[i];
			if (!enemy->CheckAlive())
			{
				std::swap(enemy_list[i], enemy_list.back());
				enemy_list.pop_back();
				delete enemy;
			}
		}

		cleardevice();
		//加载背景图与人物
		putimage(0, 0, &img_background);

		player.Draw(1000/120);
		for (Enemy* enemy : enemy_list)
			enemy->Draw(1000/120);
		for (Bullet& bullet : bullet_list)
			bullet.Draw();
		
		DrawPlayerScore(score);
		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 120) {
			Sleep(1000 / 120 - delta_time);
		}

	}

	EndBatchDraw();
	return 0;
}
