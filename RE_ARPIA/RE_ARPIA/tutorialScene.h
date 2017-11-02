#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"

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