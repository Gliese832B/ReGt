#include "PlatformPrecomp.h"
#include "Tiles.hpp"


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
