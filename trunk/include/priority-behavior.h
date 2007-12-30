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

protected:
private:

};

#endif
