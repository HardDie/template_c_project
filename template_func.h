#ifndef _TEMPLATE_FUNC_
#define _TEMPLATE_FUNC_

#include <stdint.h>
#include <pthread.h>

extern int fd_tcp_server_open( uint16_t port );
extern int fd_tcp_client_open( const char *ip, uint16_t port );
extern pthread_t
             fd_tcp_server_register_handler( int server_socket,
                                             void *( *handler )( void *client_socket ) );
extern int   fd_udp_server_open( uint16_t port );
extern void *fd_udp_client_open( const char *ip, uint16_t port );

#endif /* _TEMPLATE_FUNC_ */
