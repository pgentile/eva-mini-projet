#ifndef WANDER_BEHAVIOR_H
#define WANDER_BEHAVIOR_H

#include "steering-entity.h"
#include "steering-behavior.h"

class WanderBehavior:public SteeringBehavior
{
public:
  WanderBehavior();
  virtual ~WanderBehavior();

  virtual Vector3D compute(SteeringEntity* entity);

  inline void setTarget(const Vector3D& vec)
  {
    _target=vec;
  }
  inline Vector3D getTarget() const
  {
    return _target;
  }

protected:
private:
  double _radius;
  double _distance;
  double _jitter;
  Vector3D _localTarget;
  Vector3D _target;
};

#endif
