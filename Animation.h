#pragma once

#include <vector>
#include <graphics.h>
#include "Atlas.h"
class Animation
{
public:
	Animation(Atlas* atlas, int interval);

	void Play(int x, int y, int delta);


	~Animation();

private:
	int timer = 0; //动画计时
	int idx_frame = 0; // 动画索引
	int interval_ms = 0;
private:
	Atlas* anim_atlas;
};

