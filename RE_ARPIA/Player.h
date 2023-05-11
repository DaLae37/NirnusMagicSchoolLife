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

	void LoadPlayerResource(); //�÷��̾� ���� ���ҽ� �ҷ���
	void Move(float eTime);//�̵����� �Լ�
	void Attack(float eTime); //���ݰ��� �Լ�
	void Physics(float eTime); //�߷� �� ���� ���� �Լ�
	void SetObjectPos(); //��������Ʈ�� ��ġ�� Ŭ������ ���� ������
	void SetGround(float posY); //ĳ������ �׶��� ��ġ�� ���� ��) ���� �ٲ� ��
	float GetGround(); //ĳ������ �׶��� ��ġ�� ������
	void SetIsGround(bool _isGround); //Ground���θ� ����
	bool GetIsGround(); //Y���� Ground�� �ִ��� Ȯ��
	bool GetIsAttacked(); //������ �޾Ҵ��� ���� Ȯ��
	bool GetIsJump(); //���� �� ���� Ȯ��
	bool GetIsInvincibility(); //���� �������� Ȯ��
	void GetDamage(int _damage); //���ظ� ����
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