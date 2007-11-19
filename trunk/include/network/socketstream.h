#ifndef SOCKETSTREAM_H
#define SOCKETSTREAM_H

#include <iostream>
#include <streambuf>
#include "socket.h"

// class NetworkSerializable
// {
// public:
//   NetworkSerializable();
//   virtual ~NetworkSerializable();

//   friend std::ostream& operator<<(std::ostream& os,const NetworkSerializable& ns)
//   {
//     os.write(ns);
//     return os;
//   }

//   friend std::istream operator>>(std::istream& is,NetworkSerializable& ns)
//   {
    
//   }

// protected:
// private:
// };

/**
   SocketStreamBuffer
   Only for TCPSocket for now?
*/
class SocketStreamBuffer:public std::streambuf
{
  static int _bufSize;
public:
  SocketStreamBuffer(Socket* socket,int bufSize=_bufSize);
  virtual ~SocketStreamBuffer();

  virtual bool isReady();
  
  inline char* get_ibuffer() {return _ibuffer;}
  inline char* get_obuffer() {return _obuffer;}

protected:
  //ostream
  virtual int sync();
  virtual int overflow(int c=EOF);
  //istream
  virtual int underflow();

  

private:
  Socket* _socket;
  char* _ibuffer;
  char* _obuffer;
};

/**
   Socket Stream
*/
class SocketStream:public std::iostream
{
public:
  SocketStream(Socket* socket);
  virtual ~SocketStream();

  inline bool isReady() {return _buffer.isReady();}

protected:
 
private:
  SocketStreamBuffer _buffer;
};

#endif
