#include "stdafx.h"
#include "Player.h"
#include <iostream>
Player::Player() : groundPosY(768.0f), gravity(0.0f), timer(0.0f), invincibilityTimer(0.0f), hp(100.0f), mp(100.0f), exp(0.0f), HpMpTimer(0.0f),//float형 초기화
					isJump(false), isWalk(false), isGround(false), isAttack(false), isInvincibility(false), saveEnd(false),//bool형 초기화
					speed(300), level(1) //int형 초기화
{
	statue = PlayerStatues::IDLE; //상태 지정
	LoadPlayerResource();
}

Player::~Player()
{
}

Player* Player::instance() {
	static Player pl;
	return &pl;
}

void Player::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (ZeroInputMgr->GetKey(VK_ESCAPE) == INPUTMGR_KEYDOWN) {
		if (saveEnd) {
			PoPUPMgr->isSave = false;
			saveEnd = false;
		}
		else{
		PoPUPMgr->isSave = true;
		saveEnd = true;
		}
	}
	if (saveEnd) {
		PoPUPMgr->Update(eTime);
		if (PoPUPMgr->isSelected) {
			if (PoPUPMgr->isYes) {
				DataMgr->Save();
				exit(0);
				//Yes가 선택되었으면 데이터를 저장시키고 초기화
			}
			if (!PoPUPMgr->isYes) {
				saveEnd = false;
				//No가 선택되었으면 창을 닫고 초기화
			}
			PoPUPMgr->isSelected = false;
			PoPUPMgr->isYes = false;
			PoPUPMgr->isSave = false;
		}
	}
	if (!saveEnd) {
		HpMpTimer += eTime;
		if (HpMpTimer >= 3.0f) {
			hp += 5;
			mp += 5;
			if (hp > 100)
				hp = 100;
			if (mp > 100)
				mp = 100;
			HpMpTimer = 0.0f;
		}
		if (exp > 100)
			exp = 100;
		DataMgr->data.exp = exp;
		Move(eTime);
		Attack(eTime);
		Physics(eTime);
		CheckInvincibility(eTime);
	}
	if (hp <= 0) {
		ZeroSceneMgr->ChangeScene(new gameScene());
		hp = 1;
		return;
	}
}

void Player::Render() {
	ZeroIScene::Render();
	if (statue == PlayerStatues::IDLE)
		playerStop->Render();
	else if (statue == PlayerStatues::JUMP)
		playerJump->Render();
	else if (statue == PlayerStatues::LEFT_MOVE || statue == PlayerStatues::RIGHT_MOVE)
		playerWalk->Render();
	else if (statue == PlayerStatues::ATTACK) {
		playerAttack->Render();
		playerHand->Render();
	}

	if (statue == PlayerStatues::ATTACK && isAttack && timer >= 0.5f && mp > 0) {
		magic->Render();
		magicGround->Render();
		magicEffect->Render();
	}

	if (saveEnd) {
		PoPUPMgr->Render();
	}
}

void Player::Attack(float eTime) {
	if (ZeroInputMgr->GetKey(VK_LCONTROL) == INPUTMGR_KEYDOWN) {
		statue = PlayerStatues::ATTACK;
		isAttack = true;
	}

	if (statue == PlayerStatues::ATTACK && timer <= 0.5f) {
		timer += eTime;
	}

	if (ZeroInputMgr->GetKey(VK_LCONTROL) && statue == PlayerStatues::ATTACK) {
		ZeroSoundMgr->PushChannel("attack", "attack");
		playerHand->Update(eTime);
		if (this->Scale().x > 0) {
			playerHand->SetPos(this->Pos().x - 45, this->Pos().y + 45);
		}
		else {
			playerHand->SetPos(this->Pos().x - 15 + this->playerAttack->Width(), this->Pos().y + 45);
		}

		if (timer >= 0.5f) {
			mp -= (eTime * 5);

			magicEffect->Update(eTime);
			magicGround->Update(eTime);
			if (this->Scale().x > 0) {
				magicEffect->SetPos(this->Pos().x - this->playerAttack->Width() - 90, this->Pos().y + 45);
				magicGround->SetPos(magicEffect->Pos().x-8, this->Pos().y + 120);
			}
			else {
				magicEffect->SetPos(this->Pos().x + this->playerAttack->Width() + 45, this->Pos().y + 45);
				magicGround->SetPos(magicEffect->Pos().x-8, this->Pos().y + 120);
			}
			magic->SetPos(magicGround->Pos().x + magicGround->Width()/ 4, magicGround->Pos().y - 75);
		}
		if (mp < 0) {
			timer = 0.0f;
		}
	}
	else {
		ZeroSoundMgr->StopAllChannel("attack");
		isAttack = false;
		timer = 0.0f;
	}
}

void Player::Move(float eTime) {
	playerWalk->Update(eTime);
	if (ZeroInputMgr->GetKey(VK_RIGHT)) {
		if (!(statue == PlayerStatues::ATTACK)) {
			this->AddPosX(speed * eTime);

			if (!isJump)
				statue = PlayerStatues::RIGHT_MOVE;
			isWalk = true;

		}
		if (this->Scale().x > 0)
			this->SetScale(-1, 1);
	}
	else if (ZeroInputMgr->GetKey(VK_LEFT)) {
		if (!(statue == PlayerStatues::ATTACK)) {
			this->AddPosX(-speed * eTime);

			if (!isJump)
				statue = PlayerStatues::LEFT_MOVE;
			isWalk = true;
		}
		if (this->Scale().x < 0)
			this->SetScale(1, 1);
	}
	else {
		isWalk = false;
	}
	if (ZeroInputMgr->GetKey(VK_MENU) == INPUTMGR_KEYDOWN && !isJump && isGround) {
		ZeroSoundMgr->PushChannel("jump", "jump");
		isJump = true;
		statue = PlayerStatues::JUMP;
	}
	if(!isJump && !isWalk && !isAttack) {
		statue = PlayerStatues::IDLE;
	}
	SetObjectPos();
}

void Player::Physics(float eTime) {
	gravity += 9.8f * 1.5f;
	this->AddPosY(gravity * eTime);
	if (isJump) {
		this->AddPosY(-500 * eTime);
	}

	if (this->Pos().y > groundPosY - playerStop->Height()) {
		this->Pos().y = groundPosY - playerStop->Height(); 
		gravity = 0;
		isJump = false;
	}
	if (this->Pos().y == groundPosY - playerStop->Height()) {
		isGround = true;
	}
	else {
		isGround = false;
	}
	SetObjectPos();
}

void Player::SetGround(float posY) {
	groundPosY = posY;
}

float Player::GetGround() {
	return groundPosY;
}

void Player::SetIsGround(bool _isGround) {
	isGround = _isGround;
}

bool Player::GetIsGround() {
	return isGround;
}

void Player::SetObjectPos() {
	for (auto iter = resourceList.begin(); iter != resourceList.end(); iter++) {
		(*iter)->SetPos(this->Pos());
		(*iter)->SetScale(this->Scale());
	}
}

void Player::LoadPlayerResource() {
	playerWalk = new ZeroAnimation(6);
	magicEffect = new ZeroAnimation(8);
	magicGround = new ZeroAnimation(6);
	playerHand = new ZeroAnimation(6);

	if (DataMgr->data.isMale) {
		playerStop = new ZeroSprite("Resource/Player/male_stop.png");
		playerJump = new ZeroSprite("Resource/Player/male_jump.png");
		for (int i = 1; i <= 4; i++) {
			playerWalk->PushSprite("Resource/Player/male_walk%d.png", i);
			playerHand->PushSprite("Resource/Player/male_magicHand%d.png", i);
			magicGround->PushSprite("Resource/Player/male_magicGround%d.png", i);
			magicEffect->PushSprite("Resource/Player/male_effect%d.png", i);
		}
		playerAttack = new ZeroSprite("Resource/Player/male_attack.png");
		magic = new ZeroSprite("Resource/Player/male_magic.png");
	}
	else {
		playerStop = new ZeroSprite("Resource/Player/female_stop.png");
		playerJump = new ZeroSprite("Resource/Player/female_jump.png");
		for (int i = 1; i <= 4; i++) {
			playerWalk->PushSprite("Resource/Player/female_walk%d.png", i);
			playerHand->PushSprite("Resource/Player/female_magicHand%d.png", i);
			magicGround->PushSprite("Resource/Player/female_magicGround%d.png", i);
			magicEffect->PushSprite("Resource/Player/female_effect%d.png", i);
		}
		playerAttack = new ZeroSprite("Resource/Player/female_attack.png");
		magic = new ZeroSprite("Resource/Player/female_magic.png");
	}
	playerStop->SetScalingCenter(playerStop->Width() / 2.f, playerStop->Height() / 2.f);
	resourceList.push_back(playerStop);

	playerJump->SetScalingCenter(playerStop->Width() / 2.f, playerStop->Height() / 2.f);
	resourceList.push_back(playerJump);

	playerWalk->SetScalingCenter(playerStop->Width() / 2.f, playerStop->Height() / 2.f);
	resourceList.push_back(playerWalk); //리소스 넣기

	playerAttack->SetScalingCenter(playerAttack->Width() / 2.f, playerAttack->Height() / 2.f);
	resourceList.push_back(playerAttack);
}

bool Player::GetIsAttacked() {
	return (isAttack && timer >= 0.5f && mp > 0);
}

void Player::GetDamage(int _damage) {
	hp -= 5;
	isInvincibility = true;
	invincibilityTimer = 0.0f;
}

bool Player::GetIsJump() {
	return isJump;
}

bool Player::GetIsInvincibility() {
	return isInvincibility;
}

void Player::CheckInvincibility(float eTime) {
	if (isInvincibility) {
		invincibilityTimer += eTime;
		if ((int)(invincibilityTimer * 10) % 2 == 0 && (int)(invincibilityTimer * 10) > 0) {
			for (auto iter = resourceList.begin(); iter != resourceList.end(); iter++) {
				(*iter)->SetColorA(150);
			}
		}
		else {
			for (auto iter = resourceList.begin(); iter != resourceList.end(); iter++) {
				(*iter)->SetColorA(255);
			}
		}
		if (invincibilityTimer >= 1.0f) {
			isInvincibility = false;
			for (auto iter = resourceList.begin(); iter != resourceList.end(); iter++) {
				(*iter)->SetColorA(255);
			}
			invincibilityTimer = 0.0f;
		}
	}
}