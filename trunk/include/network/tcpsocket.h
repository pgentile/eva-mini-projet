#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "socket.h"

// //Acknowledge stuff
// #define ACK "done\n" //default ACK string to be used by the TCPTextServer
// #define ACK_SIZE 5 //ACK size in bytes


// namespace Utils
// {

class TCPSocket:public Socket
{
 public:
  TCPSocket(int port=-1);
  virtual ~TCPSocket();

  
  virtual TCPSocket* accept();
  virtual bool listen(int size);
  virtual bool connect(IPADDRESS address,unsigned short port);
  virtual bool connect(std::string host,unsigned short port);
  virtual bool disconnect();
 
  
//   static void sendACK(TCPSocket* socket)
//   {
//     socket->send(ACK,ACK_SIZE,0);
//   }
  
//   static void receiveACK(TCPSocket* socket)
//   {
//     char buff[ACK_SIZE];
//     socket->receive(buff,ACK_SIZE,0);
//   }


 private:
};

//}//namespace Utils

#endif
