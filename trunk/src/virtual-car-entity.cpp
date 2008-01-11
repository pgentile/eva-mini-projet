#include "virtual-car-entity.h"
#include "steering-behavior.h"

VirtualCarEntity::VirtualCarEntity(SteeringSystem* system): SteeringEntity(system)
{
}

void VirtualCarEntity::update(double dt)
{
    Vector3D velocity = getVelocity();
    velocity = velocity + getAcceleration() * dt;
    velocity.truncate(getMaxVelocity());
    
    setForward(velocity);
    
    Vector3D position = getTransform()->getPosition();
    position = position + velocity * dt;
    getTransform()->setPosition(position);
}
