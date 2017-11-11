#include "stdafx.h"
#include "tutorialScene.h"

tutorialScene::tutorialScene()
{
	GenderPanel = new SettingGenderPanel();
	NamePanel = new SettingNamePanel();
}


tutorialScene::~tutorialScene()
{

}

void tutorialScene::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (!DataMgr->data.isSettingGender) {
		GenderPanel->Update(eTime);
	}
	else {		
		NamePanel->Update(eTime);
	}
}

void tutorialScene::Render() {
	ZeroIScene::Render();
	if (!DataMgr->data.isSettingGender) {
		GenderPanel->Render();
	}
	if (DataMgr->data.isSettingGender && !DataMgr->data.isSettingName) {
		NamePanel->Render();
	}
}

SettingGenderPanel::SettingGenderPanel() {
	male = new ZeroSprite("Resource/Player/male_stop.png");
	female = new ZeroSprite("Resource/Player/female_stop.png");
	female->SetPosX(500);
	isPopUp = false;
	isMale = false;
}

SettingGenderPanel::~SettingGenderPanel() {

}

void SettingGenderPanel::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYUP && !isPopUp) {
		if (male->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			isPopUp = true;
			isMale = true;
		}
		else if (female->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			isPopUp = true;
			isMale = false;
		}
	}
	if (isPopUp) { //팝업이 켜져있을 때
		PoPUPMgr->Update(eTime);
		if (PoPUPMgr->isSelected) {
			if (PoPUPMgr->isYes) {
				DataMgr->data.isMale = isMale;
				DataMgr->data.isSettingGender = true;
				DataMgr->Save();	
				//Yes가 선택되었으면 데이터를 저장시키고 초기화
			}
			if (!PoPUPMgr->isYes) {
				isPopUp = false;
				//No가 선택되었으면 창을 닫고 초기화
			}
			PoPUPMgr->isSelected = false;
			PoPUPMgr->isYes = false;
		}
	}
}

void SettingGenderPanel::Render() {
	ZeroIScene::Render();
	male->Render();
	female->Render();
	if (isPopUp) {
		PoPUPMgr->Render();
	}
}

SettingNamePanel::SettingNamePanel() {
	nameFont = new ZeroFont(100, "이름을 입력해 주세요");
	nameFont->SetPosX(150);
	nameFont->SetColorA(255);
	nameFont->SetColorR(0);
	nameFont->SetColorG(0);
	nameFont->SetColorB(0);
}

SettingNamePanel::~SettingNamePanel() {

}

void SettingNamePanel::Update(float eTime) {
	ZeroIScene::Update(eTime);
	nameFont->SetString(tmpName);
	int nameLength = tmpName.length();
	if (nameLength < 10) {
		for (int i = 'A'; i <= 'Z'; i++) {
			if (ZeroInputMgr->GetKey(i) == INPUTMGR_KEYDOWN) {
				stringstream s;
				if (ZeroInputMgr->GetKey(VK_LSHIFT) || ZeroInputMgr->GetKey(VK_RSHIFT))
					s << (char)(i);
				else
					s << (char)(i + 32);
				tmpName.append(s.str());
			}
		}
		for (int i = '0'; i <= '9'; i++) {
			if (ZeroInputMgr->GetKey(i) == INPUTMGR_KEYDOWN) {
				stringstream s;
				s << (char)i;
				tmpName.append(s.str());
			}
		}
		for (int i = VK_NUMPAD0; i <= VK_NUMPAD9; i++) {
			if (ZeroInputMgr->GetKey(i) == INPUTMGR_KEYDOWN) {
				stringstream s;
				s << (char)('9' - (VK_NUMPAD9 - i));
				tmpName.append(s.str());
			}
		}
		if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
			tmpName.append(" ");
		}
	}
	if (ZeroInputMgr->GetKey(VK_BACK) == INPUTMGR_KEYDOWN && tmpName.length() > 0) {
		tmpName.erase(nameLength - 1, nameLength);
	}
	if (ZeroInputMgr->GetKey(VK_RETURN) == 2) {
		strcpy(DataMgr->data.name, tmpName.c_str());
		DataMgr->data.isSettingName = true;
		DataMgr->Save();
		ZeroSceneMgr->ChangeScene(new gameScene());
		return;
	}
}

void SettingNamePanel::Render() {
	ZeroIScene::Render();
	nameFont->Render();

}