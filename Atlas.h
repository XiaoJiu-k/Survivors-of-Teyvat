#pragma once
#include <graphics.h>
#include <vector>
class Atlas
{
public:
	Atlas(LPCTSTR path,int num);
	~Atlas();
public:
	std::vector<IMAGE*> frame_list;
};


