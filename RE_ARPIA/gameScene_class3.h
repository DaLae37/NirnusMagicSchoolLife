#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#include "ZeroCameraManager.h"
#include "ZeroSceneManager.h"

#include "gameScene.h"

#include "Player.h"
class gameScene_class3 : public ZeroIScene
{
public:
	gameScene_class3();
	~gameScene_class3();
	void Update(float eTime);
	void Render();
	void SetCameraPos();
	void PlayerUpdate(float eTime);

	ZeroSprite *background;
	ZeroSprite *portal1;
	ZeroSprite *portal2;
};

