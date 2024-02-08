#pragma once
#include "PlatformPrecomp.h"

#include "util/TextScanner.h"
#include <vector>
class ItemInfo {
public:
	int field_0;
	int field_4;
	int field_8;
	std::string m_name;
	unsigned int field_10;
	std::string field_14;
	int field_18;
	unsigned int field_1C;
	unsigned char field_20;
	unsigned char field_21;
	char field_22;
	char field_23;
	int field_24;
	int field_28;
	int field_2C;
	unsigned char field_30;
	char field_31;
	unsigned short flags;
	char field_33;
	int field_34;
	int field_38;
	unsigned char field_3C;
	unsigned char field_3D;
	unsigned char field_3E;
	unsigned char field_3F;
	unsigned int field_40;
	unsigned int field_44;
	unsigned short field_48;
	char field_49;
	unsigned short field_4A;
	char field_4B;
	unsigned int field_4C;
	int lockPower;
	unsigned __int16 field_54;
	unsigned char field_56;
	char field_57;
	int field_58;
	unsigned int field_5C;
	int field_60;
	void Serialize(unsigned __int8* a2, int a3, bool a4, unsigned __int16 a5);
	bool isUnlimited();
	int GetInventorySortPriority();
	int GetMaxTilesToLock();
	bool isEditable();
	int CalculateGrowImagesAndColors(int a2);
	void CheckItemForUpdates(ItemInfo* a1, int* a2);
};
class ItemInfoManager {
public:
	ItemInfoManager() {
		field_4 = 0;
		field_10 = 0;
		//kiss my ass NEX I wont rename

	}
	

  short field_0;
  BYTE field_4;
  std::vector<ItemInfo> m_items;
  std::vector<ItemInfo> field_C;
  int field_10;
  bool LoadFromMem(unsigned __int8* a2);
  ItemInfo* GetItemByName(std::string a2);

  ItemInfo* GetItemByIDSafe(int itemid);
};
 class InventoryItem
{
public:
	short itemId;
	uint8_t amount;
	uint8_t flag;
	void ToggleFlag(unsigned __int8 a2);
	

	
	
	
};

class PlayerItems {
public:
	void SetDefaultQuickTools();
	int field_0;
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
	std::list<InventoryItem> field_18;
	
	int field_1C;
	uint16 field_20[4];
	uint16 field_24;
	int field_28;
	InventoryItem* GetItemByID(int itemid);
	
	int GetQuickSlotThisItemIsIn(int a2);
	int GetCountOfAnItem(int itemid);
	void RemoveFromQuickSlots(int a2);
	std::string PrintItems();

};
