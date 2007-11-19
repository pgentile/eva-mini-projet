#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "socket.h"

// namespace Utils
// {

class UDPSocket:public Socket
{
 public:
  UDPSocket(int port=-1);
  virtual ~UDPSocket();
  
  virtual bool sendto(const void* msg,int length,IPADDRESS addr,int flags=0);
  virtual bool receivefrom(void* msg,int length,IPADDRESS addr,int flags=0);

  //virtual bool connect(IPADDRESS address,unsigned short port);

 private:
};

//}//namespace Utils

#endif
