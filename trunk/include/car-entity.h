#ifndef CAR_ENTITY_H
#define CAR_ENTITY_H

#include "steering-entity.h"
#include "steering-behavior.h"
#include "seek-behavior.h"
#include "arrive-behavior.h"
#include "stay-on-track-behavior.h"
#include "separation-behavior.h"
#include "priority-behavior.h"
#include "car-track.h"

class CarEntity:public SteeringEntity
{
public:
  CarEntity(SteeringSystem* system,
            CarTrack* track, unsigned int currentTarget);
  virtual ~CarEntity();

  virtual void update(double dt);
  virtual Vector3D getCurrentTarget();
  virtual Vector3D getPreviousTarget();
  inline void setCamera(Camera* camera)
  {
    _camera=camera;
  }
  inline CarTrack* getTrack()
  {
      return _track;
  }
protected:
private:
  Camera* _camera;
  CarTrack* _track;
  
  void _securityTest(SteeringEntity* nearestEntity, Vector3D target);
  std::vector<SteeringEntity*> getNearEntities(double minDist,double maxDist, double minAngleDeg, double maxAngleDeg);
  std::vector<SteeringEntity*> getNearEntities(void);
  SteeringEntity* getNearestEntity(std::vector<SteeringEntity*> nearEntities);

  bool _securityOn;
  Vector3D _oldTarget;

  //behaviors                                    
  SeekBehavior* _seek;
  ArriveBehavior* _arrive;
  SeparationBehavior* _separation;
  PriorityBehavior* _priority;
  StayOnTrackBehavior* _stayOnTrack;
};


#endif
