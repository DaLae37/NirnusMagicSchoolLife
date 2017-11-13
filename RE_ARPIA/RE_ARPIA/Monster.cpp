#include "stdafx.h"
#include "Monster.h"

Monster::Monster(int kinds) : timer(0.0f)
{
	myKinds = kinds;
	statue = MonsterStatues::IDLE;
	SetMonsterProfile();
}

Monster::~Monster()
{
}

void Monster::Update(float eTime) {
	ZeroIScene::Update(eTime);
	if (this->statue == MonsterStatues::TRACE) {
		
	}
	else {
		if (this->statue == MonsterStatues::ATTACKED) {
			if (timer >= 0.5f) {
				this->statue = MonsterStatues::TRACE;
			}
		}
	}
}

void Monster::Render() {
	ZeroIScene::Render();
	if(statue == MonsterStatues::IDLE)
	monsterStop->Render();
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

void Monster::SetMonsterProfile() {
	//몬스터별 hp 설정
	switch (myKinds) {
	case 0:
		hp = 100;
		break;
	default:
		hp = 1;
		break;
	}	
	originHp = hp; //원래의 HP설정
	//몬스터별 리소스 설정
	if (myKinds == 0) {
		monsterStop = new ZeroSprite("Resource/gameScene_dungeon/monster.png");
		monsterList.push_back(monsterStop);
	}
}