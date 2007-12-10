#include "wall.h"

#include "shape.h"
#include "shape-part.h"
#include "baseshapes.h"

Wall::Wall(Vector3D p1, Vector3D p2): _p1(p1), _p2(p2), _up(Vector3D(0.0, 0.0, 1.0))
{
	_initShape();
}

Wall::Wall(Vector3D p1, Vector3D p2, Vector3D up): _p1(p1), _p2(p2), _up(Vector3D(up))
{
	_initShape();
}

Wall::~Wall(void)
{
}

void Wall::_initShape(void)
{
	Shape* shape = new Shape();

	Vector3D width = _p2 - _p1;
	ShapePart* part = new Quad(width.getModule(), _up.getModule());
	Vector3D position = (_p1 + _p2) / 2.0;
	part->getTransform()->setPosition(position);
	//Vector3D direction = getDirection();
	//part->getTransform()->setOrientation(direction.getX(), direction.getY(), direction.getZ());
	shape->addPart(part);
	
	setShape(shape);
}
