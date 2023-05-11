#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#include "ZeroCameraManager.h"
#include "ZeroSceneManager.h"
#include "ZeroSoundManager.h"
#include "ZeroFont.h"

#include "gameScene_class1.h"
#include "gameScene_class2.h"
#include "gameScene_class3.h"
#include "gameScene_maleToilet1.h"
#include "gameScene_maleToilet2.h"
#include "gameScene_maleToilet3.h"
#include "gameScene_femaleToilet1.h"
#include "gameScene_femaleToilet2.h"
#include "gameScene_femaleToilet3.h"
#include "gameScene_office.h"

#include "Player.h"
class gameScene : public ZeroIScene //플레이어가 첫 스폰 되는 지점
{
private:
	bool office, maleToilet, femaleToilet, _classPortal;	
	bool isStory;
	unsigned long oColorB, mColorB, fColorB, cColorB;
	float male_sub_timer;
	float male_teacher_timer;
	float female_teacher_timer;
	int chatIndex, npcIndex;

	bool isChatting;
public:
	gameScene();
	~gameScene();

	void Update(float eTime);
	void Render();
	void SetCameraPos();
	void PlayerUpdate(float eTime);
	void SetResource();
	void TakePortal();
	void PortalEffect();
	void TurnNPC(float eTime);
	void ChatNPC();
	void SetText();
	void SetCanvas();

	ZeroSprite *panel;

	ZeroSprite *floor[4];

	ZeroSprite *classPortal[6];
	ZeroSprite *femaleToiletPortal[3];
	ZeroSprite *maleToiletPortal[3];
	ZeroSprite *officePortal[1];

	ZeroSprite *upPortal[3];
	ZeroSprite *downPortal[3];
	ZeroSprite *portal[13];

	ZeroSprite *female_teacher;
	ZeroSprite *male_teacher;
	ZeroSprite *female_sub[2];
	ZeroSprite *male_sub;

	ZeroFont *text[5][4];
	ZeroFont *storyText[5][2];
	ZeroFont *fistStoryOne;

	ZeroFont *fourStoryText[2];

	ZeroFont *sixStoryText[5];

	list<ZeroSprite*> backgroundList;
	list<ZeroSprite*> portalList;
	list<ZeroSprite*> npcList;

	int currentFloor; //현재 층을 알려줌
};

