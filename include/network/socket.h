#ifndef SOCKET_H
#define SOCKET_H

#include "socket_types.h"

#include <iostream>

// namespace Utils
// {

class Socket
{
 public:

  //DEBUG
#ifdef DEBUG
  static unsigned int _nbSockets;
#endif 
 
  static const int MSG_OOB;
  static const int MSG_EOR;
  static const int MSG_DONTROUTE;
  static const int MSG_DONTWAIT;
  static const int MSG_NOSIGNAL;
  static const int MSG_CONFIRM;
  static const int MSG_PEEK;
  static const int MSG_WAITALL;
  static const int MSG_TRUNC;
  static const int MSG_ERRQUEUE;
  static const int MSG_CTRUNC;
  
  Socket();
  virtual ~Socket();

  //getters
  inline SOCKET_T getSocket() const {return _socket;}
  inline unsigned short getPort() const {return _port;}
  inline std::string getHostname() const   {return _hostname;}

  //Asynchronous IO management
  virtual bool isReady();


  virtual bool listen(int size);
  virtual bool accept(Socket& s);
  virtual bool connect(SOCKADDR_T *serv_addr);
  virtual int send(const void* buf,int len,int flags);
  virtual bool sendto(const void *msg, size_t count, int flags,const SOCKADDR_T *to);
  virtual bool receivefrom(void *buf, size_t len, int flags,SOCKADDR_T *from);
  virtual int receive(void* buf,int len,int flags);
  virtual bool read(void *buf, int len);
  virtual bool write(const void *buf, int count);
  virtual bool setSocketOption(int option,const void* value);

  //addresses management
  virtual HOSTENT_T* getHostByName(std::string name);



 protected:
  //setters
  inline void setSocket(SOCKET_T s) {_socket=s;}
  inline void setPort(unsigned short port) {_port=port;}
  //functions
  virtual bool create(int type);
  virtual bool close();
  virtual bool bind(unsigned short port);


 private:
  //attributes
  SOCKET_T _socket;
  int _port;
  std::string _hostname;
};

// }//namespace Utils

#endif
