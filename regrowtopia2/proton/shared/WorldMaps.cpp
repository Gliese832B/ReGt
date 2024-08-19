#include "WorldMaps.hpp"
void* __fastcall WorldObject::Serialize(unsigned __int8* a2, int a3, int a4) {
	bool v4; // zf
	__int16* v9; // r3
	unsigned __int8 v10; // r12
	int* v11; // r1
	unsigned __int8* v12; // r0
	int v13; // r0
	
	int v15; // r3
	int v16; // r6

	v4 = a4 == 0;
	if (v4) {
		MemorySerialize<short>(field_C, a2, a3, a4);

		MemorySerialize(field_4, a2, a3, a4);
		MemorySerialize(field_8, a2, a3, a4);

	}

	
}
CL_Rectf* WorldObject::GetWorldRect(CL_Rectf* a2) {
	float v2; // r6
	float v3; // r5

	v2 = *(float*)&field_4;
	v3 = *(float*)&field_8;
	a2->left = v2;
	a2->top = v3;
	a2->right = v2 + (float)(v2 + 16.0);
	a2->bottom = v3 + (float)(v3 + 16.0);
	return a2;



}
float WorldObject::GetScaleEffect() {
	float result;
	int v14;
	int v3;

	if (field_18) {
		eTimingSystem v13 = GetBaseApp()->GetActiveTimingSystem();
		result = (float)GetTick(v13);
		int v15 = field_18 + 3000;
		bool v16 = v15 >= result;
		if (v15 >= result)
			result = 0.995;
		else
			v14 = 0;
		if (!v16) {
			field_18 = v14;
			result = 1.0;

		}

	}
	else {
		v3 = field_14;
		eTimingSystem timing2 = GetBaseApp()->GetActiveTimingSystem();
		float timingresult2 = static_cast<float>(GetTick(timing2));

		if (v3 && (static_cast<float>(static_cast<float>(static_cast<unsigned int>(v3)) + 630.0f) >= timingresult2)) {
			eTimingSystem timing3 = GetBaseApp()->GetActiveTimingSystem();
			float timeresult3 = static_cast<float>(GetTick(timing3) -  field_14) / 630.0;



		}
		else {
			result = 1.0;
		}
	}
	return result;
}
