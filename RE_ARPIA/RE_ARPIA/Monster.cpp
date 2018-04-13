#include "stdafx.h"
#include "Monster.h"

Monster::Monster(int kinds) : timer(0.0f), groundPosY(768.f), gravity(0.0f), isDead(false), DeadDone(false), isAttacked(false)
{
	scaleTimer = 0.0f;
	stop = false;
	myKinds = kinds;
	if (kinds % 2 == 0)
		statue = MonsterStatues::LEFT_MOVE;
	else
		statue = MonsterStatues::RIGHT_MOVE;
	SetMonsterProfile();
}

Monster::~Monster()
{
}

void Monster::Update(float eTime) {
	ZeroIScene::Update(eTime);
	CheckIsAttacked();
	if (myKinds == 6 && !stop){
		scaleTimer += eTime;
		if (scaleTimer >= 2.0f) {
			SetGroundPos(WINDOW_HEIGHT - 52);
			stop = true;
		}
	}
	if (!isAttacked)
		MonsterMove(eTime);
	else if(!isDead && isAttacked)
		ChaseEnemy(eTime);
	Physics(eTime);
	SetObjectPos();
	Dead(eTime);
}

void Monster::Render() {
	ZeroIScene::Render();
	if (!isDead){
		if (myKinds == 6) {
			if (!stop)
				bigMove->Render();
			else
				monsterMove->Render();
		}else{
		monsterMove->Render();
		}
	}
	else
		monsterDead->Render();
}

void Monster::SetObjectPos() {
	for (auto iter = monsterList.begin(); iter != monsterList.end(); iter++) {
		(*iter)->SetPos(this->Pos());
		(*iter)->SetScale(this->Scale());
	}
}

void Monster::SetEnemy(ZeroIScene *_enemy) {
	enemy = _enemy;
}

void Monster::SetGroundPos(float pos) {
	groundPosY = pos;
}

void Monster::SetMonsterProfile() {
	//몬스터별 hp 설정
	//몬스터별 스피드 설정
	//몬스터별 리소스 설정
	monsterMove = new ZeroAnimation(4);
	bigMove = new ZeroAnimation(4);
	for (int i = 1; i <= 4; i++) {
		switch (myKinds) {
		case 0:
			monsterMove->PushSprite("Resource/Monster/blue_%d.png", i);
			hp = 100;
			power = 100;
			speed = 100;
			break;
		case 1:
			monsterMove->PushSprite("Resource/Monster/green_%d.png", i);
			hp = 200;
			power = 100;
			speed = 100;
			break;
		case 2:
			monsterMove->PushSprite("Resource/Monster/orange_%d.png", i);
			hp = 100;
			power = 150;
			speed = 100;
			break;
		case 3:
			monsterMove->PushSprite("Resource/Monster/purple_%d.png", i);
			hp = 100;
			power = 150;
			speed = 100;
			break;
		case 4:
			monsterMove->PushSprite("Resource/Monster/red_%d.png", i);
			hp = 300;
			power = 100;
			speed = 100;
			break;
		case 5:
			monsterMove->PushSprite("Resource/Monster/yellow_%d.png", i);
			hp = 50;
			power = 150;
			speed = 100;
			break;
		case 6 :
			bigMove->PushSprite("Resource/Monster/big_%d.png", i);
			monsterMove->PushSprite("Resource/Monster/green_%d.png", i);
			hp = 370;
			power = 100;
			speed = 100;
			break;
		}
	}
	monsterList.push_back(monsterMove);
	monsterMove->SetScalingCenter(monsterMove->Width() / 2, monsterMove->Height() / 2);
	//몬스터 죽는 애니메이션
	monsterDead = new ZeroAnimation(2);
	for (int i = 1; i <= 2; i++) {
		switch (myKinds) {
		case 0:
			monsterDead->PushSprite("Resource/Monster/Die/blue_%d.png", i);
			break;
		case 1:
			monsterDead->PushSprite("Resource/Monster/Die/green_%d.png", i);
			break;
		case 2:
			monsterDead->PushSprite("Resource/Monster/Die/orange_%d.png", i);
			break;
		case 3:
			monsterDead->PushSprite("Resource/Monster/Die/purple_%d.png", i);
			break;
		case 4:
			monsterDead->PushSprite("Resource/Monster/Die/red_%d.png", i);
			break;
		case 5:
			monsterDead->PushSprite("Resource/Monster/Die/yellow_%d.png", i);
			break;
		case 6:
			monsterDead->PushSprite("Resource/Monster/Die/green_%d.png", i);
			break;
		}
	}
	monsterDead->SetScalingCenter(monsterDead->Width() / 2, monsterDead->Height() / 2);
	monsterList.push_back(monsterDead);
	monsterList.push_back(bigMove);
}

void Monster::Physics(float eTime) {
	gravity += 9.8f * 1.5f;
	this->AddPosY(gravity * eTime);
	if (this->Pos().y > groundPosY - monsterMove->Height()) {
		this->Pos().y = groundPosY - monsterMove->Height();
		gravity = 0;
	}
}

void Monster::Dead(float eTime) {
	if (!isDead && this->hp <= 0){
		isDead = true;
		timer = 0.0f;
		ZeroSoundMgr->PushChannel("slime_dead", "slime_dead");
	}
	if (isDead && !DeadDone) {
		timer += eTime;
		monsterDead->SetColorA(255 - (timer * 100));
		if (timer >= 2.5f)
			DeadDone = true;
	}
}

void Monster::MonsterMove(float eTime) {
	if (myKinds == 6 && !stop)
		bigMove->Update(eTime);
	else
		monsterMove->Update(eTime);
	timer += eTime;
	if (timer >= 2.5f) {
		timer = 0.0f;
		if (this->statue == MonsterStatues::LEFT_MOVE) {
			before = MonsterStatues::LEFT_MOVE;
			this->statue = MonsterStatues::IDLE;
		}
		else if (this->statue == MonsterStatues::RIGHT_MOVE) {
			before = MonsterStatues::RIGHT_MOVE;
			this->statue = MonsterStatues::IDLE;
		}
		else if (this->statue == MonsterStatues::IDLE) {
			if (before == MonsterStatues::RIGHT_MOVE)
				this->statue = MonsterStatues::LEFT_MOVE;
			else
				this->statue = MonsterStatues::RIGHT_MOVE;
		}
	}
	else {
		if (this->statue == MonsterStatues::LEFT_MOVE) {
			this->AddPosX(-speed * eTime);
			if(this->Scale().x > 0)
				this->SetScale(-this->Scale().x, this->Scale().y);
		}
		else if (this->statue == MonsterStatues::RIGHT_MOVE) {
			this->AddPosX(speed * eTime);
			if(this->Scale().x < 0)
				this->SetScale(-this->Scale().x, this->Scale().y);
		}
	}
}

void Monster::ChaseEnemy(float eTime) {
	monsterMove->Update(eTime);
	monsterMove->SetColorR(144);

	if (!player->GetIsInvincibility()) {
		if (player->statue == PlayerStatues::ATTACK && monsterMove->IsOverlapped(player->playerAttack)) {
			player->GetDamage(GetPower());
		}
		else if ((player->statue == PlayerStatues::LEFT_MOVE || player->statue == PlayerStatues::RIGHT_MOVE) && monsterMove->IsOverlapped(player->playerWalk)) {
			player->GetDamage(GetPower());
		}
		else if (player->statue == PlayerStatues::IDLE && monsterMove->IsOverlapped(player->playerStop)) {
			player->GetDamage(GetPower());
		}
		else if (player->statue == PlayerStatues::JUMP && monsterMove->IsOverlapped(player->playerJump)) {
			player->GetDamage(GetPower());
		}
	}

	if (this->Pos().x > player->Pos().x) {
		this->AddPosX(-speed * eTime);
		this->SetScale(-1, 1);
	}
	else {
		this->AddPosX(speed * eTime);
		this->SetScale(1, 1);
	}
}

int Monster::GetPower() {
	return power;
}

void Monster::CheckIsAttacked() {
	if (!isDead && monsterMove->IsOverlapped(player->magic) && player->GetIsAttacked()) {
		isAttacked = true;
		hp -= 3;
	}
}

bool Monster::GetDeadDone() {
	return DeadDone;
}