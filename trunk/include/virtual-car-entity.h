#ifndef VIRTUAL_CAR_ENTITY_H
#define	VIRTUAL_CAR_ENTITY_H

#include "steering-entity.h"
#include "flee-behavior.h"

class VirtualCarEntity: public SteeringEntity
{

public:
    
    VirtualCarEntity(SteeringSystem* system);
    
    virtual void update(double dt);
    
    void correct(double time, Vector3D position, Vector3D speed, Vector3D acceleration);

private:
    
    double _getCurrentTime(void);
    
    FleeBehavior _fleeBehavior;
    
    double _delay;
    
    Vector3D _estimatedPosition, _estimatedSpeed, _estimatedAcceleration;

};

#endif
