#include "stdafx.h"
#include "Player.h"
#include <iostream>
Player::Player() : gravity(0.0f), isJump(false)
{
	player = new ZeroSprite("Resource/Player/male.png");
	player->SetScale(0.5f, 0.5f);
	spriteList.push_back(player);
}

Player::~Player()
{
}

void Player::Update(float eTime) {
	ZeroIScene::Update(eTime);
	Move(eTime);
	Physics(eTime);
	SetObjectPos();
}

void Player::Render() {
	ZeroIScene::Render();
	player->Render();
}

void Player::Move(float eTime) {
	if (ZeroInputMgr->GetKey(VK_RIGHT)) {
		this->AddPosX(200 * eTime);
	}
	else if (ZeroInputMgr->GetKey(VK_LEFT)) {
		this->AddPosX(-200 * eTime);
	}
	if (ZeroInputMgr->GetKey(VK_UP) && !isJump) {
		isJump = true;
	}
}

void Player::Physics(float eTime) {
	gravity += 9.8f;
	this->AddPosY(gravity * eTime);
	if (isJump) {
		this->AddPosY(-500 * eTime);
	}
	if (this->Pos().y > 400) {
		this->Pos().y = 400;
		gravity = 0;
		isJump = false;
	}
}

void Player::SetObjectPos() {
	for (auto iter = spriteList.begin(); iter != spriteList.end(); iter++) {
		(*iter)->SetPos(this->Pos());
	}
}