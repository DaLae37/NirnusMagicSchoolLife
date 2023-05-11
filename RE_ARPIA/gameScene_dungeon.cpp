#include "stdafx.h"
#include "gameScene_dungeon.h"
#include <time.h>
gameScene_dungeon::gameScene_dungeon() : currentFloor(1)
{
	ZeroSoundMgr->PauseAllChannel("dungeon");
	ZeroSoundMgr->PushChannel("dungeon", "dungeon");
	if (DataMgr->data.storyIndex == 6 && DataMgr->data.sixStoryindex >= 7) {
		bigmon = new Monster(6);
		bigmon->SetGroundPos(WINDOW_HEIGHT - 52);
		bigmon->SetPosX(50);
	}
	else {
		MakeEnemy();
	}
	player->SetGround(WINDOW_HEIGHT - 52);
	background = new ZeroSprite("Resource/gameScene_dungeon/dungeon.png");
	background->SetPosX(WINDOW_WIDTH - background->Width());
	step = new ZeroSprite("Resource/gameScene_dungeon/step.png");
	step->SetPos(-280, 425);

	portal = new ZeroSprite("Resource/Portal/Portal.png");
	portal->SetPos(-444, 555);

	upPortal = new ZeroSprite("Resource/Portal/upPortal.png");
	upPortal->SetPos(222, 555);
	downPortal = new ZeroSprite("Resource/Portal/downPortal.png");
	downPortal->SetPos(222, 266);

	ZeroCameraMgr->SetCameraOn();
}

gameScene_dungeon::~gameScene_dungeon()
{
}

void gameScene_dungeon::Update(float eTime) {
	ZeroIScene::Update(eTime);
		timer += eTime;
	if (timer >= 5.0f) {
		MakeEnemy();
		timer = 0.0f;
	}
	SetCameraPos();
	UIMgr->Update(eTime);
	PlayerUpdate(eTime);
	if (DataMgr->data.storyIndex == 5) {
		for (auto iter = monsterList.begin(); iter != monsterList.end(); iter++) {
			(*iter)->Update(eTime);
			if ((*iter)->GetDeadDone()) {
				player->exp += 5;
				DataMgr->data.questIndex++;
				delete(*iter);
				iter = monsterList.erase(iter);
				if (iter == monsterList.end())
				{
					break;
				}
			}
		}
		if (DataMgr->data.questIndex == 13) {
			DataMgr->data.storyIndex = 6;
			DataMgr->Save();
		}
	}
	else if (DataMgr->data.storyIndex == 6 && DataMgr->data.sixStoryindex >= 7) {
		bigmon->Update(eTime);
		if (bigmon->GetDeadDone()) {
			DataMgr->data.questIndex = 15;
			DataMgr->data.storyIndex = 7;
			DataMgr->Save();
		}
	}
	else {
		for (auto iter = monsterList.begin(); iter != monsterList.end(); iter++) {
			(*iter)->Update(eTime);
		}
	}
	TakePortal();
}
void gameScene_dungeon::Render() {
	ZeroIScene::Render();
	step->Render();
	background->Render();
	if (DataMgr->data.storyIndex == 6 && DataMgr->data.sixStoryindex >= 7) {
		bigmon->Render();
	}
	else {
		for (auto iter = monsterList.begin(); iter != monsterList.end(); iter++) {
			(*iter)->Render();
		}
	}
	portal->Render();
	upPortal->Render();
	downPortal->Render();
	player->Render();
	UIMgr->Render();
}

void gameScene_dungeon::PlayerUpdate(float eTime) {
	player->Update(eTime);
	float playerX = player->Pos().x;
	if (playerX > WINDOW_WIDTH - player->playerStop->Width()) {
		player->SetPosX(WINDOW_WIDTH - player->playerStop->Width());
	}
	if (playerX < WINDOW_WIDTH - background->Width()) {
		player->SetPosX(WINDOW_WIDTH - background->Width());
	}

	if (currentFloor == 2) {
		bool isXout = (player->Pos().x < step->Pos().x || player->Pos().x > step->Pos().x + step->Width());
		if (isXout) {
				currentFloor = 1;
				player->SetGround(WINDOW_HEIGHT - 52);
		}
		if (player->GetIsJump() && player->Pos().y + player->playerStop->Width() < step->Pos().y && !isXout) {
			currentFloor = 2;
			player->SetGround(step->Pos().y);
		}
		else if(player->GetIsJump() && isXout){
			currentFloor = 1;
			player->SetGround(WINDOW_HEIGHT - 52);
		}
	}
}

void gameScene_dungeon::SetCameraPos() {
	//카메라가 플레이어를 중앙에 두고 추적
	ZeroCameraMgr->SetPos(player->Pos().x - WINDOW_WIDTH / 2, player->Pos().y - WINDOW_HEIGHT / 2 - UIMgr->box->Height());

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

void gameScene_dungeon::TakePortal() {
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN) {
		if (portal->IsOverlapped(player->playerStop)) {
			ZeroSoundMgr->PauseAllChannel("dungeon");
			ZeroSoundMgr->PushChannel("school", "school");
			if (DataMgr->data.isMale) {
				player->SetPos(-220, WINDOW_HEIGHT - 65);
				ZeroSceneMgr->ChangeScene(new gameScene_maleToilet1());
				return;
			}
			else {
				player->SetPos(900, WINDOW_HEIGHT - 65);
				ZeroSceneMgr->ChangeScene(new gameScene_femaleToilet1());
				return;
			}
		}
		else if (upPortal->IsOverlapped(player->playerStop) && currentFloor == 1) {
			player->SetPosY(step->Pos().y + player->Height() + 5);
			player->SetGround(step->Pos().y);
			currentFloor++;	
		}
		else if (downPortal->IsOverlapped(player->playerStop) && currentFloor == 2) {
			player->SetGround(WINDOW_HEIGHT - 52);
			player->SetPosY(WINDOW_HEIGHT - 52);
			currentFloor--;
		}
	}
}

void gameScene_dungeon::MakeEnemy() {
	srand(time(NULL));
	int a = monsterList.size();
	for (int i = 0; i < 9 - a; i++) {
		Monster * mon = new Monster(rand() % 6);
		mon->SetGroundPos(WINDOW_HEIGHT - 52);
		mon->SetPosX(rand() % 1200 - 500);
		monsterList.push_back(mon);
	}
}