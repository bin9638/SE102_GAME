#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define MARIO_WIDTH 14

class CBrick : public CGameObject {
public: 
	CBrick(float x, float y);
	void Render();
	void Update(DWORD dt) {}
};

class CMario : public CGameObject
{
protected:
public:
	CMario(float x, float y, float vx, float vy);
	void Update(DWORD dt);
	void Render();
};


