#pragma once

#include <vector>
#include <graphics.h>
class Animation
{
public:
	Animation(LPCTSTR path, int num, int interval);

	void Play(int x, int y, int delta);


	~Animation();

private:
	int timer = 0; //动画计时
	int idx_frame = 0; // 动画索引

	int interval_ms = 0;
	std::vector<IMAGE*> frame_list;
};

