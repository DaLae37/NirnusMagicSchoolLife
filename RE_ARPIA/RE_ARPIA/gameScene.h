#pragma once
#include "ZeroIScene.h"
class gameScene : public ZeroIScene
{
public:
	gameScene();
	~gameScene();
	void Update(float eTime);
	void Render();
};

