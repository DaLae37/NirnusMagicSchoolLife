#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#include "ZeroFont.h"
#include "ZeroSceneManager.h"

#include "gameScene.h"
class SettingGenderPanel : public ZeroIScene {
public:
	SettingGenderPanel();
	~SettingGenderPanel();
	void Update(float eTime);
	void Render();
	bool isPopUp;
	bool isMale;
	ZeroSprite *male;
	ZeroSprite *female;
};

class SettingNamePanel : public ZeroIScene {
public:
	SettingNamePanel();
	~SettingNamePanel();
	void Update(float eTime);
	void Render();

	ZeroFont *nameFont;
	string tmpName;
};

class tutorialScene : public ZeroIScene
{
public:
	tutorialScene();
	~tutorialScene();
	void Update(float eTime);
	void Render();

	SettingGenderPanel *GenderPanel;
	SettingNamePanel *NamePanel;
};