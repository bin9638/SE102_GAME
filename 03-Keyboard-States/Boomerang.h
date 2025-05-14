#pragma once

#include "Weapon.h"
#include "Animations.h"

const DWORD BoomerangTime = 900;

class CBoomerang : public CWeapon
{
private:
	int dx[3], dy[3];
	bool flip;
public:
	CBoomerang(float x, float y, int nx) : CWeapon(x, y, nx) {
		this->attackTime = BoomerangTime;
		this->flip = false;
		this->activeTime = BoomerangTime;
	};

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) override;
	void UpdatePosition(float simon_x, float simon_y, int aniId, int frame, DWORD dt);
	void Render();

};
