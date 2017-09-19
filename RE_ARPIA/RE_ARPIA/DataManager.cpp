#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

DataManager* DataManager::instance() {
	static DataManager instacne;
	return &instacne;
}