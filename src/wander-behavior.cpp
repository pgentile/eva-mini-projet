#include "wander-behavior.h"
#include "macros.h"

WanderBehavior::WanderBehavior()
{
  _distance=0.0;
  _radius=10.0;
  _jitter=5.0;
}


WanderBehavior::~WanderBehavior()
{}

Vector3D WanderBehavior::compute(SteeringEntity* entity)
{
  _localTarget=_localTarget+Vector3D(RANDOM_NUMBER(-_jitter,_jitter),
                                     RANDOM_NUMBER(-_jitter,_jitter),
                                     RANDOM_NUMBER(-_jitter,_jitter));
  _localTarget.normalize();
  _localTarget=_localTarget*_radius;
  std::cout<<"Local target: "<<_localTarget<<std::endl;
  _target=entity->getTransform()->getPosition()+
    _localTarget+_distance*entity->getForward();
  std::cout<<"Position: "<<entity->getTransform()->getPosition()<<std::endl;
  std::cout<<"Final target: "<<_target<<std::endl;
  return (_target-entity->getTransform()->getPosition());
}
