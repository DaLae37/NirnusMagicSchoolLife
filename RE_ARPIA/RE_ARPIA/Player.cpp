#include "stdafx.h"
#include "Player.h"
#include <iostream>
Player::Player() : groundPosY(768.0f), gravity(0.0f), isJump(false), isWalk(false), isGround(false), speed(300)
{
	statue = PlayerStatues::IDLE; //상태 지정
	
	playerWalk = new ZeroAnimation(6);
	
	if (DataMgr->data.isMale) {
		playerStop = new ZeroSprite("Resource/Player/male_stop.png");
		playerJump = new ZeroSprite("Resource/Player/male_jump.png");
		for (int i = 1; i <= 4; i++)
			playerWalk->PushSprite("Resource/Player/male_walk%d.png", i);
	}
	else {
		playerStop = new ZeroSprite("Resource/Player/female_stop.png");
		playerJump = new ZeroSprite("Resource/Player/female_jump.png");
		for (int i = 1; i <= 4; i++)
			playerWalk->PushSprite("Resource/Player/female_walk%d.png", i);
	}
	playerStop->SetScalingCenter(playerStop->Width() / 2.f, playerStop->Height() / 2.f);
	resourceList.push_back(playerStop);

	playerJump->SetScalingCenter(playerStop->Width() / 2.f, playerStop->Height() / 2.f);
	resourceList.push_back(playerJump);
	
	playerWalk->SetScalingCenter(playerStop->Width()/2.f, playerStop->Height()/2.f);
	resourceList.push_back(playerWalk); //리소스 넣기
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
	Move(eTime);
	Physics(eTime);
	SetObjectPos();
}

void Player::Render() {
	ZeroIScene::Render();
	if (statue == PlayerStatues::IDLE)
		playerStop->Render();
	else if (statue == PlayerStatues::JUMP)
		playerJump->Render();
	else if (statue == PlayerStatues::LEFT_MOVE || statue == PlayerStatues::RIGHT_MOVE)
		playerWalk->Render();
}

void Player::Move(float eTime) {
	playerWalk->Update(eTime);
	if (ZeroInputMgr->GetKey(VK_RIGHT)) {
		this->AddPosX(speed * eTime);

		if (!isJump)
			statue = PlayerStatues::RIGHT_MOVE;
		isWalk = true;		

		if (this->Scale().x > 0)
			this->SetScale(-1, 1);
	}
	else if (ZeroInputMgr->GetKey(VK_LEFT)) {
		this->AddPosX(-speed * eTime);

		if(!isJump)
			statue = PlayerStatues::LEFT_MOVE;
		isWalk = true;

		if (this->Scale().x < 0)
			this->SetScale(1, 1);
	}
	else {
		isWalk = false;
	}
	if (ZeroInputMgr->GetKey(VK_MENU) && !isJump && isGround) {
		isJump = true;
		statue = PlayerStatues::JUMP;
	}
	if(!isJump && !isWalk) {
		statue = PlayerStatues::IDLE;
	}
}

void Player::Physics(float eTime) {
	gravity += 9.8f * 1.5f;
	this->AddPosY(gravity * eTime);
	if (isJump) {
		this->AddPosY(-600 * eTime);
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
}

void Player::SetGround(float posY) {
	groundPosY = posY;
}

float Player::GetGround() {
	return groundPosY;
}

void Player::SetObjectPos() {
	for (auto iter = resourceList.begin(); iter != resourceList.end(); iter++) {
		(*iter)->SetPos(this->Pos());
		(*iter)->SetScale(this->Scale());
	}
}