#include "Bat.h"
#include "Game.h"


CBat::CBat(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->YStart = y;


}

void CBat::Update(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (y >= YStart + BAT_DELTA_Y || y <= YStart - BAT_DELTA_Y)
	{
		vy = -vy;
	}
}

void CBat::Render()
{	
	LPANIMATION ani;

	if (vx < 0) ani = CAnimations::GetInstance()->Get(20);
	else ani = CAnimations::GetInstance()->Get(20);

	ani->Render(x, y);
}