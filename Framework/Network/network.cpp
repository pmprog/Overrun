
#include "network.h"

ALLEGRO_EVENT_SOURCE eventSource;
void event_destructor(ALLEGRO_USER_EVENT* e);

bool install_network()
{
	al_init_user_event_source( &eventSource );
	return ( enet_initialize() == 0 );
}

void uninstall_network()
{
	al_destroy_user_event_source( &eventSource );
	enet_deinitialize();
}

ENetHost* network_create_server( int port )
{
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = port;
	return enet_host_create ( &address /* the address to bind the server host to */,
		32 /* allow up to 32 clients and/or outgoing connections */,
		1 /* allow up to 1 channel to be used (0) */,
		0 /* assume any amount of incoming bandwidth */,
		0 /* assume any amount of outgoing bandwidth */);
}

ENetHost* network_create_client()
{
	return enet_host_create (NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		1 /* allow up to 1 channel to be used (0) */,
		0 /* 57600 / 8 == 56K modem with 56 Kbps downstream bandwidth */,
		0 /* 14400 / 8 == 56K modem with 14 Kbps upstream bandwidth */);
}

bool network_connect( ENetHost* socket, const char* server, int port )
{
	return network_connect( socket, server, port, 3000 );
}

bool network_connect( ENetHost* socket, const char* server, int port, int timeout )
{
	ENetAddress address;
	ENetEvent ev;

	if( socket == 0 )
		return false;

	enet_address_set_host( &address, server );
	address.port = port;
	enet_host_connect( socket, &address, 1, 0 );
	return (enet_host_service( socket, &ev, timeout) > 0 && ev.type == ENET_EVENT_TYPE_CONNECT);
}

void network_close( ENetHost* socket )
{
	ENetEvent ev;

	if( socket == 0 )
		return;

	for( int i = 0; i < socket->peerCount; i++ )
	{
		ENetPeer* p = &socket->peers[i];
		if( p->state != ENET_PEER_STATE_DISCONNECTED )
			enet_peer_disconnect( p, 0 );
	}
	while( enet_host_service( socket, &ev, 0 ) > 0 ) { }
	enet_host_destroy( socket );
}

void network_send( ENetHost* socket, void* data, int datalength )
{
	if( socket == 0 )
		return;

	ENetPacket* packet = enet_packet_create( data, datalength, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast( socket, 0, packet );
	enet_host_flush(socket);
}

void network_send( ENetHost* socket, ENetPeer* peer, void* data, int datalength )
{
	if( socket == 0 || peer == 0 )
		return;

	ENetPacket* packet = enet_packet_create( data, datalength, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, packet);
	enet_host_flush(socket);
}

void network_poll( ENetHost* socket )
{
	ALLEGRO_EVENT e;
	ENetEvent ev;

	if( socket == 0 )
		return;

	while( enet_host_service( socket, &ev, 0 ) > 0 )
	{
		e.user.data1 = (intptr_t)ev.peer;
		e.user.data2 = (intptr_t)ev.packet;
		switch( ev.type )
		{
			case ENET_EVENT_TYPE_CONNECT:
				e.type = ALLEGRO_EVENT_NETWORK_CONNECTION;
				al_emit_user_event( &eventSource, &e, &event_destructor );
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				e.type = ALLEGRO_EVENT_NETWORK_RECEIVEPACKET;
				al_emit_user_event( &eventSource, &e, &event_destructor );
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				e.type = ALLEGRO_EVENT_NETWORK_DISCONNECTION;
				al_emit_user_event( &eventSource, &e, &event_destructor );
				break;
		}
	}
}

ALLEGRO_EVENT_SOURCE* get_network_event_source()
{
	return &eventSource;
}

void event_destructor(ALLEGRO_USER_EVENT* e)
{
	enet_packet_destroy( (ENetPacket*)e->data3 );
}
