#include "stdafx.h"
#include "mainScene.h"

mainScene::mainScene() : isPopUp(false)
{
	startIndex = 0;
	endIndex = 0;
	resetIndex = 0;
	for (int i = 0; i < 3; i++) {
		gameStart[i] = new ZeroSprite("Resource/mainScene/start%d.png", i + 1);
		gameStart[i]->SetPos(150, 400);
		gameEnd[i] = new ZeroSprite("Resource/mainScene/end%d.png", i + 1);
		gameEnd[i]->SetPos(150, 600);
		resetData[i] = new ZeroSprite("Resource/mainScene/reset%d.png", i + 1);
		resetData[i]->SetPos(150, 500);
	}

	background = new ZeroSprite("Resource/mainScene/mainScene.jpg");
}

mainScene::~mainScene() {

}

void mainScene::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYON && gameStart[1]->IsOverlapped(ZeroInputMgr->GetClientPoint()))
		startIndex = 2;
	else if (gameStart[0]->IsOverlapped(ZeroInputMgr->GetClientPoint()))
		startIndex = 1;
	else
		startIndex = 0;

	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYON && gameEnd[1]->IsOverlapped(ZeroInputMgr->GetClientPoint()))
		endIndex = 2;
	else if (gameEnd[0]->IsOverlapped(ZeroInputMgr->GetClientPoint()))
		endIndex = 1;
	else
		endIndex = 0;

	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYON && resetData[1]->IsOverlapped(ZeroInputMgr->GetClientPoint()))
		resetIndex = 2;
	else if (resetData[0]->IsOverlapped(ZeroInputMgr->GetClientPoint()))
		resetIndex = 1;
	else
		resetIndex = 0;
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN && !isPopUp) {
		if (gameStart[startIndex]->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			StartGame();
			return;
		}
		else if (gameEnd[endIndex]->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			exit(0);
		}
		else if (resetData[resetIndex]->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			isPopUp = true;
		}
	}

	if (isPopUp) { //팝업이 켜져있을 때
		PoPUPMgr->Update(eTime);
		if (PoPUPMgr->isSelected) {
			if (PoPUPMgr->isYes) {
				DataMgr->Reset();
				DataMgr->Save();
				PoPUPMgr->isSelected = false;
				PoPUPMgr->isYes = false;
				ZeroSoundMgr->PopChannel("main");
				ZeroSceneMgr->ChangeScene(new loadingScene());
				return;
				//Yes가 선택되었으면 데이터를 초기화 시키고 로딩 화면으로
			}
			if (!PoPUPMgr->isYes) {
				PoPUPMgr->isSelected = false;
				PoPUPMgr->isYes = false;
				isPopUp = false;
				//No가 선택되었으면 창을 닫고 초기화
			}
		}
	}
}

void mainScene::Render() {
	ZeroIScene::Render();
	background->Render();
	gameStart[startIndex]->Render();
	gameEnd[endIndex]->Render();
	resetData[resetIndex]->Render();
	if (isPopUp)
		PoPUPMgr->Render();
}

void mainScene::StartGame() {
	ZeroSoundMgr->PauseAllChannel("main");
	if (!DataMgr->data.isSettingGender || !DataMgr->data.isSettingName)
		ZeroSceneMgr->ChangeScene(new tutorialScene());
	else {
		switch (DataMgr->data.currentScene) {
		case 0:
			ZeroSceneMgr->ChangeScene(new gameScene());
			break;
		}
	}
}