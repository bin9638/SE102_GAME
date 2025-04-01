#pragma once

#include <Windows.h>
#include <d3dx10.h>
#include <vector>
#include "AppConfiguration.h"

#include "Sprites.h"


using namespace std;

class CGameObject
{
protected:

	int health;

	int direction;

	float x; 
	float y;

	float vx;
	float vy;

	int state;

public: 
	
	CGameObject();
	CGameObject(float x, float y);
	virtual ~CGameObject() {};

	int getHealth();
	void setHealth(int health);
	
	int getDirection();
	void setDirection(int direction);

	float getX();
	void setX(float x);

	float getY();
	void setY(float y);

	float getVx();
	void setVx(float vx);

	float getVy();
	void setVy(float vy);

	void SetState(int state);


	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
};

typedef CGameObject* LPGAMEOBJECT;