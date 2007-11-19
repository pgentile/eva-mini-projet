#ifndef CAR_ENTITY_H
#define CAR_ENTITY_H

#include "steering-entity.h"
#include "steering-behavior.h"
#include "seek-behavior.h"
#include "arrive-behavior.h"
#include "separation-behavior.h"
#include "car-track.h"

class CarEntity:public SteeringEntity
{
public:
  CarEntity(SteeringSystem* system,
            CarTrack* track);
  virtual ~CarEntity();

  virtual void update(double dt);
  inline void setCamera(Camera* camera)
  {
    _camera=camera;
  }
protected:
private:
  Camera* _camera;
  CarTrack* _track;
  unsigned int _currentTarget;
  //behaviors                                    
  SeekBehavior* _seek;
  ArriveBehavior* _arrive;
  SeparationBehavior* _separation;
};


#endif
