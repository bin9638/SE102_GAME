#include "Bat.h"
#include "debug.h"
#include "Game.h"


CBat::CBat(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->YStart = y;
	this->XStart = x;
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;

	if (y >= YStart + BAT_DELTA_Y || y <= YStart - BAT_DELTA_Y)
	{
		vy = -vy;
	}

	if(coObjects != nullptr)
		CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBat::Render()
{
	LPANIMATION ani;

	if (vx < 0) ani = CAnimations::GetInstance()->Get(BAT_ANI_FLY_LEFT);
	else ani = CAnimations::GetInstance()->Get(BAT_ANI_FLY_RIGHT);

	ani->Render(x, y);
}

void CBat::OnCollisionWith(LPCOLLISIONEVENT e)  
{  
   // Handle collision with Simon  
	this->Delete();
}