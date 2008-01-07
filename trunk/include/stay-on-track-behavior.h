#ifndef STAY_ON_TRACK_H
#define STAY_ON_TRACK_H

#include "steering-behavior.h"
#include "steering-entity.h"

class StayOnTrackBehavior:public SteeringBehavior
{
public:
  StayOnTrackBehavior();
  virtual ~StayOnTrackBehavior();

  virtual Vector3D compute(SteeringEntity* entity);
protected:
private:
};

#endif
