#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroInputManager.h"
#define PoPUPMgr PopUp::instance()
#define CONTROL_RELATIVE 50
class PopUp :
	public ZeroIScene
{
public:
	PopUp();
	~PopUp();
	void Update(float eTime);
	void Render();

	bool isYes; //Yes가 선택되었는지 아닌지를 판별
	bool isSelected; //Yes 또는 No 버튼이 눌렸는지를 판별
	bool isSave;

	static PopUp* instance();

	ZeroSprite *popUP;
	ZeroSprite *yes;
	ZeroSprite *no;

	ZeroSprite *saveExit;
};

