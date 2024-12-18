#pragma once
#include "ItemInfo.h"
#include "World.hpp"

class Tile {
public:
	void SetBG(__int16 a2, __int16 a3);
	bool DoesWorldRectCollide(CL_Rectf* a2);
	int Set(int a2, unsigned __int16 a3, World* a4);
	int isDoor();
	void ApplyDamage(int a2);
	int __fastcall GetItemIDThatWillTakeDamage();

private:
	__int16 field_0;
	__int16 field_2;
	int field_4;
	int field_8;
	__int16 field_C;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
	int field_30;
	int field_34;



};
