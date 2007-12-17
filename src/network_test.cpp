/*
  Test de la libnetwork
*/
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "tcp-text-server.h"
#include "vector-3d.h"
#include "network/usefull.h"



class NetworkCommand
{

public:

	NetworkCommand(void)
	{
	}
	
	NetworkCommand(std::string name): _name(name)
	{
	}

	bool parse(std::string input)
	{
		std::vector<std::string> parts = Utils::split_string(input, " ");
		std::string args;
		_name = parts[0];
		parts.erase(parts.begin());
		if (parts.size() == 0) {
			parts.push_back("");
		}
		if (_name == "TIME_IS") {
			_time = strtod(parts[0].c_str(), NULL);
		} else if (_name == "YOUR_ID_IS") {
			_clientId = atoi(parts[0].c_str());
		} else if (_name == "CONNECT_ME") {
			// Do nothing...
		} else if (_name == "ARE_YOU_ALIVE") {
			// Do nothing...
		} else if (_name == "I_AM_ALIVE") {
			_clientId = atoi(parts[0].c_str());
		} else if (_name == "ADD_ENTITY") {
			if (parts.size() >= 6) {
				_clientId = atoi(parts[0].c_str());
				_entityId = atoi(parts[1].c_str());
				_time = strtod(parts[2].c_str(), NULL);
				_position = _parseVector(parts[3]);
				_speed = _parseVector(parts[4]);
				_acceleration = _parseVector(parts[5]);
			} else {
				return false;
			}
		} else if (_name == "REMOVE_ENTITY") {
			if (parts.size() >= 2) {
				_clientId = atoi(parts[0].c_str());
				_entityId = atoi(parts[1].c_str());
			} else {
				return false;
			}
		} else if (_name == "CORRECT") {
			if (parts.size() >= 6) {
				_clientId = atoi(parts[0].c_str());
				_entityId = atoi(parts[1].c_str());
				_time = strtod(parts[2].c_str(), NULL);
				_position = _parseVector(parts[3]);
				_speed = _parseVector(parts[4]);
				_acceleration = _parseVector(parts[5]);
			} else {
				return false;
			}
		} else {
			return false;
		}
		return true;
	}
	
	std::string toString(void)
	{
		std::stringstream buffer;
		buffer << _name;
		return buffer.str();
	}

	inline std::string getName(void) { return _name; }
	inline void setName(std::string name) { _name = name; }

	inline double getTime(void) { return _time; }
	inline void setTime(double time) { _time = time; }

	inline int getEntityId(void) { return _entityId; }
	inline void setEntityId(int entityId) { _entityId = entityId; }

	inline int getClientId(void) { return _clientId; }
	inline void setClientId(int clientId) { _clientId = clientId; }

	inline Vector3D getPosition(void) { return _position; }
	inline void setPosition(Vector3D position) { _position = position; }

	inline Vector3D getSpeed(void) { return _speed; }
	inline void setSpeed(Vector3D speed) { _speed = speed; }

	inline Vector3D getAcceleration(void) { return _acceleration; }
	inline void setAcceleration(Vector3D acc) { _acceleration = acc; }

private:

	Vector3D _parseVector(std::string s)
	{
		std::vector<std::string> parts = Utils::split_string(s, "-");
		if (parts.size() == 3) {
			double x = strtod(parts[0].c_str(), NULL);
			double y = strtod(parts[1].c_str(), NULL);
			double z = strtod(parts[2].c_str(), NULL);
			return Vector3D(x, y, z);
		}
		return Vector3D(0.0, 0.0, 0.0);
	}

	std::string _name;

	double _time;

	int _entityId;

	int _clientId;

	Vector3D _position, _speed, _acceleration;

};


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
