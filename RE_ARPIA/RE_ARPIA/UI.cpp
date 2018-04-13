#include "stdafx.h"
#include "UI.h"

UI::UI() : questOpen(true)
{
	questIndex = 0;
	quest = new ZeroSprite("Resource/UI/quest.png");
	for (int i = 0; i < 7; i++) {
		illust[i] = new ZeroSprite("Resource/Illust/illust_%d.png", i+1);
	}
	for (int i = 0; i < 16; i++) {
		quests[i] = new ZeroSprite("Resource/UI/Quest/%d.png", i+ 1);
	}
	box = new ZeroSprite("Resource/UI/box.png");
	for (int i = 0; i < 2; i++) {
		hp[i] = new ZeroSprite("Resource/UI/hp%d.png", i + 1);
		mp[i] = new ZeroSprite("Resource/UI/mp%d.png", i + 1);
		exp[i] = new ZeroSprite("Resource/UI/exp%d.png", i + 1);
	}
	name = new ZeroFont(35, DataMgr->data.name);
}

UI::~UI()
{
}

void UI::Update(float eTime) {
	ZeroIScene::Update(eTime);
	box->SetPos(ZeroCameraMgr->Pos().x ,ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - box->Height());
	
	hp[0]->SetPos(ZeroCameraMgr->Pos().x +56, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - box->Height() / 2 - 10);
	hp[0]->SetScale(player->hp / 100.0f, 1);
	hp[1]->SetPos(ZeroCameraMgr->Pos().x + 20, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - box->Height() / 2 - 10);

	mp[0]->SetPos(ZeroCameraMgr->Pos().x + 236, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - box->Height() / 2 - 10);
	mp[0]->SetScale(player->mp / 100.0f, 1);
	mp[1]->SetPos(ZeroCameraMgr->Pos().x + 200, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - box->Height() / 2 - 10);

	exp[0]->SetPos(ZeroCameraMgr->Pos().x + 426, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - box->Height() / 2 - 10);
	exp[0]->SetScale(DataMgr->data.exp / 100.0f, 1);
	exp[1]->SetPos(ZeroCameraMgr->Pos().x + 380, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - box->Height() / 2 - 10);
	
	name->SetPos(ZeroCameraMgr->Pos().x + 700, ZeroCameraMgr->Pos().y + WINDOW_HEIGHT - box->Height() / 2 - 25);
	name->SetString(DataMgr->s_name);
	questIndex = DataMgr->data.questIndex;
	quest->SetPos(ZeroCameraMgr->Pos().x + WINDOW_WIDTH - quest->Width(), ZeroCameraMgr->Pos().y);
	for (int i = 0; i < 16; i++) {
		quests[i]->SetPos(ZeroCameraMgr->Pos().x + WINDOW_WIDTH - quests[i]->Width() - 10, ZeroCameraMgr->Pos().y + 60);
	}
	for (int i = 0; i < 7; i++) {
		illust[i]->SetPos(WINDOW_WIDTH - illust[i]->Width() + ZeroCameraMgr->Pos().x, WINDOW_HEIGHT - illust[i]->Height() + ZeroCameraMgr->Pos().y);
	}
	if (ZeroInputMgr->GetKey('Q') == INPUTMGR_KEYDOWN)
		questOpen = !questOpen;
}

void UI::Render() {
	ZeroIScene::Render();
	if(questOpen){
		quest->Render();
		if (questIndex < 16)
			quests[questIndex]->Render();
	}
	box->Render();
	for (int i = 0; i < 2; i++) {
		hp[i]->Render();
		mp[i]->Render();
		exp[i]->Render();
		name->Render();
	}
}

UI *UI::instance() {
	static UI ui;
	return &ui;
}