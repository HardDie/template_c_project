#ifndef _TEMPLATE_FUNC_
#define _TEMPLATE_FUNC_

#include <stdint.h>

extern int fd_tcp_socket_open( uint16_t port );
extern int fd_tcp_socket_connect( const char *ip, uint16_t port );

#endif /* _TEMPLATE_FUNC_ */
