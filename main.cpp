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
//���ɵ���
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list) {
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}
//�����ӵ�
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
//����
void DrawPlayerScore(int score) {
	static TCHAR text[64];
	_stprintf_s(text, _T("��ǰ��ҵ÷֣�%d"), score);

	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 85, 185));
	outtextxy(10, 10, text);
}
int main() {
	
	initgraph(1280,720);
	//��������
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
	//װ��ͼƬ
	loadimage(&img_background, _T("img/background.png"));
	
	BeginBatchDraw();

	while (running)
	{

		DWORD start_time = GetTickCount();
		//�����ƶ��߼�
		while (peekmessage(&msg))
		{
			player.ProcessEvent(msg);
		}
		player.move();
		UpdateBullets(bullet_list, player);
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
			enemy->Move(player);

		//�����˺������ײ
		for (Enemy* enemy : enemy_list)
		{
			if (enemy->CheckPlayerCollision(player)) {
				MessageBox(GetHWnd(), _T("�ۡ�1���ۿ�ս��CG"), _T("��Ϸ����"), MB_OK);
				running = false;
				break;
			}
		}
		//����ӵ��͵�����ײ
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
		//�Ƴ�����Ϊ0�ĵ���
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
		//���ر���ͼ������
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
