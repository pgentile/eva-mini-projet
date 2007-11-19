#include "tcp-text-server.h"
#include <algorithm>

#define MAXRECV 1024

//tcptextclient
TCPTextClient::TCPTextClient()
{}

TCPTextClient::~TCPTextClient()
{}

bool TCPTextClient::connect(std::string host,int port)
{
  if (!_socket.connect(host,port))
    {
      return false;
    }
  //Get the endCharacter from server
  char c;
  ((Socket*)&_socket)->receive(&c,sizeof(char),MSG_WAITALL);
  _socket.setEndCharacter(c);
  return true;
}

void TCPTextClient::send(const std::string& txt)
{
  _socket.send(txt);
}

std::string TCPTextClient::receive()
{
  std::string tmp_str;
  _socket.receive(tmp_str);
  return /*_socket.receive()*/tmp_str;
}
