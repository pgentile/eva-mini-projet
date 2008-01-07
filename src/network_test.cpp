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
	createClient();
	return 0;
}
