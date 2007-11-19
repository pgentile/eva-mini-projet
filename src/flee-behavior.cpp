#include "flee-behavior.h"

FleeBehavior::FleeBehavior()
{}

FleeBehavior::~FleeBehavior()
{}

Vector3D FleeBehavior::compute(SteeringEntity* entity)
{
  Vector3D toTarget=entity->getTransform()->getPosition()-_target;
  if (toTarget.getSqrModule()>_distance)
    {
      return Vector3D(0,0,0);
    }
  else
    {
      Vector3D desiredVelocity= toTarget*entity->getMaxVelocity();
      desiredVelocity.normalize();
      return (desiredVelocity-entity->getVelocity());
    }
}
