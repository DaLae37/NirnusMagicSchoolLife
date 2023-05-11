#pragma once
#define Dialog Dialogue::Instance()
#include "ZeroIScene.h"
#include "ZeroFont.h"
#include <string>
#include <fstream>
#include <iostream>
class Dialogue : public ZeroIScene
{
private :
	ZeroFont *font;
	ifstream *in;
	string route;
	string startswith;
	string log;
public:
	static Dialogue *Instance();
	Dialogue();
	~Dialogue();
	void Update(float eTime);
	void Render();
	void SetRoute(char * _route);
	void SetString();
};

