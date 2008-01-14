#include "steering-entity.h"
#include "macros.h"
#include "baseshapes.h"

Shape* SteeringEntity::_steeringShape=NULL;

SteeringEntity::SteeringEntity(SteeringSystem* system)
{
    _maxVelocity=RANDOM_NUMBER(1.0,100.0);
    _maxAcceleration=RANDOM_NUMBER(1.0,100.0);
    _mass=RANDOM_NUMBER(1.0,100.0);
    _system=system;
    _id=system->addEntity(this);
    initShape();
}

SteeringEntity::~SteeringEntity()
{}

void SteeringEntity::update(double dt)
{
    Vector3D oldVelocity=_velocity;
    
    for (unsigned int i=0;i<_behaviors.size();i++)
    {
        _acceleration=_acceleration+
        _behaviors[i]->getWeight()*
        _behaviors[i]->compute(this);
    }
    
    _acceleration=_acceleration/_mass;
    _acceleration.truncate(_maxAcceleration);
    _velocity=_velocity+_acceleration*dt;
    _velocity.truncate(_maxVelocity);
    
    //update position & orientation
    Vector3D position=getTransform()->getPosition();
    setForward(_velocity);
    getTransform()->setPosition(position+_velocity*dt);
}

void SteeringEntity::initShape()
{
    //_steeringShape=new AntShape();
    
    /*
    _steeringShape = new Shape();
    ShapePart* part=new Axis();
    part->getTransform()->setScale(5,5,5);
    _steeringShape->addPart(part);
    part=new Sphere();
    _steeringShape->addPart(part);
    */
    
    
    _steeringShape = new Shape();
    ShapePart* part=new Car();
    part->getTransform()->setScale(0.6,0.6,0.6);
    part->getMaterial()->setAmbient(1.0,0.0,0.0);
    part->getMaterial()->setDiffuse(1.0,0.0,0.0);

    _steeringShape->addPart(part);
    

    setShape(_steeringShape);
	
}

