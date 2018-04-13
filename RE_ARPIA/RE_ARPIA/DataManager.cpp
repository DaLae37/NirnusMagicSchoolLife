#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}

void DataManager::Save() {
	ofstream ofs("Data/data.ros", ios::binary);
	ofs.write((char *)&data, sizeof(data));
	ofs.close();
}

void DataManager::Load() {
	DataField tmp;
	ifstream ifs("Data/data.ros", ios::binary);
	ifs.read((char *)&tmp, sizeof(tmp));
	data = tmp;
	ifs.close();
}

void DataManager::Reset() {
	data.questIndex = 0;

	for (int i = 0; i < 20; i++)
		data.name[i] = 0;

	data.storyIndex = 1;
	data.firstStoryindex = 1;
	data.secondStoryindex = 1;
	data.thirdStoryindex = 1;
	data.fourStoryindex = 1;
	data.fiveStoryindex = 1;
	data.sixStoryindex = 1;

	data.currentScene = 0;
		
	data.isMale = false;
	data.isSettingGender = false;
		
	data.isSettingName = false;
		
	data.currentFloor = 1;
	data.gameS_posX = 0;
	data.gameS_posY = 501;
}

void DataManager::ChangeNameToString() {
	s_name = data.name;
}

DataManager* DataManager::instance() {
	static DataManager inst;
	return &inst;
}