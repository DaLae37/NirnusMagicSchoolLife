#pragma once

#define DataMgr DataManger::instance()
class DataManager
{
public:
	DataManager();
	~DataManager();
	static DataManager* instance();
};