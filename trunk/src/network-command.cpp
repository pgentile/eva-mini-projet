#include <vector>
#include "network/usefull.h"
#include "network-command.h"

NetworkCommand::NetworkCommand(void)
{
}

NetworkCommand::NetworkCommand(std::string name): _name(name)
{
}

bool NetworkCommand::parse(std::string input)
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
	} else if (_name == "YOUR_ID_IS" || _name == "I_AM_ALIVE") {
		_clientId = atoi(parts[0].c_str());
	} else if (_name == "CONNECT_ME") {
		// Do nothing...
	} else if (_name == "ARE_YOU_ALIVE") {
		// Do nothing...
	} else if (_name == "ADD_ENTITY" || _name == "CORRECT") {
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
	} else {
		return false;
	}
	return true;
}

std::string NetworkCommand::toString(void)
{
	std::stringstream buffer;
	buffer << _name;
	if (_name == "TIME_IS") {
		buffer << " " << _time;
	} else if (_name == "YOUR_ID_IS" || _name == "I_AM_ALIVE") {
		buffer << " " << _clientId;
	} else if (_name == "ADD_ENTITY" || _name == "CORRECT") {
		buffer << " " << _clientId << " " << _entityId << " " << _time;
		buffer << " " << _position.getX() << "-" << _position.getY() << "-" << _position.getZ();
		buffer << " " << _speed.getX() << "-" << _speed.getY() << "-" << _speed.getZ();
		buffer << " " << _acceleration.getX() << "-" << _acceleration.getY() << "-" << _acceleration.getZ();
	} else if (_name == "REMOVE_ENTITY") {
		buffer << " " << _clientId << " " << _entityId;
	}
	return buffer.str();
}

Vector3D NetworkCommand::_parseVector(std::string s)
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
