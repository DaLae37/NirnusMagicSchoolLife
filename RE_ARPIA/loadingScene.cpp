#include "stdafx.h"
#include "loadingScene.h"

loadingScene::loadingScene() : timer(0.0f)
{
	loading = new ZeroAnimation(10);
	for (int i = 1; i <= 22; i++) {
		if (i == 11 || i == 12 || i == 13) {
			loading->PushSprite("Resource/Powered_by_ZeroEngine/%d.png", i);
		}		
		loading->PushSprite("Resource/Powered_by_ZeroEngine/%d.png", i);
	}
	ZeroSoundMgr->PushSound("Sound/school.mp3", "school");
	ZeroSoundMgr->PushSound("Sound/dungeon.mp3", "dungeon");
	ZeroSoundMgr->PushSound("Sound/slime_dead.mp3", "slime_dead");
	ZeroSoundMgr->PushSound("Sound/jump.wav", "jump");
	ZeroSoundMgr->PushSound("Sound/attack.wav", "attack");
	ZeroSoundMgr->PushSound("Sound/main.mp3", "main");
	ZeroSoundMgr->PushChannel("main", "main");
}

loadingScene::~loadingScene()
{
}

void loadingScene::Update(float eTime) {
	ZeroIScene::Update(eTime);
	loading->Update(eTime);
	timer += eTime;
	if (timer >= 2.5f) {
		ZeroSceneMgr->ChangeScene(new mainScene());
		return;
	}
}

void loadingScene::Render() {
	ZeroIScene::Render();
	loading->Render();
}