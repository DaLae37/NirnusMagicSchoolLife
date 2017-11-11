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
	cout << "ÀúÀåµÊ!" << endl;
	ofs.close();
}

void DataManager::Load() {
	DataField tmp;
	ifstream ifs("Data/data.ros", ios::binary);
	ifs.read((char *)&tmp, sizeof(tmp));
	data = tmp;
	cout << "ºÒ·¯¿È!" << endl;
	ifs.close();
}

void DataManager::Reset() {
	data.currentScene = 0;
		
	data.isMale = false;
	data.isSettingGender = false;
		
	data.isSettingName = false;
		
	data.currentFloor = 1;
	data.gameS_posX = 0;
	data.gameS_posY = 0;
}

void DataManager::ChangeNameToString() {
	s_name = data.name;
}

DataManager* DataManager::instance() {
	static DataManager inst;
	return &inst;
}