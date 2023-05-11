#include "stdafx.h"
#include "tutorialScene.h"

tutorialScene::tutorialScene() : isDialogue(false), index(0)
{
	if (DataMgr->data.isSettingGender && !DataMgr->data.isSettingName)
		index =5;
	panel = new ZeroSprite("Dialogues/Dialogue.png");
	panel->SetPosY(WINDOW_HEIGHT - 195);
	background = new ZeroSprite("Resource/blackbackground.png");
	GenderPanel = new SettingGenderPanel();
	NamePanel = new SettingNamePanel();
	FontSetting();
	UIMgr->illust[5]->SetPos(WINDOW_WIDTH - UIMgr->illust[5]->Width(), WINDOW_HEIGHT - UIMgr->illust[5]->Height());
}


tutorialScene::~tutorialScene()
{

}

void tutorialScene::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
		if (index != 3 && index != 5) {
			index++;
		}
	}
	if (index == 3) {
		GenderPanel->Update(eTime);
		if (DataMgr->data.isSettingGender)
			index++;
	}
	else if(index == 5)
		NamePanel->Update(eTime);
}

void tutorialScene::Render() {
	ZeroIScene::Render();
	background->Render();
	switch (index) {
	case 0:
		panel->Render();
		UIMgr->illust[5]->Render();
		text[0]->Render();
		break;
	case 1:
		panel->Render();
		UIMgr->illust[5]->Render();
		text[1]->Render();
		break;
	case 2:
		panel->Render();
		UIMgr->illust[5]->Render();
		text[2]->Render();
		break;
	case 3:
		GenderPanel->Render();
		break;
	case 4:	
		panel->Render();
		UIMgr->illust[5]->Render();
		text[3]->Render();
		break;
	case 5:
		NamePanel->Render();
		break;
	case 6:
		panel->Render();
		UIMgr->illust[5]->Render();
		text[4]->Render();
		break;
	}
}

void tutorialScene::FontSetting() {
	text[0] = new ZeroFont(40, "���� ������ : ����� �����б��� �پ��� ��ǵ� ������ �׻�\nȰ�Ⱑ ��ġ�� ������ �б��̸��� ���İ�?\n�ϸ��ʽ��� �����б�, �ϸ��ʽ�", "�߳��� ��ü B", "Font/a.ttf");
	text[1] = new ZeroFont(40, "���� ������ : �ϸ��ʽ��� ������ �ϰڴٰ�?", "�߳��� ��ü B", "Font/a.ttf");
	text[2] = new ZeroFont(40, "���� ������ : �׷��� �켱 ĳ���͸� ��������", "�߳��� ��ü B", "Font/a.ttf");
	text[3] = new ZeroFont(40, "���� ������ : �� ������ ���⿡ �̸��� ������", "�߳��� ��ü B", "Font/a.ttf");
	text[4] = new ZeroFont(40, "���� ������ : ����� �����б� �ϸ��ʽ� �پ��� ������ �ʸ� ��ٸ��� �� ����, ������ ���� ������", "�߳��� ��ü B", "Font/a.ttf");
	for (int i = 0; i < 5; i++) {
		text[i]->SetColorR(0);
		text[i]->SetColorG(0);
		text[i]->SetColorB(0);
		text[i]->SetPos(40,WINDOW_HEIGHT - 175);
	}
}

SettingGenderPanel::SettingGenderPanel() {
	male = new ZeroSprite("Resource/Illust/illust_2.png");
	male->SetPos(100, 100);
	male->SetColorA(150);
	female = new ZeroSprite("Resource/Illust/illust_1.png");
	female->SetPos(600, 100);
	female->SetColorA(150);
	isPopUp = false;
	isMale = false;
}

SettingGenderPanel::~SettingGenderPanel() {

}

void SettingGenderPanel::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (!isPopUp) {
		if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN) {
			if (male->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
				isPopUp = true;
				isMale = true;
			}
			else if (female->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
				isPopUp = true;
				isMale = false;
			}
		}
		if (male->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			male->SetColorA(255);
		}
		else {
			male->SetColorA(150);
		}
		if (female->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			female->SetColorA(255);
		}
		else {
			female->SetColorA(150);
		}
	}
	else{ //�˾��� �������� ��
		PoPUPMgr->Update(eTime);
		if (PoPUPMgr->isSelected) {
			if (PoPUPMgr->isYes) {
				DataMgr->data.isMale = isMale;
				DataMgr->data.isSettingGender = true;
				DataMgr->Save();	
				//Yes�� ���õǾ����� �����͸� �����Ű�� �ʱ�ȭ
			}
			if (!PoPUPMgr->isYes) {
				isPopUp = false;
				//No�� ���õǾ����� â�� �ݰ� �ʱ�ȭ
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
	background = new ZeroSprite("Resource/papper.png");
	background->SetPos(25, 25);
	nameFont = new ZeroFont(30, "","Riffic Free Medium", "Font/Dialogue.ttf");
	nameFont->SetPos(670, 600);
	nameFont->SetWeight(100);
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
	stringstream s;
	if (nameLength < 10) {
		for (int i = 'A'; i <= 'Z'; i++) {
			if (ZeroInputMgr->GetKey(i) == INPUTMGR_KEYDOWN) {
				if (ZeroInputMgr->GetKey(VK_LSHIFT) || ZeroInputMgr->GetKey(VK_RSHIFT))
					s << (char)(i);
				else
					s << (char)(i + 32);
				tmpName.append(s.str());
			}
		}
		for (int i = '0'; i <= '9'; i++) {
			if (ZeroInputMgr->GetKey(i) == INPUTMGR_KEYDOWN) {
				s << (char)i;
				tmpName.append(s.str());
			}
		}
		for (int i = VK_NUMPAD0; i <= VK_NUMPAD9; i++) {
			if (ZeroInputMgr->GetKey(i) == INPUTMGR_KEYDOWN) {
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
	if (ZeroInputMgr->GetKey(VK_RETURN) == INPUTMGR_KEYDOWN) {
		strcpy(DataMgr->data.name, tmpName.c_str());
		DataMgr->data.isSettingName = true;
		DataMgr->Save();
		DataMgr->ChangeNameToString();
		ZeroSceneMgr->ChangeScene(new gameScene());
		return;
	}
}

void SettingNamePanel::Render() {
	ZeroIScene::Render();
	background->Render();
	nameFont->Render();
}