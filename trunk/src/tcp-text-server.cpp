#include "tcp-text-server.h"
#include <algorithm>

#define MAXRECV 1024


TCPTextServer::TCPTextServer(unsigned short port,
                             bool killOnLastExit,
                             char endCharacter):
  _socket(port,endCharacter)
{
  _socket.listen(5);
  _run=false;
  _killOnLastExit=killOnLastExit;
}

TCPTextServer::~TCPTextServer()
{
  //Clean all client sockets
}

void TCPTextServer::launch()
{
  setup();
  execute();
}

void TCPTextServer::stop()
{
  _run=false;
}

void TCPTextServer::setup()
{
  _run=true;
}

void TCPTextServer::addClient(TCPTextSocket* sock)
{
  //Negotiate end character
  char c=_socket.getEndCharacter();
  ((Socket*)sock)->send((void*)&c,sizeof(char),0);
  sock->setEndCharacter(c);
  _clients.push_back(sock);
}

void TCPTextServer::removeClient(TCPTextSocket* sock)
{
  //remove the client
  _removedClients.push_back(std::find(_clients.begin(),_clients.end(),sock));
}

void TCPTextServer::cleanRemovedClients()
{
  for (unsigned int i=0;i<_removedClients.size();i++)
    {
      TCPTextSocket* sock=*_removedClients[i];
      _clients.erase(_removedClients[i]);
      //Clean the socket
      delete sock;
      //quit if last client
      if (_clients.empty()&&_killOnLastExit)
        {
          _run=false;
        }
    }
  _removedClients.clear();
}

void TCPTextServer::execute()
{
  while (_run)
    {
      step();
    }
}

void TCPTextServer::step()
{
  //accept clients
  while (_socket.isReady())
    {
      TCPTextSocket* sock=_socket.accept();
      if (!sock)
        {
          std::cout<<"Error accepting connection."<<std::endl;
          exit(-1);
        }
      else
        {
          addClient(sock);
        }
    }
  //process requests for each clients
  for (unsigned int i=0;i<_clients.size();i++)
    {
      //if there's data on the socket
      if (_clients[i]->isReady())
        {
          TCPTextSocket* sock=_clients[i];
          std::string command;
          if (sock->receive(command))
            {
              //execute command
              if (!parse_command(command,sock))
                {
                  removeClient(sock);
                  break;
                }
            }
          else
            {
              removeClient(sock);
              break;
            }
        }
    }
  cleanRemovedClients();
}


