#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#include "Player.h"
class gameScene : public ZeroIScene
{
public:
	gameScene();
	~gameScene();

	void Update(float eTime);
	void Render();

	Player *player;
};

