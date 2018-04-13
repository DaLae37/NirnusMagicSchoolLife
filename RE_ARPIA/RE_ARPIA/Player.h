#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroAnimation.h"
#include "ZeroInputManager.h"
#include "ZeroSoundManager.h"
#include "ZeroSceneManager.h"

#include "gameScene.h"
#define player Player::instance()
enum class PlayerStatues
{
	IDLE,
	LEFT_MOVE,
	RIGHT_MOVE,
	JUMP,
	ATTACK,
};
class Player : public ZeroIScene
{
private:	
	int speed;
	int level;
	bool isJump;
	bool isWalk;
	bool isGround;
	bool isAttack;
	bool isInvincibility;
	bool saveEnd;
	float groundPosY;
	float gravity;
	float timer;
	float HpMpTimer;
	float invincibilityTimer;
public:
	static Player *instance();

	float mp;
	float hp;
	float exp;

	Player();
	~Player();
	void Update(float eTime);
	void Render();

	void LoadPlayerResource(); //플레이어 관련 리소스 불러옴
	void Move(float eTime);//이동관련 함수
	void Attack(float eTime); //공격관련 함수
	void Physics(float eTime); //중력 등 물리 관련 함수
	void SetObjectPos(); //스프라이트의 위치를 클래스의 값과 맞춰줌
	void SetGround(float posY); //캐릭터의 그라운드 위치를 설정 예) 층이 바뀔 때
	float GetGround(); //캐릭터의 그라운드 위치를 가져옴
	void SetIsGround(bool _isGround); //Ground여부를 결정
	bool GetIsGround(); //Y값이 Ground에 있는지 확인
	bool GetIsAttacked(); //공격을 받았는지 여부 확인
	bool GetIsJump(); //점프 중 인지 확인
	bool GetIsInvincibility(); //무적 상태인지 확인
	void GetDamage(int _damage); //피해를 받음
	void CheckInvincibility(float eTime);

	PlayerStatues statue;

	std::list<ZeroIScene *> resourceList;
	ZeroSprite *playerStop;	
	ZeroSprite *playerJump;
	ZeroSprite *playerAttack;
	ZeroSprite *magic;

	ZeroAnimation *playerWalk;
	ZeroAnimation *playerHand;
	ZeroAnimation *magicEffect;
	ZeroAnimation *magicGround;
};