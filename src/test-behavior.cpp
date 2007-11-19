#include "test-behavior.h"

TestBehavior::TestBehavior()
{}

TestBehavior::~TestBehavior()
{}

Vector3D TestBehavior::compute(SteeringEntity* entity)
{
  Vector3D position=entity->getTransform()->getPosition();
  if ((position.getX()>=30)||(position.getY()>=30))
    {
      _arrived=true;
    }
  else  if ((position.getX()<0)||(position.getY()<0))
    {
      _arrived=false;
    }
  if (position.getZ()<-10)
    {
      up_component=20.0;
    }
  else if (position.getZ()>10)
    {
      up_component=-20.0;
    }
  if (!_arrived)
    {
      return Vector3D(5,5,up_component);
    }
  else
    {
      return Vector3D(-5,-5,up_component);
    }
}

