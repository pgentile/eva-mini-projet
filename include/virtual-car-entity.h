#ifndef VIRTUAL_CAR_ENTITY_H
#define	VIRTUAL_CAR_ENTITY_H

#include "steering-entity.h"

class VirtualCarEntity: public SteeringEntity
{

public:
    
    VirtualCarEntity(SteeringSystem* system);
    
    virtual void update(double dt);

};

#endif
