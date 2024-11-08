#include "PlatformPrecomp.h"
#include "app.h"
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
	MemorySerialize(m_name, a2, a3, a4);
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
ItemInfo* ItemInfoManager::GetItemByName(std::string name) {
	name = ToLowerCaseString(name);
	for (size_t i = 0; i < m_items.size(); i++) {
		std::string lowerName = ToLowerCaseString(m_items[i].m_name);
		if (lowerName == name)
			return &m_items[i];
	}
	return nullptr;

}
ItemInfo* ItemInfoManager::GetItemByIDSafe(int itemid) {
	ItemInfo* v2 = new ItemInfo;
	if (itemid >= 0 && itemid < m_items.size()) return &v2[itemid];
	else return 0;
}

 void PlayerItems::SetDefaultQuickTools() {
	field_20[0] = 18;
} 
ItemInfoManager* GetItemInfoManager() { 
	return GetApp()->ItemManager;

}
 void InventoryItem::ToggleFlag(unsigned __int8 a2) {
	flag = a2;
	
}
 InventoryItem *PlayerItems::GetItemByID(int itemid) {
	 for (auto it = field_18.begin(); it != field_18.end(); ++it) {
		 if (it == field_18.end()) return NULL;
		 if (it->itemId == itemid) return &*it;	
			 
	
	 }
	 return NULL;

	 
 }
 int PlayerItems::GetQuickSlotThisItemIsIn(int a2) {
	 if (field_20[0] == a2) return 0;
	 if (field_20[1] == a2)
		 return 1;
	 if (field_20[2] == a2)
		 return 2;
	 if (field_20[3] == a2)
		 return 3;
	 return -1;

	
 }
 int PlayerItems::GetCountOfAnItem(int itemid) {
	 InventoryItem* result;
	 result = GetItemByID(itemid);
	 if (result) {
		 return result->amount;
	 }
	 return 0;
 }
 void PlayerItems::RemoveFromQuickSlots(int a2) {

	 if (field_20[0] == a2) field_20[0] = 0;
	 if (field_20[1] == a2) field_20[1] = 0;
	 if (field_20[2] == a2) field_20[2] = 0;
	 if (field_20[3] == a2) field_20[3] = 0;
	 
 }
 std::string PlayerItems::PrintItems() {
	 std::string a;
	 std::string v52;
	 auto v22 = field_18.begin();
	 if (field_18.empty()) {
		 a = "NONE";
	 }
	 else {
		 int itemCount = 0;

		 for (const InventoryItem& item : field_18)
		 {
			 
			 itemCount++;
		 }
		 v52.reserve(itemCount);
		 if (v22 != field_18.end()) {
			 while (1) {
				 ItemInfoManager* v5 = GetItemInfoManager();
				 ItemInfo* v21 = v5->GetItemByIDSafe(v22->itemId);
				 if (v21) break;
				 std::string a = toString(v22->itemId);
				 v52 + "ERROR: item " + a + " doesn't exist";
				 break;
			 }
		 }

	 }
	 return v52;

 }
 static bool operator<(const InventoryItem& a, const InventoryItem& b) {
	 ItemInfoManager* v4 = GetItemInfoManager();
	 int v5 = v4->m_items[a.itemId].GetInventorySortPriority();
	 ItemInfoManager* v6 = GetItemInfoManager();
	 return v5 < v6->m_items[b.itemId].GetInventorySortPriority();
 }