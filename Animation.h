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
	int timer = 0; //������ʱ
	int idx_frame = 0; // ��������

	int interval_ms = 0;
	std::vector<IMAGE*> frame_list;
};

