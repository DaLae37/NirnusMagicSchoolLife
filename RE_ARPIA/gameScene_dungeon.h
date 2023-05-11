#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroSceneManager.h"
#include "ZeroSoundManager.h"
#include "ZeroCameraManager.h"

#include "gameScene_femaleToilet1.h"
#include "gameScene_maleToilet1.h"

#include "Player.h"
#include "Monster.h"
class gameScene_dungeon : public ZeroIScene
{
private :
	int currentFloor;
	float timer = 0.0f;
public:
	gameScene_dungeon();
	~gameScene_dungeon();
	void Update(float eTime);
	void Render();
	void PlayerUpdate(float eTime);
	void SetCameraPos();
	void TakePortal();
	void MakeEnemy();

	list<Monster*> monsterList;
	Monster *bigmon;
	ZeroSprite *background;
	ZeroSprite *portal;
	ZeroSprite *upPortal;
	ZeroSprite *downPortal;
	ZeroSprite *step;
};