﻿#include "Simon.h"

void CSimon::Update(DWORD dt)
{
	if (isAttacking)
	{
		attackTime -= dt;
		if (attackTime <= 0)
		{
			isAttacking = false;
		}
	}

	// Di chuyển và rơi như bình thường
	x += vx * dt;
	y += vy * dt;
	vy += SIMON_GRAVITY * dt;

	// Kiểm tra va chạm với mặt đất
	if (y > GROUND_Y && x >= -1000 && x < 1000)
	{
		vy = 0; y = GROUND_Y;
	}

	// Kiểm tra biên giới
	//if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;
}


void CSimon::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	// Kiểm tra nếu Simon đang trên không
	if (y < GROUND_Y)
	{
		if (isAttacking)
		{
			aniId = (nx >= 0) ? ID_ANI_SIMON_SIT_ATTACK_RIGHT : ID_ANI_SIMON_SIT_ATTACK_LEFT;
		}
		else
		{
			aniId = (nx >= 0) ? ID_ANI_SIMON_SIT_RIGHT : ID_ANI_SIMON_SIT_LEFT;
		}
	}
	else if (isSitting)
	{
		if (isAttacking)
		{
			aniId = (nx >= 0) ? ID_ANI_SIMON_SIT_ATTACK_RIGHT : ID_ANI_SIMON_SIT_ATTACK_LEFT;
		}
		else
		{
			aniId = (nx >= 0) ? ID_ANI_SIMON_SIT_RIGHT : ID_ANI_SIMON_SIT_LEFT;
		}
	}
	else
	{
		if (isAttacking)
		{
			aniId = (nx > 0) ? ID_ANI_SIMON_STAND_ATTACK_RIGHT : ID_ANI_SIMON_STAND_ATTACK_LEFT;
		}
		else if (vx > 0)
		{
			aniId = ID_ANI_SIMON_WALKING_RIGHT;
		}
		else if (vx < 0)
		{
			aniId = ID_ANI_SIMON_WALKING_LEFT;
		}
		else
		{
			aniId = (nx > 0) ? ID_ANI_SIMON_IDLE_RIGHT : ID_ANI_SIMON_IDLE_LEFT;
		}
	}
	currentId = aniId;

	animations->Get(aniId)->Render(x, y);
}


void CSimon::SetState(int state)
{
	CAnimations* animations = CAnimations::GetInstance();

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		if (y == GROUND_Y)
		{
			vy = -SIMON_JUMP_SPEED_Y;
		}
		break;
	case SIMON_STATE_SIT:
		if (y == GROUND_Y)
		{
			vx = 0;
			vy = 0;
			isSitting = true;
		}
		break;
	case SIMON_STATE_ATTACK:
		if (isAttacking && attackTime > 150) return;

		isAttacking = true;
		attackTime = 900;

		if (nx >= 0)
		{
			animations->Get(ID_ANI_WEAPON_RIGHT)->Reset();
			animations->Get(ID_ANI_SIMON_STAND_ATTACK_RIGHT)->Reset();
		}
		else
		{
			animations->Get(ID_ANI_WEAPON_LEFT)->Reset();
			animations->Get(ID_ANI_SIMON_STAND_ATTACK_LEFT)->Reset();
		}
		if (isSitting) {
			if (nx >= 0)
				animations->Get(ID_ANI_SIMON_SIT_ATTACK_RIGHT)->Reset();
			else
				animations->Get(ID_ANI_SIMON_SIT_ATTACK_LEFT)->Reset();
		}

		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		isSitting = false;
		isAttacking = false;
		break;
	}
	CGameObject::SetState(state);
}

void CSimon::KeyState(BYTE* states)
{
	if (isAttacking) {
		return;
	}

	CGame* game = CGame::GetInstance();

	// Kiểm tra nếu nhấn đồng thời phím DOWN và SPACE (Ngồi và Tấn công)
	if (!isAttacking && game->IsKeyDown(DIK_DOWN) && game->IsKeyDown(DIK_SPACE)) {
		if (!isSitting) {
			SetState(SIMON_STATE_SIT);  // Đảm bảo Simon đang ngồi
		}
		SetState(SIMON_STATE_ATTACK);  // Thực hiện tấn công
	}
	else if (game->IsKeyDown(DIK_RIGHT)) {
		SetState(SIMON_STATE_WALKING_RIGHT);
		if (game->IsKeyDown(DIK_UP)) {
			SetState(SIMON_STATE_JUMP);
		}
		if (!isAttacking && game->IsKeyDown(DIK_SPACE)) {
			SetState(SIMON_STATE_ATTACK);
		}
	}
	else if (game->IsKeyDown(DIK_LEFT)) {
		SetState(SIMON_STATE_WALKING_LEFT);
		if (game->IsKeyDown(DIK_UP)) {
			SetState(SIMON_STATE_JUMP);
		}
		if (!isAttacking && game->IsKeyDown(DIK_SPACE)) {
			SetState(SIMON_STATE_ATTACK);
		}
	}
	else if (game->IsKeyDown(DIK_UP)) {
		if (!isAttacking) SetState(SIMON_STATE_JUMP);
	}
	else if (!isAttacking) {
		SetState(SIMON_STATE_IDLE);
	}
	

	// Nếu chỉ nhấn phím DOWN mà không nhấn phím SPACE, Simon sẽ ngồi
	if (game->IsKeyDown(DIK_DOWN) && !game->IsKeyDown(DIK_SPACE)) {
		SetState(SIMON_STATE_SIT);
	}

	// Kiểm tra phím tấn công nếu phím SPACE được nhấn
	if (!isAttacking && game->IsKeyDown(DIK_SPACE) && !game->IsKeyDown(DIK_DOWN)) {
		SetState(SIMON_STATE_IDLE);
		SetState(SIMON_STATE_ATTACK);
	}
}


void CSimon::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
}

void CSimon::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		// Nếu đang tấn công, chỉ chuyển trạng thái khi attackTime đã hết
		if (!isAttacking || attackTime <= 0)
		{
			SetState(SIMON_STATE_IDLE);
		}
		break;
	}
}