#include "stdafx.h"
#include "gameScene_class1.h"

gameScene_class1::gameScene_class1() : isStory(false)
{
	NPC[0] = new ZeroSprite("Resource/NPC/female_sub1.png");
	NPC[1] = new ZeroSprite("Resource/NPC/female_sub2.png");
	NPC[2] = new ZeroSprite("Resource/NPC/male_sub1.png");
	for (int i = 0; i < 3; i++) {
		NPC[i]->SetPos(300 + (i - 1) * 100, WINDOW_HEIGHT - 242);
	}
	panel = new ZeroSprite("Dialogues/Dialogue.png");
	
	if (DataMgr->data.firstStoryindex == 2) {
		isStory = true;
		firstStoryText[0] = new ZeroFont(40, "���Ⱑ ������ ���� ��Ȱ�� ���̱���\n���� �������� ������ �����̳�...", "�߳��� ��ü B", "Font/a.ttf");
		firstStoryText[1] = new ZeroFont(40, "(���� �ֵ��� �����ִ� ���� ���ϱ� �ѹ� ������)", "�߳��� ��ü B", "Font/a.ttf");
		for (int i = 0; i < 3; i++) {
			if (i < 2) {
				firstStoryText[i]->SetColorR(0);
				firstStoryText[i]->SetColorG(0);
				firstStoryText[i]->SetColorB(0);
			}
			
		}
		firstStoryindex = DataMgr->data.firstStoryindex;
	}
	if (DataMgr->data.storyIndex == 2) {
		isStory = true;
		SetSecondStory();
	}
	player->SetGround(WINDOW_HEIGHT - 75);

	background = new ZeroSprite("Resource/gameScene_class/background.png");
	background->SetPosX(WINDOW_WIDTH - background->Width());

	portal1 = new ZeroSprite("Resource/Portal/Portal.png");
	portal1->SetPos(730, WINDOW_HEIGHT - 235);

	portal2 = new ZeroSprite("Resource/Portal/Portal.png");
	portal2->SetPos(-200, WINDOW_HEIGHT - 235);

	ZeroCameraMgr->SetCameraOn();
	ZeroCameraMgr->SetScreen(WINDOW_WIDTH, WINDOW_HEIGHT);
}

gameScene_class1::~gameScene_class1()
{
}

void gameScene_class1::Update(float eTime) {
	ZeroIScene::Update(eTime);
	SetCameraPos();
	UIMgr->Update(eTime);
	if (isStory && (DataMgr->data.firstStoryindex == 2 || DataMgr->data.firstStoryindex == 3)) {
		player->SetObjectPos();
		panel->SetPos(ZeroCameraMgr->Pos().x, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - 195);
		for (int i = 0; i < 2; i++) {
			firstStoryText[i]->SetPos(ZeroCameraMgr->Pos().x + 40, WINDOW_HEIGHT - 175 + ZeroCameraMgr->Pos().y);
		}
		if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
			DataMgr->data.firstStoryindex++;
			if (DataMgr->data.firstStoryindex >= 4) {
				DataMgr->data.storyIndex = 2;
				SetSecondStory();
				DataMgr->data.questIndex++;
				DataMgr->Save();
			}
		}
	}
	else if (isStory && (DataMgr->data.secondStoryindex == 1 || DataMgr->data.secondStoryindex == 2 || DataMgr->data.secondStoryindex == 3 || DataMgr->data.secondStoryindex == 4 || DataMgr->data.secondStoryindex == 5 || DataMgr->data.secondStoryindex == 6 || DataMgr->data.secondStoryindex == 7 || DataMgr->data.secondStoryindex == 8)) {
		if((DataMgr->data.secondStoryindex ==1))
			PlayerUpdate(eTime);
		panel->SetPos(ZeroCameraMgr->Pos().x, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - 195);
		for (int i = 0; i < 7; i++) {
			secondStoryText[i]->SetPos(ZeroCameraMgr->Pos().x + 40, WINDOW_HEIGHT - 175 + ZeroCameraMgr->Pos().y);
		}
		if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
			if (DataMgr->data.secondStoryindex == 1) {
				for (int i = 0; i < 3; i++) {
					if (NPC[i]->IsOverlapped(player->playerStop)) {
						DataMgr->data.secondStoryindex++;
					}
				}
			}
			else {
				DataMgr->data.secondStoryindex++;
				if (DataMgr->data.secondStoryindex > 8) {
					DataMgr->data.storyIndex = 3;
					isStory = false;
					DataMgr->data.questIndex++;
					DataMgr->Save();
				}
			}
		}
	}
	if (!isStory) {
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
}

void gameScene_class1::Render() {
	ZeroIScene::Render();
	background->Render();
	if (DataMgr->data.storyIndex == 1 || DataMgr->data.storyIndex == 2 || DataMgr->data.storyIndex == 3) {
		for (int i = 0; i < 3; i++) {
			NPC[i]->Render();
		}
	}
	portal1->Render();
	portal2->Render();
	player->Render();
	UIMgr->Render();
	if (DataMgr->data.storyIndex == 1) {
		if (DataMgr->data.firstStoryindex <= 3){
			panel->Render();
			firstStoryText[DataMgr->data.firstStoryindex - 2]->Render();
			if (DataMgr->data.isMale)
				UIMgr->illust[1]->Render();
			else
				UIMgr->illust[0]->Render();
		}
	}
	else if (DataMgr->data.storyIndex == 2) {
		if (DataMgr->data.secondStoryindex >= 2) {
			panel->Render();
			secondStoryText[DataMgr->data.secondStoryindex - 2]->Render();
			if(DataMgr->data.secondStoryindex <7)
				UIMgr->illust[DataMgr->data.secondStoryindex % 3 + 2]->Render();
			else {
				if (DataMgr->data.isMale)
					UIMgr->illust[1]->Render();
				else
					UIMgr->illust[0]->Render();
			}
		}
	}
}

void gameScene_class1::SetCameraPos() {
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

void gameScene_class1::PlayerUpdate(float eTime) {
	player->Update(eTime);
	float playerX = player->Pos().x;
	if (playerX > WINDOW_WIDTH - player->playerStop->Width()) {
		player->SetPosX(WINDOW_WIDTH - player->playerStop->Width());
	}
	if (playerX < WINDOW_WIDTH - background->Width()) {
		player->SetPosX(WINDOW_WIDTH - background->Width());
	}
}

void gameScene_class1::SetSecondStory() {
	secondStoryText[0] = new ZeroFont(40, "�۽� ���� 1�� ȭ��ǿ���\n���������� ��ü ���Ͱ� ���´ٴ� �ҹ��� �ִ�", "�߳��� ��ü B", "Font/a.ttf");
	secondStoryText[1] = new ZeroFont(40, "���� �׷� �ҹ��� ��� �־� �������̰���", "�߳��� ��ü B", "Font/a.ttf");
	secondStoryText[2] = new ZeroFont(40, "��¥ ��ϱ� �װ� �ѹ� ����", "�߳��� ��ü B", "Font/a.ttf");
	secondStoryText[3] = new ZeroFont(40, "�������ΰ� �� �ƴϱ� �� �� �ž�.", "�߳��� ��ü B", "Font/a.ttf");
	secondStoryText[4] = new ZeroFont(40, "���� ������ �������� �׷���?", "�߳��� ��ü B", "Font/a.ttf");
	secondStoryText[5] = new ZeroFont(40, "�� �׷��ŵ�!!!", "�߳��� ��ü B", "Font/a.ttf");
	secondStoryText[6] = new ZeroFont(40, "(��¥���� ��¥���� �ñ��ѵ� �ѹ� ȭ��ǿ� ������)", "�߳��� ��ü B", "Font/a.ttf");
	for (int i = 0; i < 7; i++) {
		secondStoryText[i]->SetColorR(0);
		secondStoryText[i]->SetColorG(0);
		secondStoryText[i]->SetColorB(0);
	}
}