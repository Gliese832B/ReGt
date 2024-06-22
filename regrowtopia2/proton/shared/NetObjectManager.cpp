#include "NetObjectManager.hpp"
#include "PlatformPrecomp.h"
NetBase::NetBase() {
	field_20 = new EntityComponent;

}
void NetBase::SetNetID(int id) {
	netid = id;
}
void NetMoving::Move(float a2, float a3, int a4) {
	int v16;
	int v11;
	float v5 = a2 + field_78;
	float v6 = field_7C;
	float v7 = v5;
	field_78 = v5;
	float v8 = a3 + v6;
	field_7C = a3 + v6;
	float v9 = floorf(v5 + 0.5);
	float v10 = floorf(v8 + 0.5);
	field_78 = v7 - v9;
	field_7C = v8 - v10;
	if (v9 == 0.0)
		goto LABEL_10;
	if (v9 <= 0.0)
		v11 = -1;
	else
		v11 = 1;
	int v30 = v11;
	bool v33 = v11 > 0;
	while (1) {
		int v12 = v30;
		int v13 = field_4;
		int v14 = v30 + v13;
		int v15 = field_8;
		if (v14 >= 0) {
			v16 = v14 + field_C;
			if (v16 <= (float)((float)*(int*)(GetTileMap() + 4) * 32.0))
				break;
			
		}
	}
}
