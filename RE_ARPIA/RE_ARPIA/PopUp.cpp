#include "stdafx.h"
#include "PopUp.h"


PopUp::PopUp()
{
	popUP = new ZeroSprite("Resource/UI/popUP/POP.png");
	yes = new ZeroSprite("Resource/UI/popUP/Yes.png");
	no = new ZeroSprite("Resource/UI/popUP/No.png");
	isYes = false;
	isSelected = false;
	//이미지 위치 조정
	popUP->SetPos((WINDOW_WIDTH - popUP->Width()) / 2, (WINDOW_HEIGHT - popUP->Height()) / 2);
	yes->SetPos(popUP->Pos().x, popUP->Pos().y + popUP->Height() - yes->Height());
	no->SetPos(popUP->Pos().x + popUP->Width() - no->Width(), popUP->Pos().y + popUP->Height() - no->Height());
}


PopUp::~PopUp()
{
}

void PopUp::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN) {
		if (yes->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			isSelected = true;
			isYes = true;
		}
		if (no->IsOverlapped(ZeroInputMgr->GetClientPoint())) {
			isSelected = true;
			isYes = false;
		}
	}
}

void PopUp::Render() {
	ZeroIScene::Render();
	popUP->Render();
	yes->Render();
	no->Render();
}

PopUp* PopUp::instance() {
	static PopUp inst;
	return &inst;
}
