#ifndef UDPBROADCASTSOCKET_H
#define UDPBROADCASTSOCKET_H

#include "udpsocket.h"

#include <vector>
// namespace Utils
// {

class UDPBroadcastSocket:public UDPSocket
{
 public:
  UDPBroadcastSocket(int port=-1);
  virtual ~UDPBroadcastSocket();

  virtual int send(const void* msg,int length,int flags);
  virtual int receive(void* msg,int length,int flags);

  virtual int collectBroadcastAddresses();

 private:
  static std::vector<in_addr_t> _broadcastAddresses;
};

// }//namespace Utils

#endif
