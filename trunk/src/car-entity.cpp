#include "car-entity.h"


CarEntity::CarEntity(SteeringSystem* system,
                     CarTrack* track, unsigned int currentTarget):SteeringEntity(system)
{
  _track=track;
  _camera=NULL;
  _currentTarget = currentTarget + 1;
  _seek=new SeekBehavior();
  _arrive=new ArriveBehavior();
  _separation=new SeparationBehavior();
  _priority=new PriorityBehavior();
  _stayOnTrack = new StayOnTrackBehavior();
  addBehavior(_seek);
  addBehavior(_arrive);
  addBehavior(_stayOnTrack);
  addBehavior(_separation);
  addBehavior(_priority);
  _seek->setTarget(_track->getPoint(_currentTarget));
  _arrive->setWeight(0.0);
  _priority->setWeight(5.0);


  _oldTarget = _track->getPoint(_currentTarget);
}

CarEntity::~CarEntity()
{}

Vector3D CarEntity::getCurrentTarget()
{
    return _track->getPoint(_currentTarget);
}

// Methodes pour respecter la distance de securite

std::vector<SteeringEntity*> CarEntity::getNearEntities(double minDist, double maxDist, double minAngleDeg, double maxAngleDeg)
{
    std::vector<SteeringEntity*> nearEntities;
    SteeringSystem* system = this->getSteeringSystem();
    for ( unsigned int i = 0; i < system->getNbEntities(); i++ ) {
        if ( i != this->getId() ) {

            Vector3D toEntity = system->getEntity (i)->getTransform()->getPosition() - this->getTransform()->getPosition();
            double dist = toEntity.getModule();
            double angleRad = (this->getForward()).getAngle(toEntity);
            double angleDeg = (angleRad/M_PI)*180.0;

            if ( dist <= maxDist && dist >= minDist && angleDeg <= maxAngleDeg && angleDeg >= minAngleDeg) {
                nearEntities.push_back ( system->getEntity(i) );
            }
        }
    }
    return nearEntities;
}

std::vector<SteeringEntity*> CarEntity::getNearEntities()
{
    std::vector<SteeringEntity*> nearEntities;
    SteeringSystem* system = this->getSteeringSystem();
    for ( unsigned int i = 0; i < system->getNbEntities(); i++ ) {
        if ( i+1 != this->getId() ) {
            Vector3D toEntity = system->getEntity(i)->getTransform()->getPosition() - this->getTransform()->getPosition();
            double dist = toEntity.getModule();

            double scal = (this->getForward()).produitScalaire(toEntity);

            if (dist <= 10.0 && dist >= 0.0 && scal > 0.0) {
                nearEntities.push_back( system->getEntity(i) );
            }
        }
    }
    return nearEntities;
}

SteeringEntity* CarEntity::getNearestEntity(std::vector<SteeringEntity*> nearEntities)
{
    SteeringEntity* nearestEntity = (SteeringEntity*)0;
    double distance = 1000.0;
    Vector3D position = this->getTransform()->getPosition();

    for (unsigned int i = 0; i != nearEntities.size(); i++) {

        Vector3D toEntity = nearEntities[i]->getTransform()->getPosition() - position;
        if (toEntity.getModule() < distance) {
            nearestEntity = nearEntities[i];
        }
    }

    return nearestEntity;
}

void CarEntity::_securityTest(SteeringEntity* nearestEntity)
{
    _securityOn = false;
    if (nearestEntity != (SteeringEntity*)0 ) {
        Vector3D position = getTransform()->getPosition();
        Vector3D nearestEntityPosition = nearestEntity->getTransform()->getPosition();
        Vector3D toEntity = nearestEntityPosition - position;

        // std::cerr << "dist detectee -> " << toEntity.getModule() << std::endl;
        if (toEntity.getModule() < 10.0) {

            this->setVelocity(Vector3D(0.0, 0.0, 0.0));
         
        }

    }
}

Vector3D CarEntity::getPreviousTarget()
{
    return _track->getPreviousPoint(_currentTarget );
}

void CarEntity::update(double dt)
{
    // Detection des entites et de l'entite la plus proche
    std::vector<SteeringEntity*> nearEntities = getNearEntities(/*0.0, 20.0, -90.0, 90.0*/);
    SteeringEntity* nearestEntity = getNearestEntity(nearEntities);
    
    //check the traffic light
    TrafficLight* light=_track->getTrafficLight();
    double light_dist=(getTransform()->getPosition()- light->getTransform()->getPosition()).getModule();
    
    if ( (light->isStop())&&(light_dist<light->getDistance()) && this->getTarget() == 0)
    {
        // TrafficLight is On
        _arrive->setTarget(light->getTransform()->getPosition());
        _arrive->setWeight(1.0);
        _seek->setWeight(0.0);
        _separation->setWeight(4.0);
        
        // Distance de securite
        //_securityTest(nearestEntity);
    }
    else
    {
        _priority->setWeight(0.0);
        _separation->setWeight(0.5);
        _seek->setWeight(1.0);
        _arrive->setWeight(0.0);
        
        //check if we are at the required point
        Vector3D toTarget=_track->getPoint(_currentTarget)-
        getTransform()->getPosition();
        if (toTarget.getModule()<10.0)
        { 
            if (_currentTarget== (_track->getNbPoints() - 1  ))
            {
                _currentTarget=0;
            }
            else
            {
                _currentTarget++;
            }
            ((SeekBehavior*)getBehavior(0))->setTarget(_track->getPoint(_currentTarget));
        }
        
        // Distance de securite
        //_securityTest(nearestEntity);
    }
    
    SteeringEntity::update(dt);
    _securityTest(nearestEntity);
    
    if (_camera)
    {
        //Update camera parameters
        _camera->setPosition(getTransform()->getPosition()-3.0*getForward()+Vector3D(0,0,3.0));
        _camera->setLookAt(getTransform()->getPosition()+3.0*getForward());
    }

}
