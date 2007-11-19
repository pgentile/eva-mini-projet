/*
  Test de la libnetwork
*/
#include <iostream>
#include <sstream>
#include "tcp-text-server.h"

class EvaServer:public TCPTextServer
{
public:
  EvaServer(unsigned short port=22222,
           bool killOnLastExit=true,
           char endCharacter='\n'):
    TCPTextServer(port,killOnLastExit,endCharacter)
  {}
  virtual ~EvaServer()
  {}

  virtual bool parse_command(std::string text,TCPTextSocket* sock)
  {
    //Effectuer le traitement des commandes recues ici
    //sock est le client qui nous a envoyé le texte
    std::cout<<"Received: "<<text<<std::endl;
    return true;
  }

protected:
private:
};

int main(int argc,char** argv)
{
  if (argc==2)//mode serveur
    {
      std::stringstream port_sstr(argv[1]);
      int server_port=-1;
      port_sstr>>server_port;
      std::cout<<"Création d'un serveur sur le port: "<<server_port<<std::endl;
      EvaServer server(server_port,true,'\n');
      server.launch();
    }
  else
    {
      std::cout<<"Usage: "<<argv[0]<<" port"<<std::endl;
    }
  return 0;
}
