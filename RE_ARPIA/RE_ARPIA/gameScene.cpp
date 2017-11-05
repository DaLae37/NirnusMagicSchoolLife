#include "stdafx.h"
#include "gameScene.h"
#include <iostream>
gameScene::gameScene()
{
	player = new Player();
	currentFloor = 1;
	player->SetPos(0, 0);
	//각 층 리소스 추가
	for (int i = 1; i <= 4; i++) {
		floor[i - 1] = new ZeroSprite("Resource/gameScene/%dfloor.jpg", i);
		floor[i - 1]->SetPos(WINDOW_WIDTH - floor[i - 1]->Width(), (WINDOW_HEIGHT - floor[i - 1]->Height()) + -floor[i - 1]->Height() * (i - 1));
		backgroundList.push_back(floor[i - 1]);
	}
	ZeroCameraMgr->SetCameraOn();
	ZeroCameraMgr->SetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
}

gameScene::~gameScene()
{
}

void gameScene::Update(float eTime) {
	ZeroIScene::Update(eTime);
	player->Update(eTime);
	if (player->Pos().x < -2048)
		player->SetPosX(-2048);
	if (player->Pos().x > 1024 - player->playerStop->Width())
		player->SetPosX(1024 - player->playerStop->Width());
	ZeroCameraMgr->SetPos(player->Pos().x - WINDOW_WIDTH / 2, player->Pos().y - WINDOW_HEIGHT / 2);
	if (ZeroCameraMgr->Pos().x > 0)
		ZeroCameraMgr->SetPos(0, ZeroCameraMgr->Pos().y);
	else if (ZeroCameraMgr->Pos().x < -2048)
		ZeroCameraMgr->SetPos(-2048, ZeroCameraMgr->Pos().y);
}

void gameScene::Render() {
	ZeroIScene::Render();
	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
		(*iter)->Render();
	}
	player->Render();
}

