#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"
#include "Game.h"

#define Y_TO_MARIO -50
#define LEFT_X_TO_MARIO -10
#define RIGHT_X_TO_MARIO 10

#pragma region ANIMATION_ID

#define SHURIKEN_SPEED 0.2f
#define SHURIKEN_LIVE_TIME 1000

#define ID_ANI_WEAPON_LEFT 2000
#define ID_ANI_WEAPON_RIGHT 2001
#define ID_ANI_WEAPON_IDLE 2002

#define ID_ANI_SHURIKEN 4000

#pragma endregion

class CWeapon : public CGameObject
{
protected:
	int curStep = -1;
	int lastStepTime = 0;
	int dx[4], dy[4];
public:
	CWeapon(float x, float y) : CGameObject(x, y) { }
	void Update(DWORD dt);
	void Render();
	void SetDxDy(int state);
};


class CShuriken : public CGameObject
{
	protected:
	public:
	CShuriken(float x, float y) : CGameObject(x, y) { 
		//x = -1000;
	}
	void Update(DWORD dt);
	void Render();
};