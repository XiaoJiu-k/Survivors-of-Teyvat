#pragma once
#include <graphics.h>

class Buttn
{
public:
	Buttn(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed);
	~Buttn();
	void Draw();
	void ProcessEvent(const ExMessage& msg);

private:
	enum class Status
	{
		Idle = 0,
		Hovered,
		Pushed
	};

private:
	RECT region;
	IMAGE img_idle;
	IMAGE img_hovered;
	IMAGE img_pushed;
	Status status;
protected:
	virtual void OnClick() = 0;
private:
	bool CheckCursorHit(int x, int y);
};

