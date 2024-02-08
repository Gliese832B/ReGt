#pragma once
#include "App.h"
class NetBase {
public:
	int netid;
	EntityComponent* field_20;
	NetBase();
	void SetNetID(int id);
	
};
class NetObjectManager{
public:
	 std::map<int, NetBase*> netmap;

	NetObjectManager() {
		LogMsg("initalized netobject manager");
	}

};