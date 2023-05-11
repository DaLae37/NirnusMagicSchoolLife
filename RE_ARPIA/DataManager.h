#pragma once
#include <string>
#include <fstream>
#define DataMgr DataManager::instance()
using namespace std;
class DataField {
public :
	//UI
	int questIndex = 0;
	//Story
	int storyIndex = 1;
	int firstStoryindex = 1;
	int secondStoryindex = 1;
	int thirdStoryindex = 1;
	int fourStoryindex = 1;
	int fiveStoryindex = 1;
	int sixStoryindex = 1;
	//Global
	int currentScene = 0; //���� ���� �ε��� SceneIndex.txt����

	//GenderSetting
	bool isMale = false; //true�̸� ���� false�̸� ����
	bool isSettingGender = false; //������ ���� �Ǿ��ִ��� Ȯ���ϴ� ����

	//NameSetting
	char name[20] = { 0,}; //�̸�
	bool isSettingName = false; //�̸��� ������ �ִ��� Ȯ���ϴ� ����

	//GameScene
	int currentFloor = 1; //������ ���� �ÿ� �ִ� ��
	float gameS_posX = 0, gameS_posY = 501; //������ ���� �ÿ� �ִ� ��ġ

	//Player
	int level;
	float exp;
	DataField& operator=(DataField &ref) { //���� ������ ������
		questIndex = ref.questIndex;

		storyIndex = ref.storyIndex;
		firstStoryindex = ref.firstStoryindex;
		secondStoryindex = ref.secondStoryindex;
		thirdStoryindex = ref.thirdStoryindex;
		fourStoryindex = ref.fourStoryindex;
		fiveStoryindex = ref.fiveStoryindex;
		sixStoryindex = ref.sixStoryindex;

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