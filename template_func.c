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
