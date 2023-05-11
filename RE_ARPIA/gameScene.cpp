#include "stdafx.h"
#include "gameScene.h"
#include <time.h>

gameScene::gameScene() : male_sub_timer(0.0f), female_teacher_timer(0.0f), male_teacher_timer(0.0f), 
						isChatting(false), office(false), maleToilet(false), femaleToilet(false), _classPortal(false), isStory(false)
{
	if (DataMgr->data.storyIndex == 1) {
		isStory = true;
	}
	SetText();
	SetResource();
	DataMgr->ChangeNameToString();
	currentFloor = DataMgr->data.currentFloor;
	
	player->SetGround(-((DataMgr->data.currentFloor - 1) * floor[DataMgr->data.currentFloor - 1]->Height()) + WINDOW_HEIGHT - 100);
	player->SetPos(DataMgr->data.gameS_posX, DataMgr->data.gameS_posY);

	ZeroCameraMgr->SetCameraOn();
	ZeroCameraMgr->SetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);

	ZeroSoundMgr->PauseAllChannel("school");
	ZeroSoundMgr->PushChannel("school", "school");
}

gameScene::~gameScene()
{
}

void gameScene::Update(float eTime) {
	ZeroIScene::Update(eTime);	
	SetCameraPos();
	SetCanvas();
	UIMgr->Update(eTime);
	if (isChatting) {
		if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
			isChatting = false;
		}
	}
	else {
		if (isStory && DataMgr->data.firstStoryindex == 1) {
			player->SetObjectPos();
			fistStoryOne->SetPos(ZeroCameraMgr->Pos().x + 40, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - 175);
			if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
				DataMgr->data.firstStoryindex++;
			}
		}
		else if (DataMgr->data.storyIndex == 4 && DataMgr->data.fourStoryindex != 1) {
			if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN  && npcIndex == 4) {
				DataMgr->data.fourStoryindex++;
				if (DataMgr->data.fourStoryindex > 3) {
					DataMgr->data.questIndex++;
					DataMgr->data.storyIndex = 5;
					DataMgr->Save();
				}
			}
		}
		else if (DataMgr->data.storyIndex == 6 && DataMgr->data.sixStoryindex != 1 && DataMgr->data.sixStoryindex < 7) {
			if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN  && npcIndex == 4) {
				DataMgr->data.sixStoryindex++;
				if (DataMgr->data.sixStoryindex == 7) {
					DataMgr->data.questIndex++;
					DataMgr->Save();
				}
			}
		}
		else {
			PlayerUpdate(eTime);
			//PortalEffect();
			TurnNPC(eTime);
			ChatNPC();
			TakePortal();
		}
	}
}

void gameScene::Render() {
	ZeroIScene::Render();
	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
		(*iter)->Render();
	}
	for (auto iter = portalList.begin(); iter != portalList.end(); iter++) {
		(*iter)->Render();
	}
	for (auto iter = npcList.begin(); iter != npcList.end(); iter++) {
		(*iter)->Render();
	}
	player->Render();
	UIMgr->Render();
	if (DataMgr->data.firstStoryindex == 1 && DataMgr->data.storyIndex == 1) {
		panel->Render();
		fistStoryOne->Render();
		if (DataMgr->data.isMale)
			UIMgr->illust[1]->Render();
		else
			UIMgr->illust[0]->Render();
	}
	if (DataMgr->data.storyIndex == 4) {
		if (npcIndex == 4) {
			if (DataMgr->data.fourStoryindex <= 3 && DataMgr->data.fourStoryindex != 1) {
				panel->Render();
				fourStoryText[DataMgr->data.fourStoryindex - 2]->Render();
				if (DataMgr->data.fourStoryindex == 2) {
					if (DataMgr->data.isMale)
						UIMgr->illust[1]->Render();
					else
						UIMgr->illust[0]->Render();
				}
				else {
					UIMgr->illust[6]->Render();
				}
			}
		}
	}
	else if (DataMgr->data.storyIndex == 6) {
		if (npcIndex == 4) {
			if (DataMgr->data.sixStoryindex <= 6 && DataMgr->data.sixStoryindex != 1) {
				panel->Render();
				sixStoryText[DataMgr->data.sixStoryindex - 2]->Render();
				if (DataMgr->data.sixStoryindex % 2 == 0 && DataMgr->data.sixStoryindex != 6) {
					if (DataMgr->data.isMale)
						UIMgr->illust[1]->Render();
					else
						UIMgr->illust[0]->Render();
				}
				else {
					UIMgr->illust[6]->Render();
				}
			}
		}
	}
	if (isChatting) {
		panel->Render();
		if (!isStory) {
			UIMgr->illust[npcIndex +2]->Render();
			text[npcIndex][chatIndex]->Render();
		}
		else {
			UIMgr->illust[npcIndex + 2]->Render();
			storyText[npcIndex][chatIndex]->Render();
		}
	}
}

void gameScene::SetCameraPos() {
	ZeroCameraMgr->SetPos(player->Pos().x - WINDOW_WIDTH / 2, player->Pos().y - WINDOW_HEIGHT / 2 - UIMgr->box->Height()); //ī�޶� �÷��̾ �߾ӿ� �ΰ� ����

	//ȭ�� �ۿ� ī�޶� ��ġ�� �ʵ��� ����
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
	if (ZeroInputMgr->GetKey(VK_UP) == INPUTMGR_KEYDOWN && player->GetIsGround()) {
		for (int i = 0; i < 3; i++) {
			if (upPortal[i]->IsOverlapped(player->playerStop)) {
				currentFloor++;
				float y = -((currentFloor - 1) * floor[i]->Height()) + WINDOW_HEIGHT - 100;
				player->SetGround(y);
				player->SetPosY(y);
				return;
			}
			if (downPortal[i]->IsOverlapped(player->playerStop)) {
				currentFloor--;
				float y = -((currentFloor - 1) * floor[i]->Height()) + WINDOW_HEIGHT - 100;
				player->SetGround(y);
				player->SetPosY(y);
				return;
			}
		}
		for (int i = 0; i < 6; i++) {
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
	DataMgr->data.currentFloor = currentFloor;
	DataMgr->data.gameS_posX = player->Pos().x;
	DataMgr->data.gameS_posY = player->Pos().y;
	if (office) {
		ZeroSceneMgr->ChangeScene(new gameScene_office());
		return;
	}
	else if (femaleToilet) {
		if (!DataMgr->data.isMale) {
			player->SetPos(-160, WINDOW_HEIGHT - 75);
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
		}
		return;
	}
	else if (maleToilet) {
		if (DataMgr->data.isMale) {
			player->SetPos(825, WINDOW_HEIGHT - 75);
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
		}
		return;
	}
	else if (_classPortal) {
		switch (currentFloor) {
		case 2 :
			if (player->Pos().x < -200)
				player->SetPos(730, WINDOW_HEIGHT - 75);
			else
				player->SetPos(-195, WINDOW_HEIGHT - 75);
			ZeroSceneMgr->ChangeScene(new gameScene_class1());
			break;
		case 3 :
			if (player->Pos().x < 0) {
				if (player->Pos().x < -200)
					player->SetPos(730, WINDOW_HEIGHT - 75);
				else
					player->SetPos(-195, WINDOW_HEIGHT - 75);
				ZeroSceneMgr->ChangeScene(new gameScene_class2());
				break;
			}
			else if (player->Pos().x > 0) {
				if (player->Pos().x > 200)
					player->SetPos(730, WINDOW_HEIGHT - 75);
				else
					player->SetPos(-195, WINDOW_HEIGHT - 75);
				ZeroSceneMgr->ChangeScene(new gameScene_class3());
				break;
			}
		}
		return;
	}
}

void gameScene::SetResource() {
	panel = new ZeroSprite("Dialogues/Dialogue.png");
	//Npc ���ҽ� �߰�
	male_teacher = new ZeroSprite("Resource/Npc/male_teacher.png");
	male_teacher->SetPos(554, -282);
	male_teacher->SetScalingCenter(male_teacher->Width() / 2, male_teacher->Height() / 2);
	npcList.push_back(male_teacher);

	female_teacher = new ZeroSprite("Resource/Npc/female_teacher.png");
	female_teacher->SetPos(340, 486);
	female_teacher->SetScalingCenter(female_teacher->Width() / 2, female_teacher->Height() / 2);
	npcList.push_back(female_teacher);

	male_sub = new ZeroSprite("Resource/Npc/male_sub1.png");
	male_sub->SetPos(-525, -267);
	male_sub->SetScalingCenter(male_sub->Width() / 2, male_sub->Height() / 2);
	npcList.push_back(male_sub);

	female_sub[0] = new ZeroSprite("Resource/Npc/female_sub1.png");
	female_sub[0]->SetPos(-460, -1035);
	npcList.push_back(female_sub[0]);

	female_sub[1] = new ZeroSprite("Resource/Npc/female_sub2.png");
	female_sub[1]->SetPos(-585, -1035);
	female_sub[1]->SetScalingCenter(female_sub[1]->Width() / 2, female_sub[1]->Height() / 2);
	female_sub[1]->SetScale(-1, 1);
	npcList.push_back(female_sub[1]);

	//�� �� ���ҽ� �߰�
	for (int i = 1; i <= 4; i++) {
		floor[i - 1] = new ZeroSprite("Resource/gameScene/%dfloor.png", i);
		floor[i - 1]->SetPos(WINDOW_WIDTH - floor[i - 1]->Width(), -floor[i - 1]->Height() * (i - 1)); //��ġ ����
		backgroundList.push_back(floor[i - 1]); //��� �̹��� �ε�
	}
	
	//�� ��Ż ���ҽ� �߰�
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
	for (int i = 0; i < 13; i++) {
		if (i < 3) {
			upPortal[i] = new ZeroSprite("Resource/Portal/upPortal.png");
			upPortal[i]->SetPos(WINDOW_WIDTH -floor[i]->Width() + 300, -((i-1) * floor[i]->Height()) -270);
			portalList.push_back(upPortal[i]);

			downPortal[i] = new ZeroSprite("Resource/Portal/downPortal.png");
			downPortal[i]->SetPos(WINDOW_WIDTH - floor[i]->Width() + 450, -(i * floor[i]->Height()) - 270);
			portalList.push_back(downPortal[i]);
		}
		portal[i] = new ZeroSprite("Resource/Portal/Portal.png");
	}
	//��ġ ����
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

void gameScene::TurnNPC(float eTime) {
	male_teacher_timer += eTime;
	female_teacher_timer += eTime;
	male_sub_timer += eTime;
	if (male_teacher_timer >= 2.5f) {
		male_teacher_timer = 0;
		if (male_teacher->Scale().x > 0)
			male_teacher->SetScale(-1, 1);
		else
			male_teacher->SetScale(1, 1);
	}
	if (female_teacher_timer >= 3.0f) {
		female_teacher_timer = 0;
		if (female_teacher->Scale().x > 0)
			female_teacher->SetScale(-1, 1);
		else
			female_teacher->SetScale(1, 1);
	}
	if (male_sub_timer >= 3.5f) {
		male_sub_timer = 0;
		if (male_sub->Scale().x > 0)
			male_sub->SetScale(-1, 1);
		else
			male_sub->SetScale(1, 1);
	}
}

void gameScene::SetText() {
	fistStoryOne = new ZeroFont(40, "���Ⱑ �ϸ��ʽ� �����б� ����\n�����Բ��� �б��� ���� ������ ����� �ϼ�����\n�ϴ� ������ ���߰ڴ�. (���� 2���� �ֽ��ϴ�)", "�߳��� ��ü B", "Font/a.ttf");
	fistStoryOne->SetColorR(0);
	fistStoryOne->SetColorG(0);
	fistStoryOne->SetColorB(0);

	text[0][0] = new ZeroFont(40, "��� �Ӹ� : ���� �� �����簡 �ɰž�", "�߳��� ��ü B", "Font/a.ttf");
	text[0][1] = new ZeroFont(40, "��� �Ӹ� : ���� �پ��� ������ ���ž�", "�߳��� ��ü B", "Font/a.ttf");
	text[0][2] = new ZeroFont(40, "��� �Ӹ� : �츮�б��� ����Ѱ� ����", "�߳��� ��ü B", "Font/a.ttf");
	text[0][3] = new ZeroFont(40, "��� �Ӹ� : ��������� ��������~!", "�߳��� ��ü B", "Font/a.ttf");

	text[1][0] = new ZeroFont(40, "��ȫ �Ӹ� : ��... ���ͷ�����", "�߳��� ��ü B", "Font/a.ttf");
	text[1][1] = new ZeroFont(40, "��ȫ �Ӹ� : �� ���� �̷� ������ ����� ����?\n���� �Ѵ� ���� �ʿ�", "�߳��� ��ü B", "Font/a.ttf");
	text[1][2] = new ZeroFont(40, "��ȫ �Ӹ� : ���� ���� ����?", "�߳��� ��ü B", "Font/a.ttf");
	text[1][3] = new ZeroFont(40, "��ȫ �Ӹ� : ���ʹ� ���� ������� ����", "�߳��� ��ü B", "Font/a.ttf");

	text[2][0] = new ZeroFont(40, "���� �Ӹ� : �۽� �ϸ��ʽ�(nirnus)�� �Ųٷ��ϸ� �����̷�", "�߳��� ��ü B", "Font/a.ttf");
	text[2][1] = new ZeroFont(40, "���� �Ӹ� : ���� �������� ����� ���̶�µ�\n���� � ���ϱ�", "�߳��� ��ü B", "Font/a.ttf");
	text[2][2] = new ZeroFont(40, "���� �Ӹ� : �����ð��� ���� ���� �ȵ�", "�߳��� ��ü B", "Font/a.ttf");
	text[2][3] = new ZeroFont(40, "���� �Ӹ� : ����~! ���ʹ�!", "�߳��� ��ü B", "Font/a.ttf");

	text[3][0] = new ZeroFont(40, "���� ������ : ���� ���ʴ� �����~", "�߳��� ��ü B", "Font/a.ttf");
	text[3][1] = new ZeroFont(40, "���� ������ : ���� ȭ��ǿ��� �̻��� �Ҹ��� �鸰�ٴ���", "�߳��� ��ü B", "Font/a.ttf");
	text[3][2] = new ZeroFont(40, "���� ������ : �����Ե� ���ʴ� ������ϴ�~", "�߳��� ��ü B", "Font/a.ttf");
	text[3][3] = new ZeroFont(40, "���� ������ : �� ���� ����", "�߳��� ��ü B", "Font/a.ttf");

	text[4][0] = new ZeroFont(40, "�Ķ� ������ : �������� �ʸ� �ϴ´�", "�߳��� ��ü B", "Font/a.ttf");
	text[4][1] = new ZeroFont(40, "�Ķ� ������ : �� �ֿ�", "�߳��� ��ü B", "Font/a.ttf");
	text[4][2] = new ZeroFont(40, "�Ķ� ������ : �ƴѰ���?", "�߳��� ��ü B", "Font/a.ttf");
	text[4][3] = new ZeroFont(40, "�Ķ� ������ : �Ҵ뿡 �°� ȯ���մϴ�", "�߳��� ��ü B", "Font/a.ttf");

	storyText[0][0] = new ZeroFont(40, "��� �Ӹ� : ������ 2���� �־�", "�߳��� ��ü B", "Font/a.ttf");
	storyText[0][1] = new ZeroFont(40, "��� �Ӹ� : ��Ż�� �б��� ���� ���ʿ��־�", "�߳��� ��ü B", "Font/a.ttf");

	storyText[1][0] = new ZeroFont(40, "��ȫ �Ӹ� : ������ 2���̾�", "�߳��� ��ü B", "Font/a.ttf");
	storyText[1][1] = new ZeroFont(40, "��ȫ �Ӹ� : ��Ż�� ���ʿ�����", "�߳��� ��ü B", "Font/a.ttf");

	storyText[2][0] = new ZeroFont(40, "���� �Ӹ� : ������ 2����", "�߳��� ��ü B", "Font/a.ttf");
	storyText[2][1] = new ZeroFont(40, "���� �Ӹ� : ��Ż�� ������", "�߳��� ��ü B", "Font/a.ttf");

	storyText[3][0] = new ZeroFont(40, "���� ������ : 2������ ������~", "�߳��� ��ü B", "Font/a.ttf");
	storyText[3][1] = new ZeroFont(40, "���� ������ : ��Ż�� �����Դϴ�~", "�߳��� ��ü B", "Font/a.ttf");

	storyText[4][0] = new ZeroFont(40, "�Ķ� ������ : ������ 2���Դϴ�", "�߳��� ��ü B", "Font/a.ttf");
	storyText[4][1] = new ZeroFont(40, "�Ķ� ������ : ��Ż�� �����Դϴ�", "�߳��� ��ü B", "Font/a.ttf");

	fourStoryText[0] = new ZeroFont(40, "������ ȭ��ǿ��� �������� ���Ծ��", "�߳��� ��ü B", "Font/a.ttf");
	fourStoryText[1] = new ZeroFont(40, "�Ķ� ������ : �����ӵ��� ������ �ٴϴ� �������ٵ�...\nȭ����� �� �� ������ �� �� �ְڴ� ?", "�߳��� ��ü B", "Font/a.ttf");

	sixStoryText[0] = new ZeroFont(40, "������ �����ӵ��� óġ �߾��","�߳��� ��ü B", "Font/a.ttf");
	sixStoryText[1] = new ZeroFont(40, "���߾� �׷��� ���� ū �������� ���� ���ߴ�?","�߳��� ��ü B", "Font/a.ttf");
	sixStoryText[2] = new ZeroFont(40, "���� ū �������̿�?","�߳��� ��ü B", "Font/a.ttf");
	sixStoryText[3] = new ZeroFont(40, "�׷� �����ӵ��� ������ �߽����� �����ٴϱ� ������\n������ ��ƾ� �Ѵܴ�.","�߳��� ��ü B", "Font/a.ttf");
	sixStoryText[4] = new ZeroFont(40, "ŷ �������� ����ַ�","�߳��� ��ü B", "Font/a.ttf");

	for (int i = 0; i < 5; i++) {
		sixStoryText[i]->SetColorR(0);
		sixStoryText[i]->SetColorG(0);
		sixStoryText[i]->SetColorB(0);
		for (int j = 0; j < 4; j++) {
			if (j < 2) {
				storyText[i][j]->SetColorR(0);
				storyText[i][j]->SetColorG(0);
				storyText[i][j]->SetColorB(0);
				
				fourStoryText[j]->SetColorR(0);
				fourStoryText[j]->SetColorG(0);
				fourStoryText[j]->SetColorB(0);
			}
			text[i][j]->SetColorR(0);
			text[i][j]->SetColorG(0);
			text[i][j]->SetColorB(0);
		}
	}
}

void gameScene::ChatNPC() {
	srand(time(NULL));
	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN && !isChatting) {
		for (auto iter = npcList.begin(); iter != npcList.end(); iter++) {
			if(player->playerStop->IsOverlapped(male_sub)){
				isChatting = true;
				npcIndex = 0;
			}
			else if (player->playerStop->IsOverlapped(female_sub[0])) {
				isChatting = true;
				npcIndex = 1;
			}
			else if (player->playerStop->IsOverlapped(female_sub[1])) {
				isChatting = true;
				npcIndex = 2;
			}
			else if (player->playerStop->IsOverlapped(female_teacher)) {
				isChatting = true;
				npcIndex = 3;
			}
			else if (player->playerStop->IsOverlapped(male_teacher)) {
				isChatting = true;
				npcIndex = 4;
			}
			if (!isStory)
				chatIndex = rand() % 4;
			else
				chatIndex = rand() % 2;
			if (DataMgr->data.storyIndex == 4) {
				isChatting = false;
				if (DataMgr->data.fourStoryindex == 1 && npcIndex == 4)
					DataMgr->data.fourStoryindex++;
			}
			else if (DataMgr->data.storyIndex == 6) {
				isChatting = false;
				if (DataMgr->data.sixStoryindex == 1 && npcIndex == 4) {
					DataMgr->data.sixStoryindex++;
				}
			}
		}
	}
}

void gameScene::SetCanvas() {
	float x = ZeroCameraMgr->Pos().x;
	float y = ZeroCameraMgr->Pos().y;
	panel->SetPos(x, WINDOW_HEIGHT - 195 + y);	
	for (int i = 0; i < 5; i++) {
		sixStoryText[i]->SetPos(x + 40, WINDOW_HEIGHT - 175 + y);
		for (int j = 0; j < 4; j++) {
			if (j < 2){
				storyText[i][j]->SetPos(x + 40, WINDOW_HEIGHT - 175 + y);
				fourStoryText[j]->SetPos(x + 40, WINDOW_HEIGHT - 175 + y);
			}
			text[i][j]->SetPos(x + 40, WINDOW_HEIGHT - 175 + y);
		}
	}
}