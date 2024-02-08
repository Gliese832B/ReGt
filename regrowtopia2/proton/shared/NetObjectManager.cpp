#include "NetObjectManager.hpp"
NetBase::NetBase() {
	field_20 = new EntityComponent;

}
void NetBase::SetNetID(int id) {
	netid = id;
}
