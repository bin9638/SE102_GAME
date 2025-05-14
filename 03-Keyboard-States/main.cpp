﻿/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 03 - KEYBOARD AND OBJECT STATE

	This sample illustrates how to:

		1/ Process keyboard input
		2/ Control object state with keyboard events
================================================================ */

#include <windows.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Animation.h"
#include "Animations.h"
#include "Sprite.h"
#include "Sprites.h"

#include "Mario.h"
#include "Weapon.h"
#include "Simon.h"
#include "Brick.h"
#include "Quadtree.h"
#include "Bat.h"

#include "TiledBackground.h"

#include "SampleKeyEventHandler.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"03 - Keyboard and Mario states"
#define WINDOW_ICON_PATH L"mario.ico"


#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_SIMON 30
#define ID_TEX_BACKGROUND 40
#define ID_TEX_BAT 50

#define ID_SPRITE_BRICK 20001
#define ID_SPRITE_BACKGROUND 20002

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_BAT TEXTURES_DIR "\\bat.png"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc.png"
#define TEXTURE_PATH_SIMON TEXTURES_DIR "\\simon.png"
#define TEXTURE_PATH_BACKGROUND TEXTURES_DIR "\\background.png"

#define MARIO_START_X 200.0f
#define MARIO_START_Y 10.0f

#define SIMON_START_X 200.0f
#define SIMON_START_Y 10.0f

#define BRICK_X 0.0f
#define BRICK_Y GROUND_Y + 20.0f
#define NUM_BRICKS 100

CMario* mario = NULL;
CWeapon* weapon = NULL;
CSimon* simon = NULL;
CBat* bat = NULL;

CTiledBackground* background = NULL;

CSampleKeyHandler* keyHandler;

vector<LPGAMEOBJECT> objects;
Quad* root = new Quad(0, Point(0, 0), Point(1000, 1000));


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures* textures = CTextures::GetInstance();

	//textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);
	textures->Add(ID_TEX_SIMON, TEXTURE_PATH_SIMON);
	textures->Add(ID_TEX_BACKGROUND, TEXTURE_PATH_BACKGROUND);
	textures->Add(ID_TEX_BAT, TEXTURE_PATH_BAT);

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	{
		// Trong LoadResources()
		LPTEXTURE texBackground = textures->Get(ID_TEX_BACKGROUND); // Hoặc texture riêng cho background
		sprites->Add(ID_SPRITE_BACKGROUND, 18, 92, 717, 247, texBackground);

		int mapWidth = 20;
		int mapHeight = 15;

		// Tạo sprite từ sprites đã load
		CSprite* bgSprite = CSprites::GetInstance()->Get(ID_SPRITE_BACKGROUND);

		// Tạo background object và thêm vào danh sách objects
		CTiledBackground* background = new CTiledBackground(0, 0, bgSprite, mapWidth, mapHeight);
		objects.push_back(background);
	}
	
	//{
	//	// Trong LoadResources()
	//	LPTEXTURE texBackground = textures->Get(ID_TEX_BACKGROUND);
	//	CSprite* originalBgSprite = new CSprite(ID_SPRITE_BACKGROUND, 18, 92, 717, 247, texBackground);

	//	// Tạo background object với kích thước map (điều chỉnh theo nhu cầu)
	//	int mapWidth = 20;   // Số lượng tile theo chiều ngang của map
	//	int mapHeight = 15;  // Số lượng tile theo chiều dọc của map
	//	CTiledBackground* background = new CTiledBackground(0, 0, originalBgSprite, mapWidth, mapHeight);
	//	objects.push_back(background);
	//}

	{
		LPTEXTURE texSimon = textures->Get(ID_TEX_SIMON);
		
		// WALK RIGHT
		sprites->Add(10101, 1519, 21, 1534, 53, texSimon);
		sprites->Add(10102, 1536, 21, 1551, 53, texSimon);
		sprites->Add(10103, 1553, 21, 1568, 53, texSimon);

		// WALK LEFT
		sprites->Add(10111, 29, 21, 44, 53, texSimon);
		sprites->Add(10112, 46, 21, 61, 53, texSimon);
		sprites->Add(10113, 63, 21, 78, 53, texSimon);

		// IDLE RIGHT
		sprites->Add(10121, 1581, 21, 1596, 53, texSimon);

		// IDLE LEFT
		sprites->Add(10131, 1, 21, 16, 53, texSimon);

		// JUMP/DUCK RIGHT
		sprites->Add(10141, 1498, 21, 1513, 46, texSimon);

		// JUMP/DUCK LEFT
		sprites->Add(10151, 84, 21, 99, 46, texSimon);

		// STAND ATTACK RIGHT
		sprites->Add(10161, 1573, 79, 1596, 108, texSimon);
		sprites->Add(10162, 1556, 79, 1571, 108, texSimon);
		sprites->Add(10163, 1531, 79, 1552, 108, texSimon);

		// STAND ATTACK LEFT
		sprites->Add(10171, 1, 79, 24, 108, texSimon);
		sprites->Add(10172, 26, 79, 41, 108, texSimon);
		sprites->Add(10173, 45, 79, 66, 108, texSimon);

		// SIT ATTACK RIGHT
		sprites->Add(10181, 1427, 79, 1450, 101, texSimon);
		sprites->Add(10182, 1410, 79, 1425, 101, texSimon);
		sprites->Add(10183, 1385, 79, 1406, 101, texSimon);

		// SIT ATTACK LEFT
		sprites->Add(10191, 147, 79, 170, 101, texSimon);
		sprites->Add(10192, 172, 79, 187, 101, texSimon);
		sprites->Add(10193, 191, 79, 212, 101, texSimon);

		LPANIMATION ani;
		
		ani = new CAnimation(100);
		ani->Add(10101);
		ani->Add(10102);
		ani->Add(10103);
		animations->Add(ID_ANI_SIMON_WALKING_RIGHT, ani);

		ani = new CAnimation(100);
		ani->Add(10111);
		ani->Add(10112);
		ani->Add(10113);
		animations->Add(ID_ANI_SIMON_WALKING_LEFT, ani);

		ani = new CAnimation(100);
		ani->Add(10121);
		animations->Add(ID_ANI_SIMON_IDLE_RIGHT, ani);

		ani = new CAnimation(100);
		ani->Add(10131);
		animations->Add(ID_ANI_SIMON_IDLE_LEFT, ani);

		ani = new CAnimation(100);
		ani->Add(10141);
		animations->Add(ID_ANI_SIMON_SIT_RIGHT, ani);

		ani = new CAnimation(100);
		ani->Add(10151);
		animations->Add(ID_ANI_SIMON_SIT_LEFT, ani);

		ani = new CAnimation(300);
		ani->Add(10161);
		ani->Add(10162);
		ani->Add(10163);
		animations->Add(ID_ANI_SIMON_STAND_ATTACK_RIGHT, ani);

		ani = new CAnimation(300);
		ani->Add(10171);
		ani->Add(10172);
		ani->Add(10173);
		animations->Add(ID_ANI_SIMON_STAND_ATTACK_LEFT, ani);

		ani = new CAnimation(300);
		ani->Add(10181);
		ani->Add(10182);
		ani->Add(10183);
		animations->Add(ID_ANI_SIMON_SIT_ATTACK_RIGHT, ani);

		ani = new CAnimation(300);
		ani->Add(10191);
		ani->Add(10192);
		ani->Add(10193);
		animations->Add(ID_ANI_SIMON_SIT_ATTACK_LEFT, ani);

		simon = new CSimon(SIMON_START_X, SIMON_START_Y);
		CGame::GetInstance()->InitKeyboard(simon);
		objects.push_back(simon);
		objects.push_back(new CSimon(SIMON_START_X, SIMON_START_Y));
	}

	// WEAPON
	{
		LPTEXTURE texSimon = textures->Get(ID_TEX_SIMON);
		
		// WHIP_LEFT
		sprites->Add(20101, 61, 485, 68, 508, texSimon);
		sprites->Add(20102, 105, 482, 120, 500, texSimon);
		sprites->Add(20103, 222, 487, 261, 492, texSimon);

		// WEAPON_RIGHT
		sprites->Add(20111, 1529, 485, 1536, 508, texSimon);
		sprites->Add(20112, 1477, 482, 1492, 500, texSimon);
		sprites->Add(20113, 1336, 487, 1375, 492, texSimon);

		// KNIFE_LEFT
		sprites->Add(20221, 1228, 480, 1243, 488, texSimon);

		// KNIFE_RIGHT
		sprites->Add(20231, 354, 480, 369, 488, texSimon);

		// BOOMERANG_RIGHT
		sprites->Add(20241, 402, 479, 415, 491, texSimon);
		sprites->Add(20242, 418, 478, 432, 491, texSimon);
		sprites->Add(20243, 436, 478, 450, 491, texSimon);

		// BOOMERANG_LEFT
		sprites->Add(20244, 1182, 479, 1195, 491, texSimon);
		sprites->Add(20245, 1165, 478, 1179, 491, texSimon);
		sprites->Add(20246, 1147, 478, 1161, 491, texSimon);


		LPANIMATION ani;

		ani = new CAnimation(100);
		ani->Add(20101);
		ani->Add(20102);
		ani->Add(20103);
		animations->Add(ID_ANI_WEAPON_LEFT, ani);
		
		ani = new CAnimation(100);
		ani->Add(20111);
		ani->Add(20112);
		ani->Add(20113);
		animations->Add(ID_ANI_WEAPON_RIGHT, ani);


		ani = new CAnimation(100);
		ani->Add(20221);
		animations->Add(ID_ANI_WEAPON_KNIFE_LEFT, ani);

		ani = new CAnimation(250);
		ani->Add(20231);
		animations->Add(ID_ANI_WEAPON_KNIFE_RIGHT, ani);


		ani = new CAnimation(300);
		ani->Add(20241);
		ani->Add(20242);
		ani->Add(20243);
		animations->Add(ID_ANI_WEAPON_BOOMERANG_RIGHT, ani);

		ani = new CAnimation(300);
		ani->Add(20244);
		ani->Add(20245);
		ani->Add(20246);
		animations->Add(ID_ANI_WEAPON_BOOMERANG_LEFT, ani);

	}

	{
		// Brick objects 
		LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
		sprites->Add(ID_SPRITE_BRICK, 372, 153, 372 + 15, 153 + 15, texMisc);

		LPANIMATION ani;

		ani = new CAnimation(100);
		ani->Add(ID_SPRITE_BRICK);
		animations->Add(ID_ANI_BRICK, ani);

		for (int i = 0; i < NUM_BRICKS; i++)
		{
			CBrick* b = new CBrick(BRICK_X + (i * 3 + 3 + 10) *BRICK_WIDTH, BRICK_Y - i * BRICK_WIDTH);
			b->SetState(-2);
			objects.push_back(b);

			b = new CBrick(BRICK_X + (i * 3 + 4 + 10) * BRICK_WIDTH, BRICK_Y - i * BRICK_WIDTH);
			b->SetState(-2);
			objects.push_back(b);

			b = new CBrick(BRICK_X + (i * 3 + 5 + 10) * BRICK_WIDTH, BRICK_Y - i * BRICK_WIDTH);
			b->SetState(-2);
			objects.push_back(b);

			b = new CBrick(BRICK_X + (i * 3 + 6 + 10) * BRICK_WIDTH, BRICK_Y - i * BRICK_WIDTH);
			b->SetState(-2);
			objects.push_back(b);

			b = new CBrick(BRICK_X + (i * 3 + 7 + 10) * BRICK_WIDTH, BRICK_Y - i * BRICK_WIDTH);
			b->SetState(-2);
			objects.push_back(b);

			b = new CBrick(BRICK_X + i * BRICK_WIDTH, BRICK_Y);
			b->SetState(-2);
			objects.push_back(b);
			//root->insert(b);
		}
	}


	// BAT
	{	
		LPTEXTURE texBat = textures->Get(ID_TEX_BAT);

		// BAT_LEFT
		sprites->Add(40001, 98, 0, 127, 31, texBat);
		sprites->Add(40002, 64, 0, 93, 31, texBat);

		LPANIMATION ani;
		ani = new CAnimation(500);
		ani->Add(40001);
		ani->Add(40002);
		animations->Add(BAT_ANI_FLY_LEFT, ani);

		// BAT_RIGHT
		sprites->Add(40003, 160, 0, 191, 27, texBat);
		sprites->Add(40004, 130, 0, 159, 31, texBat);

		ani = new CAnimation(500);
		ani->Add(40003);
		ani->Add(40004);
		animations->Add(BAT_ANI_FLY_RIGHT, ani);

		//bat = new CBat(BAT_START_X, BAT_START_Y, -BAT_START_VX, BAT_START_VY);
		//objects.push_back(bat);
	}
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;

	for (auto obj : objects)
		coObjects.push_back(obj);

	for (auto obj : objects)
		if (!dynamic_cast<CBat*>(obj))
			obj->Update(dt, &coObjects);

	vector<LPGAMEOBJECT>* weapons = simon->getweapon();
	
	for (auto obj : objects)
		if (dynamic_cast<CBat*>(obj))
		{
			obj->Update(dt, weapons);
		}

	delete weapons;

	// Lấy vị trí của Simon

	objects.clear();
	for (auto obj : coObjects)
		if (obj->IsDeleted())
			delete obj;
				else objects.push_back(obj);

	float simonX, simonY;
	simon->GetPosition(simonX, simonY);

	CGame::GetInstance()->GetCamera()->FollowSimon(simonX, simonY);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

	spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

	FLOAT NewBlendFactor[4] = { 0,0,0,0 };
	pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Render();
	}

	root->Render();

	spriteHandler->End();
	pSwapChain->Present(0, 0);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			CGame::GetInstance()->ProcessKeyboard();
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	SetDebugWindow(hWnd);

	CGame* game = CGame::GetInstance();
	game->Init(hWnd, hInstance);

	

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	LoadResources();

	Run();

	return 0;
}