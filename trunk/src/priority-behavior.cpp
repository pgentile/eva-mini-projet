#include "priority-behavior.h"
#include "steering-entity.h"
#include "macros.h"

PriorityBehavior::PriorityBehavior()
{
    setWeight(5.0);
}

PriorityBehavior::~PriorityBehavior()
{}

Vector3D PriorityBehavior::compute(SteeringEntity* entity)
{
    std::vector<SteeringEntity*> entities;
    SteeringSystem* system = entity->getSteeringSystem();
    for ( unsigned int i = 0; i < system->getNbEntities(); i++ ) {
        if ( i+1 != entity->getId() ) {
            if (entity->getTarget() == 30 /* Croisement au niveau du circuit */ && system->getEntity(i)->getTarget() == 0 /* Point apres croisement: le feu */) {
                entity->setVelocity(Vector3D(0.0, 0.0, 0.0));
                return Vector3D(0.0, 0.0, 0.0);
            }
        }
    }
    return entity->getVelocity();
}
