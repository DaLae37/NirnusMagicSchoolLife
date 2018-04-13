#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroCameraManager.h"
#include "ZeroFont.h"
#include "Player.h"
#define UIMgr UI::instance()
class UI : public ZeroIScene
{
private :
	bool questOpen;
public:
	int questIndex;
	UI();
	~UI();
	void Update(float eTime);
	void Render();
	static UI *instance();
	ZeroSprite *quest;
	ZeroSprite *quests[16];
	ZeroSprite *illust[7];
	ZeroSprite *hp[2];
	ZeroSprite *mp[2];
	ZeroSprite *exp[2];
	ZeroSprite *box;

	ZeroFont *name;
};

