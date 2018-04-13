#pragma once
#include "ZeroAnimation.h"
#include "ZeroSceneManager.h"
#include "ZeroSoundManager.h"

#include "mainScene.h"
class loadingScene : public ZeroIScene
{
public:
	loadingScene();
	~loadingScene();
	void Update(float eTime);
	void Render();	

	float timer;

	ZeroAnimation *loading;
};