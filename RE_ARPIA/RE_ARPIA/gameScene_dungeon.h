#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroSceneManager.h"

#include "Player.h"
#include "Monster.h"
class gameScene_dungeon : public ZeroIScene
{
public:
	gameScene_dungeon();
	~gameScene_dungeon();
	void Update(float eTime);
	void Render();
	Monster *mon;
};