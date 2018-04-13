#include "stdafx.h"
#include "PopUp.h"


PopUp::PopUp()
{
	saveExit = new ZeroSprite("Resource/UI/popUP/save_exit.png");
	popUP = new ZeroSprite("Resource/UI/popUP/select.png");
	yes = new ZeroSprite("Resource/UI/popUP/Yes.png");
	no = new ZeroSprite("Resource/UI/popUP/No.png");
	isYes = false;
	isSelected = false;
	isSave = false;
	//이미지 위치 조정
	saveExit->SetPos((WINDOW_WIDTH - saveExit->Width()) / 2, (WINDOW_HEIGHT - saveExit->Height()) / 2);
	popUP->SetPos((WINDOW_WIDTH - popUP->Width()) / 2, (WINDOW_HEIGHT - popUP->Height()) / 2);
	yes->SetPos(popUP->Pos().x + 10, popUP->Pos().y + popUP->Height() - yes->Height() - 10);
	no->SetPos(popUP->Pos().x + popUP->Width() - no->Width() - 10, popUP->Pos().y + popUP->Height() - no->Height() - 10);
}


PopUp::~PopUp()
{
}

void PopUp::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (yes->IsOverlapped(ZeroInputMgr->GetClientPoint()))
		yes->SetColorA(150);	
	else
		yes->SetColorA(255);

	if (no->IsOverlapped(ZeroInputMgr->GetClientPoint()))
		no->SetColorA(150);
	else
		no->SetColorA(255);
	float x = ZeroCameraMgr->Pos().x;
	float y = ZeroCameraMgr->Pos().y;
	if(isSave){
	saveExit->SetPos((WINDOW_WIDTH - saveExit->Width()) / 2 + x, (WINDOW_HEIGHT - saveExit->Height()) / 2 + y);
	popUP->SetPos((WINDOW_WIDTH - popUP->Width()) / 2 + x, (WINDOW_HEIGHT - popUP->Height()) / 2 + y);
	yes->SetPos(popUP->Pos().x + 10, popUP->Pos().y + popUP->Height() - yes->Height() - 10);
	no->SetPos(popUP->Pos().x + popUP->Width() - no->Width() - 10, popUP->Pos().y + popUP->Height() - no->Height() - 10);
	}
	else {
		popUP->SetPos((WINDOW_WIDTH - popUP->Width()) / 2, (WINDOW_HEIGHT - popUP->Height()) / 2);
		yes->SetPos(popUP->Pos().x + 10, popUP->Pos().y + popUP->Height() - yes->Height() - 10);
		no->SetPos(popUP->Pos().x + popUP->Width() - no->Width() - 10, popUP->Pos().y + popUP->Height() - no->Height() - 10);
	}
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
	if (isSave)
		saveExit->Render();
	else
		popUP->Render();
	yes->Render();
	no->Render();
}

PopUp* PopUp::instance() {
	static PopUp inst;
	return &inst;
}
