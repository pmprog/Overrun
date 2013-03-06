
#pragma once

#include <enet/enet.h>
#include <allegro5/allegro.h>

#define ALLEGRO_EVENT_NETWORK_CONNECTION					ALLEGRO_GET_EVENT_TYPE('N', 'W', 'c', 'n')
#define ALLEGRO_EVENT_NETWORK_RECEIVEPACKET				ALLEGRO_GET_EVENT_TYPE('N', 'W', 'r', 'c')
#define ALLEGRO_EVENT_NETWORK_DISCONNECTION				ALLEGRO_GET_EVENT_TYPE('N', 'W', 'd', 'c')

bool install_network();
void uninstall_network();

ENetHost* network_create_server( int port );
ENetHost* network_create_client();
bool network_connect( ENetHost* socket, const char* server, int port );
bool network_connect( ENetHost* socket, const char* server, int port, int timeout );
void network_close( ENetHost* socket );

void network_send( ENetHost* socket, void* data, int datalength );
void network_send( ENetHost* socket, ENetPeer* peer, void* data, int datalength );
void network_poll( ENetHost* socket );

ALLEGRO_EVENT_SOURCE* get_network_event_source();
