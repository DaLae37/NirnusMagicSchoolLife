#include "stdafx.h"
#include "Dialogue.h"

Dialogue::Dialogue()
{
	in = new ifstream(route);
	font = new ZeroFont(100,"");
}

Dialogue::~Dialogue()
{
	in->close();
}

Dialogue *Dialogue::Instance() {
	static Dialogue instance;
	return &instance;
}

void Dialogue::SetRoute(char* _route) {
	route = _route;
}

void Dialogue::SetString() {
	log = "";
	while (!in->eof()) {
		char s[1000];
		in->getline(s, 100);
	}
	font->SetString(log);
}

void Dialogue::Update(float eTime) {
	ZeroIScene::Update(eTime);
}

void Dialogue::Render() {
	ZeroIScene::Render();
}