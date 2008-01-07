/*
  Test de la libnetwork
*/
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <sys/time.h>
#include "tcp-text-server.h"
#include "vector-3d.h"
#include "network/usefull.h"
#include "network-command.h"

double getCurrentTime(void)
{
	struct timeval t;
	gettimeofday(&t, NULL);
	double sec = (double) t.tv_sec;
	double usec = (double) t.tv_usec * 0.000001;
	return sec + usec;
}

void initConnection(TCPTextClient& client, int& clientId, double& timeOffset)
{
	bool hasClientId = false, hasTimeOffset = false;
	while (!hasClientId || !hasTimeOffset) {
		if (client.isReady()) {
			NetworkCommand cmd;
			if (cmd.parse(client.receive())) {
				std::string name = cmd.getName();
				// Definir l'ID du client
				if (name == "YOUR_ID_IS") {
					clientId = cmd.getClientId();
					hasClientId = true;
				// Définir l'offset de temps
				} else if (name == "TIME_IS") {
					double clientTime = getCurrentTime();
					timeOffset = cmd.getTime() - clientTime;
					hasTimeOffset = true;
				}
				cmd.display();
			}
		}
	}
}

void getAllEntities(TCPTextClient& client)
{
	client.send("I_NEED_ALL_ENTITIES");
	double startTime = getCurrentTime();
	double currentTime = startTime;
	while (currentTime - startTime < 3.0) {
		if (client.isReady()) {
			NetworkCommand cmd;
			if (cmd.parse(client.receive()) && cmd.getName() == "ADD_ENTITY") {
				std::cout << "Entite ajoutee" << std::endl;
			}
		}
		currentTime = getCurrentTime();
	}
}

void registerEntities(TCPTextClient& client, int clientId, double timeOffset)
{
	int i;
	for (i = 0; i < 10; i++) {
		client.send("GET_ENTITY_ID");
		bool idRecieved = false;
		while (!idRecieved) {
			if (client.isReady()) {
				NetworkCommand cmd;
				if (cmd.parse(client.receive()) && cmd.getName() == "ENTITY_ID_IS") {
					NetworkCommand responseCmd("ADD_ENTITY");
					responseCmd.setClientId(clientId);
					responseCmd.setEntityId(cmd.getEntityId());
					responseCmd.setTime(getCurrentTime() + timeOffset);
					client.send(responseCmd.toString());
					idRecieved = true;
				}
			}
		}
	}
}

void play(TCPTextClient& client, int clientId, double timeOffset)
{
	while (true) {
		if (client.isReady()) {
			NetworkCommand cmd;
			if (cmd.parse(client.receive())) {
				if (cmd.getName() == "I_NEED_ALL_ENTITIES") {
					int i;
					for (i = 0; i < 10; i++) {
						NetworkCommand responseCmd("ADD_ENTITY");
						responseCmd.setClientId(clientId);
						responseCmd.setEntityId(0);
						responseCmd.setTime(getCurrentTime() + timeOffset);
						client.send(responseCmd.toString());
					}
				} else if (cmd.getName() == "ADD_ENTITY") {
					std::cout << "Ajout d'une entite externe" << std::endl;
				} else {
					cmd.display();
				}
			} else {
				std::cerr << "Invalid command" << std::endl;
			}
		}
	}
}

void createClient(void)
{
	int clientId;
	double timeOffset;
	TCPTextClient client;
	if (!client.connect("localhost", 22222)) {
		std::cerr << "Error during client connection..." << std::endl;
		return;
	}
	client.send("CONNECT_ME");
	initConnection(client, clientId, timeOffset);
	std::cout << "Je suis branche sur le serveur" << std::endl;
	std::cout << "\tMon ID : " << clientId << std::endl;
	std::cout << "\tOffset temporel : " << timeOffset << std::endl;
	registerEntities(client, clientId, timeOffset);
	std::cout << "My entities registred" << std::endl;
	getAllEntities(client);
	std::cout << "Other entities added" << std::endl;
	play(client, clientId, timeOffset);
}

int main(int argc, char** argv)
{
	createClient();
	return 0;
}
