#pragma once
#include "PlatformPrecomp.h"
class WorldObject {
public:

	void* __fastcall Serialize(unsigned __int8* a2, int a3, int a4);
	CL_Rectf* GetWorldRect(CL_Rectf* a2);
	float GetScaleEffect();
private:
	int field_0;
	float field_4;
	float field_8;
	short field_C;
	int field_10;
	int field_18;
	int field_14;

};
class WorldObjectMap {
private:
	int field_0;
	int field_4;
	std::list<WorldObject> field_8;
	int field_C;	
public:
	WorldObjectMap()

};
class WorldTileMap {
private:
	int field_0;
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
	int field_18;
public:

};
