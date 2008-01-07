/*
  Test de la libnetwork
*/
#include <iostream>
#include <sstream>
#include "tcp-text-server.h"
#include "network-command.h"

class EvaServer: public TCPTextServer
{

public:
	
	EvaServer(unsigned short port = 22222, bool killOnLastExit = true, char endCharacter = '\n'):
			TCPTextServer(port, killOnLastExit, endCharacter), _nextClientId(1)
	{
	}
	
	virtual ~EvaServer(void)
	{
	}

	virtual bool parse_command(std::string text, TCPTextSocket* sock)
	{
		NetworkCommand cmd;
		if (cmd.parse(text)) {

			// Display command
			std::cout << "Received command: " << cmd.getName() << std::endl;
			std::cout << "\tTime: " << cmd.getTime() << std::endl;
			std::cout << "\tEntity ID: " << cmd.getEntityId() << std::endl;
			std::cout << "\tClient ID: " << cmd.getClientId() << std::endl;
			std::cout << "\tPosition: " << cmd.getPosition() << std::endl;
			std::cout << "\tSpeed: " << cmd.getSpeed() << std::endl;
			std::cout << "\tAcceleration: " << cmd.getAcceleration() << std::endl;
			std::cout << std::endl;

			std::string name = cmd.getName();
			
			NetworkCommand responseCmd;

			// Connecter un client au serveur
			if (name == "CONNECT_ME") {
				responseCmd.setName("YOUR_ID_IS");
				responseCmd.setClientId(_nextClientId++);
				sock->send(responseCmd.toString());

				responseCmd.setName("TIME_IS");
				responseCmd.setTime(0.0);
				sock->send(responseCmd.toString());
			
			// Envoyer la correction a tous les clients
			} else if (name == "CORRECT") {
				_sendToAll(cmd, sock);
			}

		} else {
			std::cout << "Received data: " << text << ", but not recognized..." << std::endl;
		}
		return true;
	}
	
private:

	void _sendToAll(NetworkCommand& cmd, TCPTextSocket* excludedSock = NULL) {
		int i, max;
		for (i = 0, max = getNbClients(); i < max; i++) {
			TCPTextSocket* sock = getClient(i);
			if (excludedSock != NULL && excludedSock == sock) {
				continue;
			}
			sock->send(cmd.toString());
		}
	}

	int _nextClientId;

};

int main(int argc, char** argv)
{
	EvaServer server;
	server.launch();
	return 0;
}
