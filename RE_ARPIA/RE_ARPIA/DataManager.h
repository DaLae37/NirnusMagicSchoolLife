#pragma once
#include <string>
#include <fstream>
#define DataMgr DataManager::instance()
using namespace std;
class DataField {
public :
	bool isMale = false; //true이면 남성 false이면 여성
	bool isSettingGender = false; //성별이 선택 되어있는지 확인하는 변수

	string name = ""; //이름
	bool isSettingName = false; //이름이 정해져 있는지 확인하는 변수

	DataField& operator=(DataField &ref) { //대입 연산자 재정의
		isMale = ref.isMale;
		isSettingGender = ref.isSettingGender;

		name = ref.name;
		isSettingName = ref.isSettingName;
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