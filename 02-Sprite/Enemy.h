#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define ENEMY_WIDTH 15



class CEnemy : public CGameObject
{
protected:
	float vx;
public:
	CEnemy(float x, float y, float vx, float vy);
	void Update(DWORD dt);
	void Render();
};


