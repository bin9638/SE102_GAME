#include "Ghost.h"
#include "Game.h"

CGhost::CGhost(float x, float y, float vx, float vy, int direction)
{
	this->x = x;
	this->y = y;
	this->vx = vx;
	this->vy = vy;
	this->direction = direction;
	this->vx *= this->direction;
}

void CGhost::Update(DWORD dt)
{
	x += vx * dt * direction;
	if (x <= 0 || x >= CGame::GetInstance()->GetBackBufferWidth() - GHOST_WIDTH) {
		direction = -direction;
		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= CGame::GetInstance()->GetBackBufferWidth() - GHOST_WIDTH)
		{
			x = (float)(CGame::GetInstance()->GetBackBufferWidth() - GHOST_WIDTH);
		}
	}
}

void CGhost::Render()
{
	LPANIMATION ani;
	if (direction == -1) ani = CAnimations::GetInstance()->Get(GHOST_ANI_GO_LEFT);
	else ani = CAnimations::GetInstance()->Get(GHOST_ANI_GO_RIGHT);
	ani->Render(x, y);
}