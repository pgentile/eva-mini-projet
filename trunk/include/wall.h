#ifndef WALL_H
#define WALL_H

#include "entity.h"
#include "vector-3d.h"

class Wall: public Entity
{

public:

	Wall(Vector3D p1, Vector3D p2);

	Wall(Vector3D p1, Vector3D p2, Vector3D up);
	
	virtual ~Wall(void);

	inline Vector3D getP1(void) const { return _p1; }

	inline Vector3D getP2(void) const { return _p2; }

	inline Vector3D getUp(void) const { return _up; }
	
	inline Vector3D getDirection(void) const
	{
		Vector3D d = _p2 - _p1;
		d.normalize();
		return d;
	}

private:

	Vector3D _p1, _p2, _up;
	
	void _initShape(void);

};

#endif
