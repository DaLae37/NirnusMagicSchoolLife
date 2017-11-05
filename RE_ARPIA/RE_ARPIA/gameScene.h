#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#include "ZeroCameraManager.h"

#include "Player.h"
class gameScene : public ZeroIScene //플레이어가 첫 스폰 되는 지점
{
public:
	gameScene();
	~gameScene();

	void Update(float eTime);
	void Render();

	ZeroSprite *floor[4];

	list<ZeroSprite*> backgroundList;
	int currentFloor; //현재 층을 알려줌

	Player *player;
};

