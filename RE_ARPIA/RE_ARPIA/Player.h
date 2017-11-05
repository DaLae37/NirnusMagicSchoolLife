#pragma once
#include "ZeroIScene.h"
#include "ZeroSprite.h"
#include "ZeroAnimation.h"
#include "ZeroInputManager.h"
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
	float gravity;
	bool isJump;
	bool isWalk;
public:
	Player();
	~Player();
	void Update(float eTime);
	void Render();

	void Move(float eTime);//이동관련 함수
	void Physics(float eTime); //중력 등 물리 관련 함수
	void SetObjectPos(); //스프라이트의 위치를 클래스의 값과 맞춰줌

	PlayerStatues statue;

	std::list<ZeroIScene *> resourceList;
	ZeroSprite *playerStop;	
	ZeroAnimation *playerWalk;
	ZeroSprite *playerJump;
};