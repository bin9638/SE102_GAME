#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Sprites.h"
#include "Game.h"

class CTiledBackground : public CGameObject {
private:
    CSprite* backgroundSprite;
    int tileWidth;
    int tileHeight;

public:
    CTiledBackground(float x, float y, CSprite* sprite) : CGameObject(x, y) {
        this->backgroundSprite = sprite;
        this->tileWidth = sprite->right - sprite->left + 1;
        this->tileHeight = sprite->bottom - sprite->top + 1;
    }

    void Render();
    void Update(DWORD dt) {}
};