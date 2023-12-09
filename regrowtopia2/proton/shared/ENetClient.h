#pragma once
#include <stdio.h>
#include "enet/enet.h"

class ENetClient  {
public:
	ENetHost* client;

	bool Init(ENetHost* client, const char* server, int port) {
		client = enet_host_create(NULL /* create a client host */,
			1 /* only allow 1 outgoing connection */,
			2 /* allow up 2 channels to be used, 0 and 1 */,
			0 /* assume any amount of incoming bandwidth */,
			0 /* assume any amount of outgoing bandwidth */);
		if (client) {


			client->checksum = enet_crc32;
			ENetAddress address;


			enet_host_compress_with_range_coder(client);
			enet_address_set_host(&address, server);
			address.port = port;

			ENetPeer* peer = enet_host_connect(client, &address, 2, 0);
			if (peer) {
				enet_host_flush(client);


			}
			else {
				LogMsg("No available peers for initiating an ENet connection.");
				return false;

			}
		}
		else {
			LogMsg("An error occurred while trying to create an ENet client host.");
			return false;
		}
	}
	
};