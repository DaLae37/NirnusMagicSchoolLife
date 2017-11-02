#include "stdafx.h"
#include "DataManager.h"
#include <iostream>
DataManager::DataManager()
{
	Reset();
	Load();
}

DataManager::~DataManager()
{
}

void DataManager::Save() {
	ofstream ofs("Data/data.ros", ios::binary);
	ofs.write((char *)&data, sizeof(data));
	cout << "data : " << data->isMale << endl;
	ofs.close();
}

void DataManager::Load() {
	DataField tmp;
	ifstream ifs("Data/data.ros", ios::binary);
	ifs.read((char *)&tmp, sizeof(tmp));
	*data = tmp;
	ifs.close();
}

void DataManager::Reset() {
	data->isMale = false;
	data->isSettingGender = false;

	data->name = "";
	data->isSettingName = false;
}

DataManager* DataManager::instance() {
	static DataManager inst;
	return &inst;
}