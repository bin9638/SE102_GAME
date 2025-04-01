/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"


#include "Mario.h"
#include "Enemy.h"
#include "Bat.h"
#include "Ghost.h"
#include "Simon.h"

#include "AppConfiguration.h"



#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_BAT 40
#define ID_TEX_GHOST 50
#define ID_TEX_SIMON 60

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_BAT TEXTURES_DIR "\\bat.png"
#define TEXTURE_PATH_GHOST TEXTURES_DIR "\\ghost.png"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc_transparent.png"
#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies.png"
#define TEXTURE_PATH_SIMON TEXTURES_DIR "\\simon.png"

CMario *mario;

CEnemy* enemy;
#define ENEMY_START_X 10.0f
#define ENEMY_START_Y 150.0f
#define ENEMY_START_VX 0.1f
#define ENEMY_START_VY 0.1f

CBrick *brick;
CBat* bat;
CGhost* ghost;
CSimon* simon;
CWeapon* weapon;
vector<LPGAMEOBJECT> objects;


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
	CAnimations* animations = CAnimations::GetInstance();
	LPANIMATION ani;

	// textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	// textures->Add(ID_ENEMY_TEXTURE, TEXTURE_PATH_ENEMIES, D3DCOLOR_XRGB(156, 219, 239));
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);

	textures->Add(ID_TEX_ENEMY, TEXTURE_PATH_ENEMIES);
	textures->Add(ID_TEX_BAT, TEXTURE_PATH_BAT);

	textures->Add(ID_TEX_GHOST, TEXTURE_PATH_GHOST);
	textures->Add(ID_TEX_SIMON, TEXTURE_PATH_SIMON);

	CSprites* sprites = CSprites::GetInstance();

	{
		textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
		LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

		// readline => id, left, top, right 

		//MARIO LEFT
		sprites->Add(10001, 246, 154, 259, 181, texMario);
		sprites->Add(10002, 275, 154, 290, 181, texMario);
		sprites->Add(10003, 304, 154, 321, 181, texMario);

		// MARIO RIGHT
		sprites->Add(10011, 186, 154, 200, 181, texMario);
		sprites->Add(10012, 155, 154, 171, 181, texMario);
		sprites->Add(10013, 125, 154, 141, 181, texMario);

		ani = new CAnimation(100);
		ani->Add(10001);
		ani->Add(10002);
		ani->Add(10003);
		animations->Add(500, ani);


		ani = new CAnimation(100);
		ani->Add(10011);
		ani->Add(10012);
		ani->Add(10013);
		animations->Add(501, ani);

		mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX, MARIO_START_VY);
		objects.push_back(mario);
	}


	// MISC
	{
		textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);

		LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);
		sprites->Add(20001, 300, 117, 317, 133, texMisc);
		sprites->Add(20002, 318, 117, 335, 133, texMisc);
		sprites->Add(20003, 336, 117, 353, 133, texMisc);
		sprites->Add(20004, 354, 117, 371, 133, texMisc);

		ani = new CAnimation(100);
		ani->Add(20001, 1000);
		ani->Add(20002);
		ani->Add(20003);
		ani->Add(20004);
		animations->Add(510, ani);
	}


	// ENEMY
	{
		LPTEXTURE texEnemy = textures->Get(ID_TEX_ENEMY);
		sprites->Add(30001, 90, 178, 105, 202, texEnemy);
		sprites->Add(30002, 66, 178, 81, 202, texEnemy);
		//sprites->Add(30003, 36, 173, 60, 202, texEnemy);
		//sprites->Add(30004, 7, 173, 31, 202, texEnemy);

		ani = new CAnimation(100);
		ani->Add(30001);
		ani->Add(30002);

		//ani->Add(30003);
		//ani->Add(30004);
		//animations->Add(300, ani);
		enemy = new CEnemy(ENEMY_START_X, ENEMY_START_Y, ENEMY_START_VX, ENEMY_START_VY);
		objects.push_back(enemy);
	}

	// BAT
	{
		LPTEXTURE texBat = textures->Get(ID_TEX_BAT);
		sprites->Add(40001, 98, 0, 127, 31, texBat);
		sprites->Add(40002, 64, 0, 93, 31, texBat);




		ani = new CAnimation(100);
		ani->Add(40001);
		ani->Add(40002);
		animations->Add(BAT_ANI_FLY_LEFT, ani);

		bat = new CBat(BAT_START_X, BAT_START_Y, -BAT_START_VX, BAT_START_VY);
		objects.push_back(bat);
	}


	{
		LPTEXTURE texGhost = textures->Get(ID_TEX_GHOST);
		sprites->Add(50001, 36, 0, 67, 63, texGhost);
		sprites->Add(50002, 0, 0, 32, 63, texGhost);

		ani = new CAnimation(100);
		ani->Add(50001);
		ani->Add(50002);
		animations->Add(300, ani);
	}



	/*mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX, MARIO_START_VY);

	brick = new CBrick(100.0f, 100.0f);
	enemy = new CEnemy(ENEMY_START_X, ENEMY_START_Y, ENEMY_START_VX, ENEMY_START_VY);
	bat = new CBat(BAT_START_X, BAT_START_Y, -BAT_START_VX, BAT_START_VY);*/

	//ghost = new CGhost(GHOST_START_X, GHOST_START_Y, GHOST_START_VX, GHOST_START_VY);

	// SIMON
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
	}
	

	// WEAPON
	{
		LPTEXTURE texSimon = textures->Get(ID_TEX_SIMON);

		// WEAPON_LEFT
		sprites->Add(20101, 1, 485, 8, 508, texSimon);
		sprites->Add(20102, 10, 482, 26, 500, texSimon);
		sprites->Add(20103, 27, 485, 51, 493, texSimon);

		// WEAPON_RIGHT
		sprites->Add(20111, 1588, 485, 1595, 508, texSimon);
		sprites->Add(20112, 1572, 482, 1586, 500, texSimon);
		sprites->Add(20113, 1547, 485, 1571, 493, texSimon);

		// WEAPON_IDLE
		sprites->Add(20211, 1572, 482, 1586, 500, texSimon);


		LPANIMATION ani;

		ani = new CAnimation(300);
		ani->Add(20101);
		ani->Add(20102);
		ani->Add(20103);
		animations->Add(ID_ANI_WEAPON_LEFT, ani);

		ani = new CAnimation(300);
		ani->Add(20111);
		ani->Add(20112);
		ani->Add(20113);
		animations->Add(ID_ANI_WEAPON_RIGHT, ani);

		ani = new CAnimation(100);
		ani->Add(20211);
		animations->Add(ID_ANI_WEAPON_IDLE, ani);

		weapon = new CWeapon(SIMON_START_X, SIMON_START_Y);
		objects.push_back(weapon);
	}
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	for (int i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt);
	}
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		for (int i = 0; i < (int)objects.size(); i++)
		{
			objects[i]->Render();
		}
		//ghost->Render();

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
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
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
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
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

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

	CGame *game = CGame::GetInstance();
	game->Init(hWnd, hInstance);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}