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
	ZeroSprite *background;
	ZeroFont *nameFont;
	string tmpName;
};

class tutorialScene : public ZeroIScene
{
private :
	bool isDialogue;
	int index;
public:
	tutorialScene();
	~tutorialScene();
	void Update(float eTime);
	void Render();

	void FontSetting();

	SettingGenderPanel *GenderPanel;
	SettingNamePanel *NamePanel;
	ZeroFont *text[5];
	ZeroSprite *panel;
	ZeroSprite *background;
};