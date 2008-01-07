#ifndef NETWORK_COMMAND_H
#define NETWORK_COMMAND_H

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "vector-3d.h"

class NetworkCommand
{

public:

	NetworkCommand(void);
	
	NetworkCommand(std::string name);

	bool parse(std::string input);
	
	std::string toString(void);

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

	Vector3D _parseVector(std::string s);

	std::string _name;

	double _time;

	int _entityId;

	int _clientId;

	Vector3D _position, _speed, _acceleration;

};

#endif
