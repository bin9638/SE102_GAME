#pragma once
#include "AppConfiguration.h"
#include "GameObject.h"
#include "Animation.h"	
#include "Animations.h"


class CBat : public CGameObject
{
private:
	float YStart;
public:
	CBat(float x, float y, float vx, float vy);
	void Update(DWORD dt);
	void Render();
};
