#ifndef TCP_TEXT_SOCKET_H
#define TCP_TEXT_SOCKET_H

#include <network/tcpsocket.h>
#include <vector>

  /**
     TCPTextSocket
  */
  class TCPTextSocket:public TCPSocket
  {
  public:
    TCPTextSocket(int port=-1,
                  char endCharacter='\n');
    virtual ~TCPTextSocket();

    virtual bool send(const std::string& txt);
    virtual bool receive(std::string& txt);

    virtual TCPTextSocket* accept();

    inline void setEndCharacter(const char endCharacter)
    {_endCharacter=endCharacter;}
    inline char getEndCharacter() const {return _endCharacter;}
  protected:
  private:
    char _endCharacter;
  };
  
#endif
