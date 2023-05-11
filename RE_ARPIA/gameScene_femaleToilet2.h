#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#include "ZeroSceneManager.h"
#include "ZeroCameraManager.h"

#include "gameScene.h"
#include "gameScene_dungeon.h"
#include "Player.h"
class gameScene_femaleToilet2 : public ZeroIScene
{
public:
	gameScene_femaleToilet2();
	~gameScene_femaleToilet2();
	void Update(float eTime);
	void Render();
	void SetCameraPos();
	void PlayerUpdate(float eTime);

	ZeroSprite *background;
	ZeroSprite *floor;

	ZeroSprite *portal1;
};