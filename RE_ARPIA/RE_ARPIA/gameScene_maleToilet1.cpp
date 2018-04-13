#include "stdafx.h"
#include "gameScene_maleToilet1.h"

gameScene_maleToilet1::gameScene_maleToilet1()
{

	floor = new ZeroSprite("Resource/gameScene_toilet/floor.png");

	background = new ZeroSprite("Resource/gameScene_toilet/male_toilet.png");
	background->SetPosX(WINDOW_WIDTH - background->Width());
	portal1 = new ZeroSprite("Resource/Portal/Portal.png");
	portal1->SetPos(830, 540);
	portal2 = new ZeroSprite("Resource/Portal/Portal.png");
	portal2->SetPos(-230, 540);

	panel = new ZeroSprite("Dialogues/Dialogue.png");
	if (DataMgr->data.storyIndex == 3) {
		thirdStoryMonster = new Monster(1);
		thirdStoryMonster->SetGroundPos(WINDOW_HEIGHT - 75);
		thirdStorytext[0] = new ZeroFont(40, "뭐야 아무것도 안 나오는걸?", "야놀자 야체 B", "Font/a.ttf");
		thirdStorytext[1] = new ZeroFont(40, "파란 선생님께 가봐야겠다", "야놀자 야체 B", "Font/a.ttf");
		for (int i = 0; i < 2; i++) {
			thirdStorytext[i]->SetColorR(0);
			thirdStorytext[i]->SetColorG(0);
			thirdStorytext[i]->SetColorB(0);
		}
	}
	if (DataMgr->data.storyIndex == 5 && DataMgr->data.fiveStoryindex == 1) {
		fiveStorytext = new ZeroFont(40, "못 보던 포탈이 생겼다 한 번 가보자", "야놀자 야체 B", "Font/a.ttf");

		fiveStorytext->SetColorR(0);
		fiveStorytext->SetColorG(0);
		fiveStorytext->SetColorB(0);
	}
	player->SetGround(WINDOW_HEIGHT - floor->Height());
}

gameScene_maleToilet1::~gameScene_maleToilet1()
{
}

void gameScene_maleToilet1::Update(float eTime) {
	ZeroIScene::Update(eTime);
	SetCameraPos();
	UIMgr->Update(eTime);
	if (DataMgr->data.storyIndex == 3) {
		player->SetObjectPos();
		panel->SetPos(ZeroCameraMgr->Pos().x, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - 195);
		for (int i = 0; i < 2; i++) {
			thirdStorytext[i]->SetPos(ZeroCameraMgr->Pos().x + 40, WINDOW_HEIGHT - 175 + ZeroCameraMgr->Pos().y);
		}
		if (DataMgr->data.thirdStoryindex == 2) {
			player->Update(eTime);
			thirdStoryMonster->Update(eTime);
			if (thirdStoryMonster->GetDeadDone()) {
				player->exp += 5;
				DataMgr->data.thirdStoryindex = 3;
			}
		}
		else {
			if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
				DataMgr->data.thirdStoryindex++;
				if (DataMgr->data.thirdStoryindex > 3) {
					DataMgr->data.storyIndex = 4;
					DataMgr->data.questIndex++;
					DataMgr->Save();
				}
			}
		}
	}
	else if (DataMgr->data.storyIndex == 5 && DataMgr->data.fiveStoryindex == 1) {
		panel->SetPos(ZeroCameraMgr->Pos().x, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - 195);
		fiveStorytext->SetPos(ZeroCameraMgr->Pos().x + 40, WINDOW_HEIGHT - 175 + ZeroCameraMgr->Pos().y);
		if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
			DataMgr->data.fiveStoryindex++;
		}
	}
	else {
		PlayerUpdate(eTime);
		if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN) {
			if (portal1->IsOverlapped(player->playerStop)) {
				ZeroSceneMgr->ChangeScene(new gameScene());
				return;
			}
			else if (portal2->IsOverlapped(player->playerStop)) {
				ZeroSoundMgr->StopAllChannel("school");
				player->SetPos(-444, WINDOW_HEIGHT - 52);
				ZeroSceneMgr->ChangeScene(new gameScene_dungeon());
				return;
			}
		}
	}
}

void gameScene_maleToilet1::Render() {
	ZeroIScene::Render();
	background->Render();
	if (DataMgr->data.thirdStoryindex != 2) {
		portal1->Render();
		if (DataMgr->data.storyIndex > 4)
			portal2->Render();
	}
	player->Render();
	UIMgr->Render();
	if (DataMgr->data.storyIndex == 3) {
		if (DataMgr->data.thirdStoryindex == 1) {
			panel->Render();
			thirdStorytext[0]->Render();
			if (DataMgr->data.isMale)
				UIMgr->illust[1]->Render();
			else
				UIMgr->illust[0]->Render();
		}
		else if (DataMgr->data.thirdStoryindex == 2) {
			thirdStoryMonster->Render();
		}
		else if (DataMgr->data.thirdStoryindex == 3) {
			panel->Render();
			thirdStorytext[1]->Render();
			if (DataMgr->data.isMale)
				UIMgr->illust[1]->Render();
			else
				UIMgr->illust[0]->Render();
		}
	}
	else if (DataMgr->data.storyIndex == 5) {
		if (DataMgr->data.fiveStoryindex == 1) {
			panel->Render();
			fiveStorytext->Render();
			if (DataMgr->data.isMale)
				UIMgr->illust[1]->Render();
			else
				UIMgr->illust[0]->Render();
		}
	}
}

void gameScene_maleToilet1::PlayerUpdate(float eTime) {
	player->Update(eTime);
	float playerX = player->Pos().x;
	if (playerX > WINDOW_WIDTH - player->playerStop->Width()) {
		player->SetPosX(WINDOW_WIDTH - player->playerStop->Width());
	}
	if (playerX < WINDOW_WIDTH - background->Width()) {
		player->SetPosX(WINDOW_WIDTH - background->Width());
	}
}

void gameScene_maleToilet1::SetCameraPos() {
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