#pragma once
#include "ZeroIScene.h"
#include "DataManager.h"

class tutorialScene : public ZeroIScene
{
public:
	tutorialScene();
	~tutorialScene();
	void Update(float eTime);
	void Render();
};

