#include "Boomerang.h"
#include "Simon.h"
#include "Animations.h"

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Tạm thời không làm gì cả vì vị trí Whip được cập nhật thông qua Simon
}

void CBoomerang::UpdatePosition(float simon_x, float simon_y, int aniId, int frame, DWORD dt)
{
	activeTime -= dt;
	if (activeTime <= attackTime / 2 && flip == false)
	{
		flip = true;
		nx = -nx;
		
	}
	vx = 0.3 * nx;
	x += vx * dt;
}

void CBoomerang::Render()
{
	int aniId = nx > 0 ? ID_ANI_WEAPON_BOOMERANG_RIGHT : ID_ANI_WEAPON_BOOMERANG_LEFT;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}
