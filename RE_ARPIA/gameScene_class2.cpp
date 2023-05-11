#include "stdafx.h"
#include "gameScene_class2.h"

gameScene_class2::gameScene_class2()
{
	player->SetGround(WINDOW_HEIGHT - 75);

	background = new ZeroSprite("Resource/gameScene_class/background.png");
	background->SetPosX(WINDOW_WIDTH - background->Width());

	portal1 = new ZeroSprite("Resource/Portal/Portal.png");
	portal1->SetPos(730, WINDOW_HEIGHT - 235);

	portal2 = new ZeroSprite("Resource/Portal/Portal.png");
	portal2->SetPos(-200, WINDOW_HEIGHT - 235);

	ZeroCameraMgr->SetCameraOn();

}

gameScene_class2::~gameScene_class2()
{
}

void gameScene_class2::Update(float eTime) {
	ZeroIScene::Update(eTime);
	SetCameraPos();
	PlayerUpdate(eTime);
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN) {
		if (portal1->IsOverlapped(player->playerStop)) {
			ZeroSceneMgr->ChangeScene(new gameScene());
			return;
		}
		else if (portal2->IsOverlapped(player->playerStop)) {
			ZeroSceneMgr->ChangeScene(new gameScene());
			return;
		}
	}
}

void gameScene_class2::Render() {
	ZeroIScene::Render();
	background->Render();
	portal1->Render();
	portal2->Render();
	player->Render();
	UIMgr->Render();
}

void gameScene_class2::SetCameraPos() {
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

void gameScene_class2::PlayerUpdate(float eTime) {
	player->Update(eTime);
	float playerX = player->Pos().x;
	if (playerX > WINDOW_WIDTH - player->playerStop->Width()) {
		player->SetPosX(WINDOW_WIDTH - player->playerStop->Width());
	}
	if (playerX < WINDOW_WIDTH - background->Width()) {
		player->SetPosX(WINDOW_WIDTH - background->Width());
	}
}