

#pragma once
#include "App.h"

class NetBase {
public:
	int netid;
	EntityComponent* field_20;
	NetBase();
	void SetNetID(int id);
	int field_4 = 0;
	int field_8 = 0;
	int field_C = 0;
};
class NetMoving : NetBase {
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
	int field_30;
	int field_34;
	int field_38;
	int field_3C;
	int field_40;
	int field_44;
	int field_48;
	int field_4C;
	int field_50;
	int field_54;
	int field_58;
	int field_5C;
	int field_60;
	int field_64;
	int field_68;
	int field_6C;
	int field_70;
	int field_74;
	float field_78;
	float field_7C;
public:

	void Move(float a2, float a3, int a4);

};
class NetObjectManager {
public:
	std::map<int, NetBase*> netmap;

	NetObjectManager() {
		LogMsg("initalized netobject manager");
	}

};
