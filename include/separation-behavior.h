#ifndef SEPARATION_BEHAVIOR_H
#define SEPARATION_BEHAVIOR_H

#include "steering-behavior.h"
#include "steering-entity.h"

class SeparationBehavior:public SteeringBehavior
{
public:
  SeparationBehavior();
  virtual ~SeparationBehavior();

  virtual Vector3D compute(SteeringEntity* entity);

protected:
private:
  double _distance;
};

#endif
