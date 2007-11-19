#include "tcp-text-socket.h"
#include <algorithm>

#define MAXRECV 1024

//tcptextsocket=======================================================
TCPTextSocket::TCPTextSocket(int port,char endCharacter):
  TCPSocket(port),
  _endCharacter(endCharacter)
{
}

TCPTextSocket::~TCPTextSocket()
{}

TCPTextSocket* TCPTextSocket::accept()
{
  TCPTextSocket* s=new TCPTextSocket();
  if (Socket::accept(*s))
    {
      return s;
    }
  else
    {
      delete s;
      return NULL;
    }
}

bool TCPTextSocket::send(const std::string& txt)
{
  std::string toSend=txt;
  if (_endCharacter!=0) toSend+=_endCharacter;
  return (TCPSocket::send(toSend.c_str(),toSend.length(),0));
}

bool TCPTextSocket::receive(std::string& txt)
{
  std::string reply="";
  char c=0;

  if (_endCharacter!=0)
    {
      while ((Socket::receive(&c,sizeof(char),MSG_WAITALL))&&(c!=_endCharacter))
        {
          reply+=c;
        }
    }
  if (c!=_endCharacter) {return false;}

  txt=reply;
  return true;
}


