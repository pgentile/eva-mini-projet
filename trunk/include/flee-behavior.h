#ifndef FLEE_BEHAVIOR_H
#define FLEE_BEHAVIOR_H

#include "steering-entity.h"
#include "steering-behavior.h"

class FleeBehavior:public SteeringBehavior
{
public:
  FleeBehavior();
  virtual ~FleeBehavior();

  virtual Vector3D compute(SteeringEntity* entity);

  inline void setTarget(const Vector3D& vec)
  {
    _target=vec;
  }
  inline Vector3D getTarget() const
  {
    return _target;
  }
  inline double getDistance() const
  {
    return sqrt(_distance);
  }
  inline void setDistance(double dist)
  {
    _distance=dist*dist;
  }
protected:
private:
  double _distance;
  Vector3D _target;
};

#endif
