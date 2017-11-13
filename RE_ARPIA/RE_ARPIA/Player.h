#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroAnimation.h"
#include "ZeroInputManager.h"
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
	bool isJump;
	bool isWalk;
	bool isGround;
	float groundPosY;
	float gravity;
public:
	static Player *instance();

	Player();
	~Player();
	void Update(float eTime);
	void Render();

	void Move(float eTime);//이동관련 함수
	void Physics(float eTime); //중력 등 물리 관련 함수
	void SetObjectPos(); //스프라이트의 위치를 클래스의 값과 맞춰줌
	void SetGround(float posY); //캐릭터의 그라운드 위치를 설정 예) 층이 바뀔 때
	float GetGround(); //캐릭터의 그라운드 위치를 가져옴
	void SetIsGround(bool _isGround);
	bool GetIsGround();

	PlayerStatues statue;

	std::list<ZeroIScene *> resourceList;
	ZeroSprite *playerStop;	
	ZeroAnimation *playerWalk;
	ZeroSprite *playerJump;
};