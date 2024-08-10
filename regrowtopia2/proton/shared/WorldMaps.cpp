#include "WorldMaps.hpp"
void* __fastcall WorldObject::Serialize(unsigned __int8* a2, int a3, int a4) {
	bool v4 = a4 == 0;

	MemorySerialize<int>(field_10, a2, a3, v4);

	
}