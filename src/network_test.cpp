/*
  Test de la libnetwork
*/
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "tcp-text-server.h"
#include "vector-3d.h"
#include "network/usefull.h"
#include "network-command.h"

class SimulatorServer: public TCPTextServer
{
	
public:
	
	SimulatorServer(unsigned short port = 22222, bool killOnLastExit = true, char endCharacter = '\n'):
			TCPTextServer(port, killOnLastExit, endCharacter), _nextClientId(1)
	{
	}
	
	virtual ~SimulatorServer(void)
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

			std::cout << "Command: " << cmd.toString() << std::endl;
			
			// Assign an ID on a connection client
			if (cmd.getName() == "CONNECT_ME") {
				NetworkCommand responseCmd("ARE_YOU_ALIVE");
				sock->send(responseCmd.toString());
			}
			
		} else {
			std::cout << "Received data: " << text << ", but not recognized..." << std::endl;
		}
		return true;
	}
	
private:

	int _nextClientId;

};


void createServer(void)
{
	SimulatorServer server;
	server.launch();
}

void createClient(void)
{
	TCPTextClient client;
	if (!client.connect("localhost", 22222)) {
		std::cerr << "Error during client connection..." << std::endl;
		return;
	}
	client.send("CONNECT_ME");
	while (true) {
		if (client.isReady()) {
			NetworkCommand cmd;
			if (cmd.parse(client.receive())) {
				std::cout << "OK !!!" << std::endl;
			}
		}
	}
}

int main(int argc, char** argv)
{
	bool showUsage = false;
	if (argc == 2) {
		std::string mode = argv[1];
		if (mode == "server") {
			createServer();
		} else if (mode == "client") {
			createClient();
		} else {
			showUsage = true;
		}
	} else {
		showUsage = true;
	}
	if (showUsage) {
		std::cerr << "Usage: " << argv[0] << " [ client | server ]" << std::endl;
		return 1;
	}
	return 0;
}
