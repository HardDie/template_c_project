#include <assert.h>

/**
 * Open TCP socket
 */
#include <arpa/inet.h>

int fd_tcp_socket_open( uint16_t port ) {
	int                ret;
	int                server_socket;
	struct sockaddr_in server_addr = {0};
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

	return server_socket;
}

/**
 * Connect to TCP socket
 */
#include <arpa/inet.h>

int fd_tcp_socket_connect( const char *ip, uint16_t port ) {
	int                ret;
	int                client_socket;
	struct sockaddr_in client_addr = {0};
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
