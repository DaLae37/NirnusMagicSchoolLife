#include "stdafx.h"
#include "gameScene_femaleToilet1.h"

gameScene_femaleToilet1::gameScene_femaleToilet1()
{
	player->SetGround(400);
	portal1 = new ZeroSprite("Resource/gameScene_toilet/monster.png");
	portal1->SetPos(500, 100);
	portal2 = new ZeroSprite("Resource/gameScene_toilet/monster.png");
	portal2->SetPos(1000, 100);
}

gameScene_femaleToilet1::~gameScene_femaleToilet1()
{
}

void gameScene_femaleToilet1::Update(float eTime) {
	ZeroIScene::Update(eTime);
	player->Update(eTime);
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN) {
		if (portal1->IsOverlapped(player->playerStop)) {
			ZeroSceneMgr->ChangeScene(new gameScene());
			return;
		}
		else if (portal2->IsOverlapped(player->playerStop)) {
			ZeroSceneMgr->ChangeScene(new gameScene_dungeon());
			return;
		}
	}
}

void gameScene_femaleToilet1::Render() {
	ZeroIScene::Render();
	portal1->Render();
	portal2->Render();
	player->Render();
}