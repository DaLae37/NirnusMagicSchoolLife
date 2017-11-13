#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroAnimation.h"
#include "ZeroInputManager.h"
enum class MonsterStatues
{
	IDLE,
	LEFT_MOVE,
	RIGHT_MOVE,
	TRACE,
	ATTACKED,
};
class Monster : public ZeroIScene
{
private:
	int originHp;
	int hp;
	int myKinds;
	int speed;
	float timer;
public:
	Monster(int kinds = 0); //종류를 인자로 받음
	~Monster();
	void Update(float eTime);
	void Render();
	void SetObjectPos();
	void SetEnemy(ZeroIScene *_enemy);
	void SetMonsterProfile();

	MonsterStatues statue;

	ZeroSprite *monsterStop;
	ZeroIScene *enemy;

	list<ZeroIScene *> monsterList;
};