#ifndef STEERING_BEHAVIOR_H
#define STEERING_BEHAVIOR_H

#include "vector-3d.h"

class SteeringEntity;

class SteeringBehavior
{
public:
  SteeringBehavior();
  virtual ~SteeringBehavior();

  virtual Vector3D compute(SteeringEntity* entity)=0;

  inline void setWeight(double w) {_weight=w;}
  inline double getWeight() const {return _weight;}

protected:
private:
  double _weight;
};

#endif
