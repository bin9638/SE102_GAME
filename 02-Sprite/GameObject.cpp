#include "GameObject.h"


CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	health = 1;
	direction = 1;
}

CGameObject::CGameObject(float x, float y)
{
	this->x = x;
	this->y = y;
	vx = vy = 0;
	health = 1;
	direction = 1;
}

int CGameObject::getHealth()
{
	return health;
}

void CGameObject::setHealth(int health)
{
	this->health = health;
}

int CGameObject::getDirection()
{
	return direction;
}

void CGameObject::setDirection(int direction)
{
	this->direction = direction;
}

float CGameObject::getX()
{
	return x;
}

void CGameObject::setX(float x)
{
	this->x = x;
}

float CGameObject::getY()
{
	return y;
}

void CGameObject::setY(float y)
{
	this->y = y;
}

float CGameObject::getVx()
{
	return vx;
}

void CGameObject::setVx(float vx)
{
	this->vx = vx;
}

float CGameObject::getVy()
{
	return vy;
}

void CGameObject::setVy(float vy)
{
	this->vy = vy;
}


void CGameObject::SetState(int state)
{
	this->state = state;
}