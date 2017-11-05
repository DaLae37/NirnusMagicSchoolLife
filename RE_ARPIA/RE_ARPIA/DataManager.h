#pragma once
#include <string>
#include <fstream>
#define DataMgr DataManager::instance()
using namespace std;
class DataField {
public :
	//Global
	int currentScene; //현재 씬의 인덱스 0 : gameScene

	//GenderSetting
	bool isMale = false; //true이면 남성 false이면 여성
	bool isSettingGender = false; //성별이 선택 되어있는지 확인하는 변수

	//NameSetting
	string name = ""; //이름
	bool isSettingName = false; //이름이 정해져 있는지 확인하는 변수

	//GameScene
	int currentFloor; //데이터 저자 시에 있던 층
	float gameS_posX, gameS_posY; //데이터 저장 시에 있던 위치

	DataField& operator=(DataField &ref) { //대입 연산자 재정의
		currentScene = ref.currentScene;

		isMale = ref.isMale;
		isSettingGender = ref.isSettingGender;

		name = ref.name;
		isSettingName = ref.isSettingName;

		currentFloor = ref.currentFloor;
		gameS_posX = ref.gameS_posX;
		gameS_posY = ref.gameS_posY;
		return *this;
	}
};
class DataManager
{
private :
	DataManager();
public:

	~DataManager();
	DataField *data = new DataField;
	void Save();
	void Load();
	void Reset();
	static DataManager* instance();
};