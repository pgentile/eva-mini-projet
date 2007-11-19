#ifndef ARRIVE_BEHAVIOR_H
#define ARRIVE_BEHAVIOR_H

#include "steering-behavior.h"
#include "steering-entity.h"

class ArriveBehavior:public SteeringBehavior
{
public:
  ArriveBehavior();
  virtual ~ArriveBehavior();

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
  Vector3D _target;
  double _decelerationDistance;          
  double _decelerationFactor;
};

#endif
