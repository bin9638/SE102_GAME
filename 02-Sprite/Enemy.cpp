#include "Game.h"
#include "Enemy.h"

CEnemy::CEnemy(float x, float y, float vx, float vy)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
}

void CEnemy::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - ENEMY_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - ENEMY_WIDTH)
		{
			x = (float)(BackBufferWidth - ENEMY_WIDTH);
		}
	}
}

void CEnemy::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx > 0) ani = CAnimations::GetInstance()->Get(300);
	else ani = CAnimations::GetInstance()->Get(300);

	ani->Render(x, y);
}

