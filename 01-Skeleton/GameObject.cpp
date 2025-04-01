#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"

/*
	Initialize game object 
*/
CGameObject::CGameObject(float x, float y, LPTEXTURE tex)
{
	this->x = x;
	this->y = y;
	this->texture = tex;
}

void CGameObject::Render()
{
	CGame::GetInstance()->Draw(x, y, texture);
}

CGameObject::~CGameObject()
{
	if (texture != NULL) delete texture;
}

#define MARIO_VX 0.1f
#define MARIO_WIDTH 14

void CMario::Update(DWORD dt)
{
	x += vx*dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= MARIO_WIDTH || x >= BackBufferWidth - MARIO_WIDTH) {
		
		vx = -vx;

		if (x <= MARIO_WIDTH)
		{
			x = MARIO_WIDTH;
		}
		else if (x >= BackBufferWidth - MARIO_WIDTH)
		{
			x = (float)(BackBufferWidth - MARIO_WIDTH);
		}
	}

	y += vy * dt;
	
	int BackBufferHeight = CGame::GetInstance()->GetBackBufferHeight();
	if (y <= MARIO_WIDTH || y >= BackBufferHeight - MARIO_WIDTH) {
		vy = -vy;
		if (y <= MARIO_WIDTH)
		{
			y = MARIO_WIDTH;
		}
		else if (y >= BackBufferHeight - MARIO_WIDTH)
		{
			y = (float)(BackBufferHeight - MARIO_WIDTH);
		}
	}
}
