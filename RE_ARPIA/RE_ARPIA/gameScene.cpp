#include "stdafx.h"
#include "gameScene.h"
#include <iostream>
gameScene::gameScene()
{
	currentFloor = 1;
	player->SetGround(WINDOW_HEIGHT  - 100);
	//player->SetPos(DataMgr->data->gameS_posX, DataMgr->data->gameS_posY);
	player->SetPos(0, 0);
	DataMgr->ChangeNameToString();
	cout << DataMgr->s_name << endl;
	SetResource();
	ZeroCameraMgr->SetCameraOn();
	ZeroCameraMgr->SetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
}

gameScene::~gameScene()
{
}

void gameScene::Update(float eTime) {
	ZeroIScene::Update(eTime);	
	PlayerUpdate(eTime);
	SetCameraPos();
	PortalEffect();
	TakePortal();
}

void gameScene::Render() {
	ZeroIScene::Render();
	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
		(*iter)->Render();
	}
	for (auto iter = portalList.begin(); iter != portalList.end(); iter++) {
		(*iter)->Render();
	}
	player->Render();
}

void gameScene::SetCameraPos() {
	ZeroCameraMgr->SetPos(player->Pos().x - WINDOW_WIDTH / 2, player->Pos().y - WINDOW_HEIGHT / 2); //카메라가 플레이어를 중앙에 두고 추적

	//화면 밖에 카메라가 미치지 않도록 조정
	if (ZeroCameraMgr->Pos().x > 0)
		ZeroCameraMgr->SetPos(0, ZeroCameraMgr->Pos().y);
	if (ZeroCameraMgr->Pos().x < -2048)
		ZeroCameraMgr->SetPos(-2048, ZeroCameraMgr->Pos().y);
	if (ZeroCameraMgr->Pos().y > 0)
		ZeroCameraMgr->SetPos(ZeroCameraMgr->Pos().x, 0);
	if (ZeroCameraMgr->Pos().y < -2304)
		ZeroCameraMgr->SetPos(ZeroCameraMgr->Pos().x, -2304);
}

void gameScene::PlayerUpdate(float eTime) {
	player->Update(eTime);

	float playerStopWidth = player->playerStop->Width();
	if (player->Pos().x < -2048)
		player->SetPosX(-2048);
	if (player->Pos().x > WINDOW_WIDTH - playerStopWidth)
		player->SetPosX(WINDOW_WIDTH - playerStopWidth);
	if (player->Pos().y > WINDOW_HEIGHT + playerStopWidth + 100)
		player->SetPosY(WINDOW_HEIGHT + playerStopWidth + 100);
	if (player->Pos().y < -2304)
		player->SetPosY(-2304);
}

void gameScene::PortalEffect() {
	for (int i = 0; i < 6; i++) {
		if (i < 1) {
			if (officePortal[i]->IsOverlapped(player->playerStop)) {
				officePortal[i]->SetColorA(150);
			}
			else {
				officePortal[i]->SetColor(255);
			}
		}
		if (i < 3) {
			if (maleToiletPortal[i]->IsOverlapped(player->playerStop)) {
				maleToiletPortal[i]->SetColorA(150);
			}
			else {
				maleToiletPortal[i]->SetColorA(255);
			}
			if (femaleToiletPortal[i]->IsOverlapped(player->playerStop)) {
				femaleToiletPortal[i]->SetColorA(150);
			}	
			else {
				femaleToiletPortal[i]->SetColorA(255);
			}
		}
		if (classPortal[i]->IsOverlapped(player->playerStop)) {
			classPortal[i]->SetColorA(150);
		}
		else {
			classPortal[i]->SetColorA(255);
		}
	}
}

void gameScene::TakePortal() {
	bool office = false, maleToilet = false, femaleToilet = false, _classPortal = false;
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN && player->GetIsGround()) {
		for (int i = 0; i < 6; i++) {
			if (i < 1) {
				if (officePortal[i]->IsOverlapped(player->playerStop)) {
					office = true;
					break;
				}
			}
			if (i < 3) {
				if (maleToiletPortal[i]->IsOverlapped(player->playerStop)) {
					maleToilet = true;
					break;
				}
				else if (femaleToiletPortal[i]->IsOverlapped(player->playerStop)) {
					femaleToilet = true;
					break;
				}
			}
			if (classPortal[i]->IsOverlapped(player->playerStop)) {
				_classPortal = true;
				break;
			}
		}
	}
	if (office) {
		ZeroSceneMgr->ChangeScene(new gameScene_office());
		return;
	}
	else if (femaleToilet) {
		switch (currentFloor) {
		case 1:
			ZeroSceneMgr->ChangeScene(new gameScene_femaleToilet1());
			break;
		case 2:
			ZeroSceneMgr->ChangeScene(new gameScene_femaleToilet2());
			break;
		case 3:
			ZeroSceneMgr->ChangeScene(new gameScene_femaleToilet3());
			break;
		}
		return;
	}
	else if (maleToilet) {
		switch (currentFloor) {
		case 1:
			ZeroSceneMgr->ChangeScene(new gameScene_maleToilet1());
			break;
		case 2:
			ZeroSceneMgr->ChangeScene(new gameScene_maleToilet2());
			break;
		case 3:
			ZeroSceneMgr->ChangeScene(new gameScene_maleToilet3());
			break;
		}
		return;
	}
	else if (_classPortal) {
		switch (currentFloor) {
		case 1 :
			ZeroSceneMgr->ChangeScene(new gameScene_class1());
			break;
		case 2 :
			if (player->Pos().x < 0) {
				ZeroSceneMgr->ChangeScene(new gameScene_class2());
				break;
			}
			else if (player->Pos().x > 0) {
				ZeroSceneMgr->ChangeScene(new gameScene_class3());
				break;
			}
		}
		return;
	}
}

void gameScene::SetResource() {
	//각 층 리소스 추가
	for (int i = 1; i <= 4; i++) {
		floor[i - 1] = new ZeroSprite("Resource/gameScene/%dfloor.png", i);
		floor[i - 1]->SetPos(WINDOW_WIDTH - floor[i - 1]->Width(), -floor[i - 1]->Height() * (i - 1)); //위치 지정
		backgroundList.push_back(floor[i - 1]); //배경 이미지 로딩
	}

	//각 포탈 리소스 추가
	for (int i = 0; i < 6; i++) {
		if (i < 1) {
			officePortal[i] = new ZeroSprite("Resource/gameScene/officePortal.png");
			portalList.push_back(officePortal[i]);
		}
		if (i < 3) {
			maleToiletPortal[i] = new ZeroSprite("Resource/gameScene/maleToiletPortal.png");
			femaleToiletPortal[i] = new ZeroSprite("Resource/gameScene/femaleToiletPortal.png");
			portalList.push_back(maleToiletPortal[i]);
			portalList.push_back(femaleToiletPortal[i]);
		}
		classPortal[i] = new ZeroSprite("Resource/gameScene/classPortal.png");
		portalList.push_back(classPortal[i]);
	}
	//위치 지정
	femaleToiletPortal[0]->SetPos(673, 486);
	femaleToiletPortal[1]->SetPos(-1260, -282);
	femaleToiletPortal[2]->SetPos(-1278.8, -1050);
	
	maleToiletPortal[0]->SetPos(476, 486);
	maleToiletPortal[1]->SetPos(-1457, -282);
	maleToiletPortal[2]->SetPos(-1474.9, -1050);

	classPortal[0]->SetPos(-144, -312);
	classPortal[1]->SetPos(-914, -312);
	classPortal[2]->SetPos(-947.2, -1081.6);
	classPortal[3]->SetPos(-177.4, -1081.6);
	classPortal[4]->SetPos(105.8, -1081.6);
	classPortal[5]->SetPos(876.5, -1081.6);
	
	officePortal[0]->SetPos(-645, -1882);
	
}