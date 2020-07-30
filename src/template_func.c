#include <assert.h>

#include "template_func.h"

/**
 * Open TCP socket
 */
#include <arpa/inet.h>

int fd_tcp_server_open( uint16_t port ) {
	int                ret;
	int                server_socket;
	struct sockaddr_in server_addr = { 0 };
	socklen_t          server_length;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons( port );
	server_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	server_length = sizeof( server_addr );

	server_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	assert( server_socket != -1 && "ERROR: Can't open socket!" );

	ret = bind( server_socket, (struct sockaddr *)&server_addr,
	            server_length );
	assert( ret != -1 && "ERROR: Can't bind socket!" );

	ret = listen( server_socket, 0 );
	assert( ret != -1 && "ERROR: Can't start listen port!" );

	return server_socket;
}

/**
 * Connect to TCP socket
 */
#include <arpa/inet.h>

int fd_tcp_client_open( const char *ip, uint16_t port ) {
	int                ret;
	int                client_socket;
	struct sockaddr_in client_addr = { 0 };
	socklen_t          client_length;
	struct in_addr     server_address;

	ret = inet_aton( ip, &server_address );
	assert( ret != 0 && "ERROR: Can't parse ip address!" );

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons( port );
	client_addr.sin_addr.s_addr = server_address.s_addr;
	client_length = sizeof( client_addr );

	client_socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	assert( client_socket != -1 && "ERROR: Can't open socket!" );

	ret = connect( client_socket, (struct sockaddr *)&client_addr,
	               client_length );
	assert( ret != -1 && "ERROR: Can't connect to server!" );

	return client_socket;
}

/**
 * Wait connection new TCP client
 */
#include <arpa/inet.h>

int fd_tcp_wait_client( int socket ) {
	struct sockaddr_in client_addr = { 0 };
	socklen_t          client_length;
	return accept( socket, (struct sockaddr *)&client_addr,
	               &client_length );
}

/**
 * Recv TCP message
 */
#include <arpa/inet.h>

ssize_t fd_tcp_recv_msg( int socket, char *recv_buf, size_t recv_len ) {
	return recv( socket, recv_buf, recv_len, 0 );
}

/**
 * Send TCP message
 */
#include <arpa/inet.h>

ssize_t fd_tcp_send_msg( int socket, char *send_buf, size_t send_len ) {
	return send( socket, send_buf, send_len, 0 );
}

/**
 * Register TCP packet handler
 */
#include <arpa/inet.h>
#include <pthread.h>
#include <stdlib.h>

struct server_struct_t {
	int server_socket;
	void *( *handler )( void *client_socket );
};

/*
#include <unistd.h>
#include <stdlib.h>

void *handler_example( void *arg ) {
        int *client_socket = (int *)arg;

        close( *client_socket );
        free( client_socket );
        pthread_exit( NULL );
}
*/

static void *server_thread_loop( void *arg ) {
	int                     ret;
	struct server_struct_t *server_struct = (struct server_struct_t *)arg;
	int                     client_socket;

	while ( 1 ) {
		struct sockaddr_in client_addr = { 0 };
		socklen_t          client_length;
		pthread_t          client_thread = { 0 };

		client_socket =
		    accept( server_struct->server_socket,
		            (struct sockaddr *)&client_addr, &client_length );
		assert( client_socket != -1 &&
		        "ERROR: Can't accept connection!" );

		int *tmp = calloc( 1, sizeof( int ) );
		assert( tmp != NULL && "EROR: Can't allocate memory!" );
		*tmp = client_socket;

		ret = pthread_create( &client_thread, NULL,
		                      server_struct->handler, (void *)tmp );
		assert( ret == 0 && "ERROR: Can't start accept thread!" );
	}

	// TODO: How to free after pthread_cancel() ???
	free( server_struct );
	pthread_exit( NULL );
}

pthread_t
fd_tcp_server_register_handler( int server_socket,
                                void *( *handler )( void *client_socket ) ) {
	int                     ret;
	pthread_t               server_thread;
	struct server_struct_t *server_struct;

	server_struct = calloc( 1, sizeof( struct server_struct_t ) );
	assert( server_struct != NULL && "ERROR: Can't allocate memory!" );

	server_struct->server_socket = server_socket;
	server_struct->handler = handler;

	ret = pthread_create( &server_thread, NULL, server_thread_loop,
	                      (void *)server_struct );
	assert( ret == 0 && "ERROR: Can't start loop thread!" );

	return server_thread;
}

/**
 * Unregister TCP packet handler
 */
#include <pthread.h>

void fd_tcp_server_unregister_handler( pthread_t server_thread ) {
	int   ret;
	void *res;

	ret = pthread_cancel( server_thread );
	assert( ret == 0 && "ERROR: Can't cancel pthread!" );

	ret = pthread_join( server_thread, &res );
	assert( ret == 0 && "ERROR: Can't join to pthread!" );
	assert( res == PTHREAD_CANCELED && "ERROR: Thread was not canceled!" );
}

/**
 * Open UDP socket
 */
#include <arpa/inet.h>

int fd_udp_server_open( uint16_t port ) {
	int                ret;
	int                server_socket;
	struct sockaddr_in server_addr = { 0 };
	socklen_t          server_length;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons( port );
	server_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	server_length = sizeof( server_addr );

	server_socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	assert( server_socket != -1 && "ERROR: Can't open socket!" );

	ret = bind( server_socket, (struct sockaddr *)&server_addr,
	            server_length );
	assert( ret != -1 && "ERROR: Can't bind socket!" );

	return server_socket;
}

/**
 * Connect to UDP socket
 */
#include <arpa/inet.h>

int fd_udp_client_open( void ) {
	int client_socket;

	client_socket = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP );
	assert( client_socket != -1 && "ERROR: Can't open socket!" );

	return client_socket;
}

/**
 * Recieve UDP message
 */
#include <arpa/inet.h>

ssize_t fd_udp_recv_msg( int server_socket, char *recv_buf, size_t recv_len ) {
	struct sockaddr_in client_struct = { 0 };
	socklen_t          client_length;

	return recvfrom( server_socket, recv_buf, recv_len, 0,
	                 (struct sockaddr *)&client_struct, &client_length );
}

/**
 * Send UDP message
 */
#include <arpa/inet.h>

ssize_t fd_udp_send_msg( int client_socket, char *send_buf, size_t send_len,
                         const struct sockaddr_in *server_struct ) {
	return sendto( client_socket, send_buf, send_len, 0,
	               (const struct sockaddr *)server_struct,
	               sizeof( struct sockaddr_in ) );
}

/**
 * Convert ip and port to struct sockaddr_in
 */
#include <arpa/inet.h>

socklen_t fd_util_ip_and_port_to_sockaddr( struct sockaddr_in *addr,
                                           const char *ip, uint16_t port ) {
	int            ret;
	struct in_addr address;

	ret = inet_aton( ip, &address );
	assert( ret != 0 && "ERROR: Can't parse ip address!" );

	addr->sin_family = AF_INET;
	addr->sin_port = htons( port );
	addr->sin_addr.s_addr = address.s_addr;

	return sizeof( struct sockaddr_in );
}
