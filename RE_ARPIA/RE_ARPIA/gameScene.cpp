#include "stdafx.h"
#include "gameScene.h"
#include <iostream>
gameScene::gameScene()
{
	player = new Player();
}

gameScene::~gameScene()
{
}

void gameScene::Update(float eTime) {
	ZeroIScene::Update(eTime);
	player->Update(eTime);
	std::cout << "X : " << player->Pos().x << " Y : " << player->Pos().y << endl;
}

void gameScene::Render() {
	ZeroIScene::Render();
	player->Render();
}

