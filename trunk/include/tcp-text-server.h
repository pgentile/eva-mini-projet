#ifndef TCPTEXTSERVER_H
#define TCPTEXTSERVER_H

#include "network/tcpsocket.h"
#include "tcp-text-socket.h"
#include "tcp-text-client.h"
#include <vector>

  /**
     TCPTextServer
  */
  class TCPTextServer
  {
  public:
    TCPTextServer(unsigned short port=22222,
                  bool killOnLastExit=true,
                  char endCharacter='\n');
    virtual ~TCPTextServer();

    virtual void launch();

    virtual void stop();

    virtual void setup();
    virtual void execute();

    virtual void step();

    inline bool availableConnection(TCPSocket* sock)
    {
      return (std::find(_clients.begin(),_clients.end(),sock)!=_clients.end());
    }

    inline unsigned int getNbClients() const
    {
      return _clients.size();
    }
    inline TCPTextSocket* getClient(unsigned int index)
    {
      return _clients[index];
    }
    virtual bool parse_command(std::string command,TCPTextSocket* sock)=0;
  protected:
    virtual void addClient(TCPTextSocket*);
    virtual void removeClient(TCPTextSocket*);
    virtual void cleanRemovedClients();

  private:
    TCPTextSocket _socket;
    std::vector<TCPTextSocket*> _clients;
    bool _run;
    bool _killOnLastExit;
    std::vector<std::vector<TCPTextSocket*>::iterator> _removedClients;
  };



#endif
