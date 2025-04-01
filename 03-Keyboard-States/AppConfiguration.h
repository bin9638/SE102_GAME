#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>

// BAT
#define BAT_START_X 320.0f
#define BAT_START_Y 100.0f
#define BAT_START_VX 0.05f 
#define BAT_START_VY 0.05f
#define BAT_DELTA_Y 10
#define BAT_ANI_FLY_LEFT 20
#define BAT_ANI_FLY_RIGHT 21

// MARIO
#define MARIO_START_X 10.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.1f
#define MARIO_START_VY 0.1f
#define MARIO_WIDTH 14 

// GHOST
#define GHOST_START_X 10.0f
#define GHOST_START_Y 200.0f
#define GHOST_START_VX 0.1f
#define GHOST_START_VY 0.1f
#define GHOST_WIDTH 16
#define GHOST_ANI_GO_LEFT 30
#define GHOST_ANI_GO_RIGHT 31

// Random
//std::mt19937 rd(std::chrono::steady_clock::now().time_since_epoch().count());
//
//int RandDirection() {
//	if (rd() % 2 == 0) return -1;
//	return 1;
//}


// SIMON
#define SIMON_START_X 200.0f
#define SIMON_START_Y 10.0f