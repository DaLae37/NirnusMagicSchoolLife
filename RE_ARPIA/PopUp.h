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

	bool isYes; //Yes�� ���õǾ����� �ƴ����� �Ǻ�
	bool isSelected; //Yes �Ǵ� No ��ư�� ���ȴ����� �Ǻ�
	bool isSave;

	static PopUp* instance();

	ZeroSprite *popUP;
	ZeroSprite *yes;
	ZeroSprite *no;

	ZeroSprite *saveExit;
};

