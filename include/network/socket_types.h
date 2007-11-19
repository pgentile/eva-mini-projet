#ifndef SOCKET_TYPES_H
#define SOCKET_TYPES_H

// namespace Utils
// {

#ifdef __linux__
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#define CONST_CAST(v) (v) 
#define CAST(v) (v) 
typedef struct in_addr                IN_ADDR_T;
typedef struct sockaddr               SOCKADDR_T ;
typedef struct sockaddr_in            SOCKADDR_IN_T;
typedef int                           SOCKET_T ;
typedef socklen_t                     SOCKLEN_T;
typedef struct hostent                HOSTENT_T;
#endif

#ifdef __WIN32__
#ifdef __cplusplus
extern "C" {
#endif
#include <winsock.h>
#ifdef __cplusplus
}
#endif
#include <windows.h>
#define CONST_CAST(v) ((const char*)v)
#define CAST(v) ((char*)v)
typedef IN_ADDR                      IN_ADDR_T;
typedef SOCKADDR                     SOCKADDR_T;
typedef SOCKADDR_IN                  SOCKADDR_IN_T ;
typedef SOCKET                       SOCKET_T;
typedef int                          SOCKLEN_T;
typedef struct hostent               HOSTENT_T;
#endif

union IPADDRESS
{
  IN_ADDR_T address;
  struct _bytes
  {
    unsigned char c1,c2,c3,c4;
  } bytes;
};

// }//namespace Utils

#endif
