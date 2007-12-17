#include "car-entity.h"

CarEntity::CarEntity(SteeringSystem* system,
                     CarTrack* track):SteeringEntity(system)
{
  _track=track;
  _camera=NULL;
  _currentTarget=0;
  _seek=new SeekBehavior();
  _arrive=new ArriveBehavior();
  _separation=new SeparationBehavior();
  _stayOnTrack = new StayOnTrackBehavior();
  
  addBehavior(_seek);
  addBehavior(_arrive);
  //addBehavior(_separation);
  addBehavior(_stayOnTrack);
  
  _seek->setTarget(_track->getPoint(_currentTarget));
  _arrive->setWeight(0.0);
  
}

CarEntity::~CarEntity()
{}

Vector3D CarEntity::getCurrentTarget()
{
    return _track->getPoint(_currentTarget);
}

Vector3D CarEntity::getPreviousTarget()
{
    return _track->getPoint(_currentTarget - 1);
}

void CarEntity::update(double dt)
{
    //check the traffic light
    TrafficLight* light = _track->getTrafficLight();
    double light_dist   = (getTransform()->getPosition()- light->getTransform()->getPosition()).getModule();
    
    if ((light->isStop())&&(light_dist<light->getDistance()))
    {
        // TrafficLight is On
        _arrive->setTarget(light->getTransform()->getPosition());
        _arrive->setWeight(1.0);
        _seek->setWeight(0.0);
        _separation->setWeight(0.0);
    }
    else
    {
        _separation->setWeight(0.5);
        _seek->setWeight(1.0);
        _arrive->setWeight(0.0);
           
        //check if we are at the required point
        Vector3D toTarget=_track->getPoint(_currentTarget) - getTransform()->getPosition();
        if (toTarget.getModule()<20.0)
        {
            _currentTarget++;
            if (_currentTarget==_track->getNbPoints()) _currentTarget=0;
            ((SeekBehavior*)getBehavior(0))->setTarget(_track->getPoint(_currentTarget));
        }
    }
    
    
    SteeringEntity::update(dt);
    
    if (_camera)
    {
        //Update camera parameters
        _camera->setPosition(getTransform()->getPosition()-3.0*getForward()+Vector3D(0,0,3.0));
        _camera->setLookAt(getTransform()->getPosition()+3.0*getForward());
    }
}
