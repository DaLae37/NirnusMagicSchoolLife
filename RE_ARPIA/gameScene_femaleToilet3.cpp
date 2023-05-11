#include "stdafx.h"
#include "gameScene_femaleToilet3.h"

gameScene_femaleToilet3::gameScene_femaleToilet3()
{

	floor = new ZeroSprite("Resource/gameScene_toilet/floor.png");

	background = new ZeroSprite("Resource/gameScene_toilet/female_toilet.png");
	background->SetPosX(WINDOW_WIDTH - background->Width());
	portal1 = new ZeroSprite("Resource/Portal/Portal.png");
	portal1->SetPos(-160, 540);

	player->SetGround(WINDOW_HEIGHT - floor->Height());
}

gameScene_femaleToilet3::~gameScene_femaleToilet3()
{
}

void gameScene_femaleToilet3::Update(float eTime) {
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

void gameScene_femaleToilet3::Render() {
	ZeroIScene::Render();
	background->Render();
	portal1->Render();
	player->Render();
	UIMgr->Render();
}

void gameScene_femaleToilet3::PlayerUpdate(float eTime) {
	player->Update(eTime);
	float playerX = player->Pos().x;
	if (playerX > WINDOW_WIDTH - player->playerStop->Width()) {
		player->SetPosX(WINDOW_WIDTH - player->playerStop->Width());
	}
	if (playerX < WINDOW_WIDTH - background->Width()) {
		player->SetPosX(WINDOW_WIDTH - background->Width());
	}
}

void gameScene_femaleToilet3::SetCameraPos() {
	ZeroCameraMgr->SetPos(player->Pos().x - WINDOW_WIDTH / 2, player->Pos().y - WINDOW_HEIGHT / 2 - UIMgr->box->Height()); //ī�޶� �÷��̾ �߾ӿ� �ΰ� ����

																									//ȭ�� �ۿ� ī�޶� ��ġ�� �ʵ��� ����
	if (ZeroCameraMgr->Pos().x > 0)
		ZeroCameraMgr->SetPos(0, ZeroCameraMgr->Pos().y);
	if (ZeroCameraMgr->Pos().x < WINDOW_WIDTH - background->Width())
		ZeroCameraMgr->SetPos(WINDOW_WIDTH - background->Width(), ZeroCameraMgr->Pos().y);
	if (ZeroCameraMgr->Pos().y > 0)
		ZeroCameraMgr->SetPos(ZeroCameraMgr->Pos().x, 0);
	if (ZeroCameraMgr->Pos().y < 0)
		ZeroCameraMgr->SetPos(ZeroCameraMgr->Pos().x, 0);
}