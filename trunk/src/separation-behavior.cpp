#include "separation-behavior.h"
#include "steering-system.h"

#include <vector>

SeparationBehavior::SeparationBehavior()
{
  _distance=10.0;
}

SeparationBehavior::~SeparationBehavior()
{}

Vector3D SeparationBehavior::compute(SteeringEntity* entity)
{
  std::vector<SteeringEntity*> nearEntities;
  SteeringSystem* system=entity->getSteeringSystem();
  double sqrDistance=_distance*_distance;
  for (unsigned int i=0;i<system->getNbEntities();i++)
    {
      if (i!=entity->getId())
        {
          Vector3D toEntity=entity->getTransform()->getPosition()-
            system->getEntity(i)->getTransform()->getPosition();
          double sqrdist=toEntity.getSqrModule();
          if (sqrdist<sqrDistance)
            {
              nearEntities.push_back(system->getEntity(i));
            }
        }
    }
  //compute steering force
  Vector3D steeringForce;
  for (unsigned int i=0;i<nearEntities.size();i++)
    {
      Vector3D toEntity=entity->getTransform()->getPosition()-
        nearEntities[i]->getTransform()->getPosition();
      toEntity.normalize();
      steeringForce=steeringForce+toEntity;
    }
 
  return steeringForce;
}
