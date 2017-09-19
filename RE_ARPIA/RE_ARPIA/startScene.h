#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroSceneManager.h"
#include "DataManager.h"
class startScene : public ZeroIScene
{
public:
	startScene();
	~startScene();
	void Update(float eTime);
	void Render();
};