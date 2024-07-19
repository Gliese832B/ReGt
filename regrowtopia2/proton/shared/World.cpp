#include "World.hpp"
#include "Tiles.hpp"
int World::HandlePacketTileChangeRequest(packet::gameupdatepacket* a2) {
	int result;
	int v2 = a2->m_type;
	switch (v2) {
	case 8:
		field_10[a2->m_tile_pos_x + a2->m_tile_pos_y * field_8].ApplyDamage(a2->m_net_id);
		result = 1;
		break;
	case 14:


	}
}