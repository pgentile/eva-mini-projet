#include "arrive-behavior.h"
#include "macros.h"

ArriveBehavior::ArriveBehavior()
{
  _decelerationFactor=3.0;
}

ArriveBehavior::~ArriveBehavior()
{}

Vector3D ArriveBehavior::compute(SteeringEntity* entity)
{
  Vector3D toTarget= _target-entity->getTransform()->getPosition();
  double dist=toTarget.getModule();
  if (dist>.0001)
    {
      double speed=dist/_decelerationFactor;
      speed=MIN(speed,entity->getMaxVelocity());
      Vector3D desiredVelocity=toTarget*speed/dist;
      return (desiredVelocity-entity->getVelocity());
    }
  return Vector3D(0,0,0);
}
