/*
  Test de la libnetwork
*/
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include "tcp-text-server.h"
#include "network-command.h"

class EvaServer: public TCPTextServer
{

public:
	
	EvaServer(unsigned short port = 22222, bool killOnLastExit = false, char endCharacter = '\n'):
			TCPTextServer(port, killOnLastExit, endCharacter), _nextClientId(1), _nextEntityId(1), _startTime(0.0)
	{
		_startTime = _getCurrentTime();
	}
	
	virtual ~EvaServer(void)
	{
	}

	virtual bool parse_command(std::string text, TCPTextSocket* sock)
	{
		NetworkCommand cmd;
		if (cmd.parse(text)) {

			std::cout << "Commande recue :" << std::endl;
			cmd.display();

			std::string name = cmd.getName();
			NetworkCommand responseCmd;

			// Connecter un client au serveur
			if (name == "CONNECT_ME") {
				responseCmd.setName("YOUR_ID_IS");
				responseCmd.setClientId(_nextClientId++);
				sock->send(responseCmd.toString());

				std::cout << "Commande envoyee :" << std::endl;
				responseCmd.display();

				responseCmd.setName("TIME_IS");
				responseCmd.setTime(_getCurrentTime() - _startTime);
				sock->send(responseCmd.toString());

				std::cout << "Commande envoyee :" << std::endl;
				responseCmd.display();
			
			// Envoyer les informations sur les entites sur tous les serveurs
			} else if (name == "CORRECT" || name == "ADD_ENTITY" || name == "REMOVE_ENTITY" || name == "I_NEED_ALL_ENTITIES") {
				_sendToAll(cmd, sock);
			
			// Envoyer un ID pour une entite
			} else if (name == "GET_ENTITY_ID") {
				responseCmd.setName("ENTITY_ID_IS");
				responseCmd.setEntityId(_nextEntityId++);
				sock->send(responseCmd.toString());

				std::cout << "Commande envoyee :" << std::endl;
				responseCmd.display();
			}

		} else {
			std::cerr << "Received data: " << text << ", but not recognized..." << std::endl;
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

			std::cout << "Commande envoyee :" << std::endl;
			cmd.display();
		}
	}
	
	double _getCurrentTime(void)
	{
		struct timeval t;
		gettimeofday(&t, NULL);
		double sec = (double) t.tv_sec;
		double usec = (double) t.tv_usec * 0.000001;
		return sec + usec;
	}

	int _nextClientId;
	
	int _nextEntityId;

	double _startTime;

};

int main(int argc, char** argv)
{
	EvaServer server;
	server.launch();
	return 0;
}
