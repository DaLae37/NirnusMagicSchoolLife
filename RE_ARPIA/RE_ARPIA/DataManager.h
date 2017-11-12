#pragma once
#include <string>
#include <fstream>
#define DataMgr DataManager::instance()
using namespace std;
class DataField {
public :
	//Global
	int currentScene = 0; //현재 씬의 인덱스 0 : gameScene

	//GenderSetting
	bool isMale = false; //true이면 남성 false이면 여성
	bool isSettingGender = false; //성별이 선택 되어있는지 확인하는 변수

	//NameSetting
	char name[20]; //이름
	bool isSettingName = false; //이름이 정해져 있는지 확인하는 변수

	//GameScene
	int currentFloor = 0; //데이터 저자 시에 있던 층
	float gameS_posX = 0, gameS_posY = 0; //데이터 저장 시에 있던 위치

	DataField& operator=(DataField &ref) { //대입 연산자 재정의
		currentScene = ref.currentScene;

		isMale = ref.isMale;
		isSettingGender = ref.isSettingGender;

		strcpy(name, ref.name);
		isSettingName = ref.isSettingName;

		currentFloor = ref.currentFloor;
		gameS_posX = ref.gameS_posX;
		gameS_posY = ref.gameS_posY;

		return *this;
	}
};
class DataManager
{
public:
	DataManager();
	~DataManager();
	DataField data;
	string s_name;
	void Save();
	void Load();
	void ChangeNameToString();
	void Reset();
	static DataManager* instance();
};