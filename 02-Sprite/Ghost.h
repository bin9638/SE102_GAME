#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AppConfiguration.h"

class CGhost : public CGameObject
{
private:
public:
	CGhost(float x, float y, float vx, float vy, int direction = -1);
	void Update(DWORD dt);
	void Render();
};


