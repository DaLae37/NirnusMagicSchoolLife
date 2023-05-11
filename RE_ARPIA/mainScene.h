#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"

#include "PopUp.h"
#include "DataManager.h"

#include "loadingScene.h"
#include "tutorialScene.h"
#include "gameScene.h"
class mainScene : public ZeroIScene
{
private :
	bool isPopUp;
public:
	mainScene();
	~mainScene();
	void Update(float eTime);
	void Render();
	void StartGame();
	int startIndex;
	int endIndex;
	int resetIndex;
	ZeroSprite *background;
	ZeroSprite *gameStart[3];
	ZeroSprite *gameEnd[3];
	ZeroSprite *resetData[3];
};