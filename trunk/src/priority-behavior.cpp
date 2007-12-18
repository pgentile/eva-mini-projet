#include "priority-behavior.h"
#include "steering-entity.h"
#include "macros.h"

PriorityBehavior::PriorityBehavior()
{
  _decelerationFactor=3;
}

PriorityBehavior::~PriorityBehavior()
{}

Vector3D PriorityBehavior::compute(SteeringEntity* entity){
  SteeringEntity* crossingEntity=NULL;
  SteeringSystem* system=entity->getSteeringSystem();
  double sqrmax=5000;
  for (unsigned int i=0;i<system->getNbEntities();i++)
  {
    if (i!=entity->getId())
    {
      SteeringEntity* s=system->getEntity(i);
      Vector3D toEntity=entity->getTransform()->getPosition()-
          s->getTransform()->getPosition();
      double sqrdist=toEntity.getSqrModule();
      if((s->getTarget()==61)&&(sqrdist<sqrmax)&&(entity->getSide().produitScalaire(toEntity)>0)&&(entity->getForward().produitScalaire(toEntity)>0)){
        crossingEntity=system->getEntity(i);
        sqrmax=sqrdist;
      }
    }
  }
  Vector3D toTarget =_target-entity->getTransform()->getPosition();
  //std::cout<<crossingEntity<<std::endl;
  if(crossingEntity==NULL)
  {
    Vector3D desiredVelocity= toTarget*
        entity->getMaxVelocity();
    desiredVelocity.normalize();
    if(toTarget.getModule()<5.0)
    {
      entity->setTarget(31);
    }
    return (desiredVelocity-entity->getVelocity());
  }
  else
  {    
    double dist=toTarget.getModule();
    if (dist>0.01)
    {
      double speed=dist/_decelerationFactor;
      speed=MIN(speed,entity->getMaxVelocity());
      Vector3D desiredVelocity=toTarget*speed/dist;
      return (desiredVelocity-entity->getVelocity());
    }
  }
  return Vector3D(0,0,0);
}

 
