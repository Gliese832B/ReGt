#include "PlatformPrecomp.h"
#include "ItemInfo.h"
#include "util/TextScanner.h"
#include <vector>
void ItemInfo::Serialize(unsigned __int8* a2, int a3, bool a4, unsigned __int16 a5) {
	int v10;
	MemorySerialize<int>(field_0, a2, a3, a4);
	MemorySerialize<unsigned short>(flags, a2, a3, a4);
	unsigned __int8 v14 = field_4;
	MemorySerialize<unsigned char>(v14, a2, a3, a4);
	int v9 = field_8;
	field_4 = v14;
	v14 = v9;
	MemorySerialize<unsigned char>(v14, a2, a3, a4);
	field_8 = v14;
	MemorySerialize(field_C, a2, a3, a4);
	MemorySerialize(field_14, a2, a3, a4);
	MemorySerialize<unsigned int>(field_10, a2, a3, a4);
	v14 = field_18;
	MemorySerialize<unsigned char>(v14, a2, a3, a4);
	field_18 = v14;

	MemorySerialize<unsigned int>(field_1C, a2, a3, a4);
	MemorySerialize<unsigned char>(field_20, a2, a3, a4);
	MemorySerialize<unsigned char>(field_21, a2, a3, a4);


	v14 = field_24;
	MemorySerialize<unsigned char>(v14, a2, a3, a4);
	if (a4)
		int v10 = field_28;
	field_24 = v14;
	int v11 = a3;
	if (a4) a2[v11] = v10;

	else v11 = a2[v11];
	int v12 = field_2C;
	if (!a4) {
		field_28 = v11;
	}

	++a3;
	MemorySerialize<unsigned char>(v14,a2, a3, a4);
	field_2C = v14;
	MemorySerialize<unsigned char>(field_30, a2, a3, a4);
	MemorySerialize<int>(field_34, a2, a3, a4);
	v14 = field_38;
	MemorySerialize<unsigned char>(v14, a2, a3, a4);
	field_38 = v14;

	MemorySerialize<unsigned short>(field_54, a2, a3, a4);
	MemorySerialize<unsigned char>(field_56, a2, a3, a4);
	MemorySerialize(field_58, a2, a3, a4);
	MemorySerialize<unsigned int>(field_5C, a2, a3, a4);
	MemorySerialize<int>(field_60, a2, a3, a4);
	MemorySerialize<unsigned char>(field_3C, a2, a3, a4);
	MemorySerialize<unsigned char>(field_3D, a2, a3, a4);
	MemorySerialize<unsigned char>(field_3E, a2, a3, a4);
	MemorySerialize<unsigned char>(field_3F, a2, a3, a4);
	MemorySerialize<unsigned int>(field_40, a2, a3, a4);
	MemorySerialize<unsigned int>(field_44, a2, a3, a4);
	MemorySerialize<unsigned short>(field_48, a2, a3, a4);
	MemorySerialize<unsigned short>(field_4A, a2, a3, a4);
	return MemorySerialize<unsigned int>(field_4C, a2, a3, a4);
}
bool ItemInfo::isUnlimited() {
	return field_56 == 0;

}
int ItemInfo::GetInventorySortPriority() {
	return (unsigned __int16)field_54 + 5000 * field_4;
}
int ItemInfo::GetMaxTilesToLock() {
	return lockPower;
}
bool ItemInfo::isEditable() {
	return(flags & 2) != 0;
	
}
int GetBrightColorWithSeededRandom(CRandom* a1) {
	int v10[3];
	int v2 = a1->Random(2u);
	int v3 = v2 % 3;
	int v4;
	if (a1->Random(3u)) v4 = a1->Random(80u) + 175;
	else v4 = a1->Random(150u) + 105;
	v10[v3] = v4;
	int v5 = 355 - v4;
	int v6;
	if (a1->Random(355 - v4 <= 255u)) v6 = a1->Random(v5);
	else v6 = 255;
	v10[(v2 + 1) % 3] = v6;
	int v7 = 455 - v10[v3] - v6;
	int v8;
	if (a1->Random(v7 <= 255u)) v6 = a1->Random(v7);
	else v8 = 255;
	v10[(v2 + 2) % 3] = v8;
	return (v10[1] << 16) + (v10[0] << 8) + 255 + (v10[2] << 24);
}
int ItemInfo::CalculateGrowImagesAndColors(int a2) {
	CRandom* v5 = new CRandom;
	v5->SetRandomSeed(a2);
	field_40 = GetBrightColorWithSeededRandom(v5);
	int result = GetBrightColorWithSeededRandom(v5);
	field_3F = 2 * a2 % 8;
	field_44 = result;
	field_3C = a2 % 16;
	field_3D = 2 * a2 % 16;
	field_3E = a2 % 8;
	return result;
}
/* void ItemInfo::CheckItemForUpdates(ItemInfo* a1, int* a2) {
	int v2 = a1->field_14 - 12;
	

}*/
bool ItemInfoManager::LoadFromMem(unsigned __int8* a2) {
	unsigned short v56;
	 int v54;
	m_items.clear();
	field_4 = 1;
	int v55 = 0;
	MemorySerialize<unsigned short>(v56, a2, v55, false);
	MemorySerialize<int>(v54, a2, v55, false);
	m_items.resize(v54);
	
	for (size_t i = 0; i < m_items.size(); i++) {
		m_items[i].Serialize(a2, v55, false, 2u);

	}
	return true;

}
int ItemInfoManager::GetItemByName(ItemInfo* a1, std::string a2) {
	std::string v13;
	v13 = ToLowerCaseString(a2);


}