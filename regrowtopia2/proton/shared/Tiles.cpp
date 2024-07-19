#include "PlatformPrecomp.h"
#include "Tiles.hpp"
#include "ItemInfo.h"


void Tile::SetBG(__int16 a2, __int16 a3) {
	field_C = a3;
	field_28 = 0;
	field_0 = a2;
}
bool Tile::DoesWorldRectCollide(CL_Rectf* a2) {
	bool result;
	if (a2->left >= field_C || a2->right <= field_14 || a2->top >= field_20)
		result = 0;
	else
		result = a2->bottom > field_18;
	return result;
}
int Tile::isDoor() {
	int result;
	result = field_24;
	if (result) {
		result = *(unsigned __int8*)(result + 4) == 1;

	}
	return result;

}
int Tile::GetItemIDThatWillTakeDamage() {
	int result;
	if (field_0) {
		result = (unsigned __int16)field_0;
	}
	else {
		result = (unsigned __int16)field_0;
	}
	return result;
}
void Tile::ApplyDamage(int a2) {
	unsigned int result;
	unsigned int v4 = field_2C;
	int v16;
	unsigned int v17;
	eTimingSystem v6 = GetBaseApp()->GetActiveTimingSystem();
	if (v4 > GetTick(v6)) {
		field_2C = 0;
		field_28 = 0;
	}
	ItemInfoManager* v7 = GetItemInfoManager();
	ItemInfo* v8 = &v7->m_items[GetItemIDThatWillTakeDamage()];
	int v9 = a2 + (unsigned __int8)field_28;
	int v10 = (unsigned __int8)v8->field_30;
	if (v9 < v10)
		field_28 = v9;
	else
		field_28 = v10;
	eTimingSystem v12 = GetBaseApp()->GetActiveTimingSystem();
	int v13 = GetTick(v12);
	int v14 = (unsigned __int16)field_0;
	result = v13 + 1000 * v8->field_34;
	field_2C = result;
	if (v14)
	{
		v16 = v8->field_4;
		if (v16 == 12) {
			field_4 ^= 0x40u;

		}
		else if (v16 == 11) {
			v17 = field_30;
			eTimingSystem v19 = GetBaseApp()->GetActiveTimingSystem();
			result = GetTick(v19);
			if (v17 <= result) {
				field_4 ^= 0x40u;
				eTimingSystem v21 = GetBaseApp()->GetActiveTimingSystem();
				result = GetTick(v21);
				field_30 = result + v8->field_60;

			}
		}
	}
	
}