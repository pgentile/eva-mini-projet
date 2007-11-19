#ifndef TCP_TEXT_CLIENT_H
#define TCP_TEXT_CLIENT_H

#include <network/tcpsocket.h>
#include <vector>

/**
     TCPTextClient
*/
  class TCPTextClient
  {
  public:
    TCPTextClient();
    virtual ~TCPTextClient();

    inline bool isReady() {return _socket.isReady();}

    virtual bool connect(std::string host,int port);

    virtual void send(const std::string& txt);
    virtual std::string receive();


  protected:
  private:
    TCPTextSocket _socket;
  };
  
#endif
