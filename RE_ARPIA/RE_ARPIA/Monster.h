#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroAnimation.h"
#include "ZeroInputManager.h"
#include "ZeroSoundManager.h"

#include "Player.h"
enum class MonsterStatues
{
	IDLE,
	LEFT_MOVE,
	RIGHT_MOVE,
};
class Monster : public ZeroIScene
{
private:
	int hp;
	int myKinds;
	int speed;
	int power;
	float scaleTimer;
	float timer;
	float groundPosY;
	float gravity;
	bool isAttacked;
	bool isDead;
	bool DeadDone;
	bool stop;
public:
	Monster(int kinds = 0); //종류를 인자로 받음
	~Monster();
	void Update(float eTime);
	void Render();
	void SetObjectPos();
	void SetEnemy(ZeroIScene *_enemy);
	void SetMonsterProfile();
	void SetGroundPos(float pos);
	void Physics(float eTime);
	void Dead(float eTime);
	void MonsterMove(float eTime);
	void ChaseEnemy(float eTime);
	void CheckIsAttacked();

	int GetPower();
	bool GetDeadDone();

	MonsterStatues statue;
	MonsterStatues before;

	ZeroAnimation *bigMove;
	ZeroAnimation *monsterMove;
	ZeroAnimation *monsterDead;
	ZeroIScene *enemy;

	list<ZeroIScene *> monsterList;
};