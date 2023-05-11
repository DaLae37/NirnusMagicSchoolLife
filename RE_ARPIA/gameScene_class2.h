#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#include "ZeroCameraManager.h"
#include "ZeroSceneManager.h"

#include "gameScene.h"

#include "Player.h"
class gameScene_class2 : public ZeroIScene
{
public:
	gameScene_class2();
	~gameScene_class2();
	void Update(float eTime);
	void Render();
	void SetCameraPos();
	void PlayerUpdate(float eTime);

	ZeroSprite *background;
	ZeroSprite *portal1;
	ZeroSprite *portal2;
};

