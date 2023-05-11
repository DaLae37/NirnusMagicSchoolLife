#include "stdafx.h"
#include "gameScene_maleToilet3.h"

gameScene_maleToilet3::gameScene_maleToilet3()
{

	floor = new ZeroSprite("Resource/gameScene_toilet/floor.png");

	background = new ZeroSprite("Resource/gameScene_toilet/male_toilet.png");
	background->SetPosX(WINDOW_WIDTH - background->Width());
	portal1 = new ZeroSprite("Resource/Portal/Portal.png");
	portal1->SetPos(830, 540);

	player->SetGround(WINDOW_HEIGHT - floor->Height());
}

gameScene_maleToilet3::~gameScene_maleToilet3()
{
}

void gameScene_maleToilet3::Update(float eTime) {
	ZeroIScene::Update(eTime);
	PlayerUpdate(eTime);
	SetCameraPos();
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN) {
		if (portal1->IsOverlapped(player->playerStop)) {
			ZeroSceneMgr->ChangeScene(new gameScene());
			return;
		}
	}
}

void gameScene_maleToilet3::Render() {
	ZeroIScene::Render();
	background->Render();
	portal1->Render();
	player->Render();
	UIMgr->Render();
}

void gameScene_maleToilet3::PlayerUpdate(float eTime) {
	player->Update(eTime);
	float playerX = player->Pos().x;
	if (playerX > WINDOW_WIDTH - player->playerStop->Width()) {
		player->SetPosX(WINDOW_WIDTH - player->playerStop->Width());
	}
	if (playerX < WINDOW_WIDTH - background->Width()) {
		player->SetPosX(WINDOW_WIDTH - background->Width());
	}
}

void gameScene_maleToilet3::SetCameraPos() {
	ZeroCameraMgr->SetPos(player->Pos().x - WINDOW_WIDTH / 2, player->Pos().y - WINDOW_HEIGHT / 2 - UIMgr->box->Height()); //카메라가 플레이어를 중앙에 두고 추적

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