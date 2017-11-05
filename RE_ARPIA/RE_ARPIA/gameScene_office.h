#pragma once
#include "ZeroIScene.h"
class gameScene_office :
	public ZeroIScene
{
public:
	gameScene_office();
	~gameScene_office();
	void Update(float eTime);
	void Render();
};

