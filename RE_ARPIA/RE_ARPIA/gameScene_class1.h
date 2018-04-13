#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#include "ZeroCameraManager.h"
#include "ZeroSceneManager.h"

#include "gameScene.h"

#include "Player.h"
class gameScene_class1 : public ZeroIScene
{
private :
	int firstStoryindex;
	bool isStory;
public:
	gameScene_class1();
	~gameScene_class1();
	void Update(float eTime);
	void Render();
	void SetCameraPos();
	void PlayerUpdate(float eTime);
	void SetSecondStory();

	ZeroSprite *background;
	ZeroSprite *portal1;
	ZeroSprite *portal2;

	ZeroFont *firstStoryText[2];
	ZeroFont *secondStoryText[7];
	ZeroSprite *panel;
	ZeroSprite *NPC[3];
};