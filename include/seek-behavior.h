#ifndef SEEK_BEHAVIOR_H
#define SEEK_BEHAVIOR_H

#include "steering-entity.h"
#include "steering-behavior.h"

class SeekBehavior:public SteeringBehavior
{
public:
  SeekBehavior();              
  virtual ~SeekBehavior();

  virtual Vector3D compute(SteeringEntity* entity);

  inline Vector3D getTarget() const
  {
    return _target;
  }
  inline void setTarget(const Vector3D& target)
  {
    _target=target;
  }

protected:
private:
  Vector3D _target;
};

#endif
