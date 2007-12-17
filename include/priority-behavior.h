#ifndef PIRORITY_BEHAVIOR_H
#define PIRORITY_BEHAVIOR_H

#include "steering-behavior.h"
#include "steering-entity.h"
#include "arrive-behavior.h"
#include "seek-behavior.h"

class CarEntity;

class PriorityBehavior:public SteeringBehavior
{
public:
  PriorityBehavior();
  virtual ~PriorityBehavior();

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
