#include "stdafx.h"
#include "gameScene_femaleToilet2.h"

gameScene_femaleToilet2::gameScene_femaleToilet2()
{

	floor = new ZeroSprite("Resource/gameScene_toilet/floor.png");

	background = new ZeroSprite("Resource/gameScene_toilet/female_toilet.png");
	background->SetPosX(WINDOW_WIDTH - background->Width());
	portal1 = new ZeroSprite("Resource/gameScene_toilet/monster.png");
	portal1->SetPos(500, 100);
	portal2 = new ZeroSprite("Resource/gameScene_toilet/monster.png");
	portal2->SetPos(1000, 100);

	player->SetGround(WINDOW_HEIGHT - floor->Height());
	player->SetPos(-160, player->GetGround());
}

gameScene_femaleToilet2::~gameScene_femaleToilet2()
{
}

void gameScene_femaleToilet2::Update(float eTime) {
	ZeroIScene::Update(eTime);
	PlayerUpdate(eTime);
	SetCameraPos();
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

void gameScene_femaleToilet2::Render() {
	ZeroIScene::Render();
	background->Render();
	portal1->Render();
	portal2->Render();
	player->Render();
}

void gameScene_femaleToilet2::PlayerUpdate(float eTime) {
	player->Update(eTime);
	float playerX = player->Pos().x;
	if (playerX > WINDOW_WIDTH - player->playerStop->Width()) {
		player->SetPosX(WINDOW_WIDTH - player->playerStop->Width());
	}
	if (playerX < WINDOW_WIDTH - background->Width()) {
		player->SetPosX(WINDOW_WIDTH - background->Width());
	}
}

void gameScene_femaleToilet2::SetCameraPos() {
	ZeroCameraMgr->SetPos(player->Pos().x - WINDOW_WIDTH / 2, player->Pos().y - WINDOW_HEIGHT / 2); //카메라가 플레이어를 중앙에 두고 추적

																									//화면 밖에 카메라가 미치지 않도록 조정
	if (ZeroCameraMgr->Pos().x > 0)
		ZeroCameraMgr->SetPos(0, ZeroCameraMgr->Pos().y);
	if (ZeroCameraMgr->Pos().x < WINDOW_WIDTH - background->Width())
		ZeroCameraMgr->SetPos(WINDOW_WIDTH - background->Width(), ZeroCameraMgr->Pos().y);
	if (ZeroCameraMgr->Pos().y > 0)
		ZeroCameraMgr->SetPos(ZeroCameraMgr->Pos().x, 0);
	if (ZeroCameraMgr->Pos().y < 0)
		ZeroCameraMgr->SetPos(ZeroCameraMgr->Pos().x, 0);
}