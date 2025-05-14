#pragma once
#include "GameObject.h"
#include "Animation.h"	
#include "Animations.h"

// BAT
#define BAT_START_X 500.0f
#define BAT_START_Y 100.0f
#define BAT_START_VX 0.05f 
#define BAT_START_VY 0.05f
#define BAT_DELTA_Y 10
#define BAT_DELTA_X 10
#define BAT_ANI_FLY_LEFT 20
#define BAT_ANI_FLY_RIGHT 21


class CBat : public CGameObject
{
private:
	float YStart;
	float XStart;
public:
	CBat(float x, float y, float vx, float vy);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {
        // Implement the bounding box logic here
        left = x;
        top = y;
        right = x + 32; // Example width
        bottom = y + 48; // Example height
    }

    int IsCollidable() override
    {
        return 1;
    }

    void OnCollisionWith(LPCOLLISIONEVENT e) override;
};
