#include <iostream>
#include <graphics.h>
#include <string>
#include <vector>
#include "Player.h"
#include "Animation.h"
#include "putimage_alpha.h"
#include "Enemy.h"


void TryGenerateEnemy(std::vector<Enemy*>& enemy_list) {
	const int INTERVAL = 100;
	static int counter = 0;
	if ((++counter) % INTERVAL == 0)
		enemy_list.push_back(new Enemy());
}

int main() {
	
	initgraph(1280,720);

	bool running = true;

	ExMessage msg;
	IMAGE img_background;
	std::vector<Enemy*> enemy_list;


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
		TryGenerateEnemy(enemy_list);
		for (Enemy* enemy : enemy_list)
			enemy->Move(player);

		cleardevice();
		//加载背景图与人物
		putimage(0, 0, &img_background);

		player.Draw(1000/120);
		for (Enemy* enemy : enemy_list)
			enemy->Draw(1000/120);
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
