#include "seek-behavior.h"

SeekBehavior::SeekBehavior()
{}

SeekBehavior::~SeekBehavior()
{}

Vector3D SeekBehavior::compute(SteeringEntity* entity)
{
  Vector3D desiredVelocity= (_target-entity->getTransform()->getPosition())*
    entity->getMaxVelocity();
  desiredVelocity.normalize();
  return (desiredVelocity-entity->getVelocity());
}

