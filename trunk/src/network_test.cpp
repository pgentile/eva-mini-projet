/*
  Test de la libnetwork
*/
#include <iostream>
#include <sstream>
#include "tcp-text-server.h"

class MyServer:public TCPTextServer
{
public:
  MyServer(unsigned short port=22222,
           bool killOnLastExit=true,
           char endCharacter='\n'):
    TCPTextServer(port,killOnLastExit,endCharacter)
  {}
  virtual ~MyServer()
  {}

  virtual bool parse_command(std::string text,TCPTextSocket* sock)
  {
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
      MyServer server(server_port,true,'\n');
      server.launch();
    }
  else if (argc==3)//mode client
    {
      std::stringstream port_sstr(argv[2]);
      int server_port=-1;
      port_sstr>>server_port;
      std::string server_addr=argv[1];
      std::cout<<"Connexion au serveur "
               <<server_addr<<":"<<server_port<<std::endl;
      TCPTextClient txt_client;
      if (!txt_client.connect(server_addr,server_port))
        {
          std::cout<<"Erreur lors de la connexion."<<std::endl;
          exit(-1);
        }

      while (true)
        {
          std::string input;
          std::cin>>input;
          txt_client.send(input);
        }
    }
  else
    {
      std::cout<<"Usage: "<<argv[0]<<" [server_ip] port"<<std::endl;
      std::cout<<"Si uniquement le port est précisé, un serveur est "
               <<"lancé, sinon c'est un client qui se connecte avec "
               <<"les paramètres fournis"<<std::endl;
    }
  return 0;
}
