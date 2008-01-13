#include "virtual-car-entity.h"
#include "steering-behavior.h"

VirtualCarEntity::VirtualCarEntity(SteeringSystem* system): SteeringEntity(system), _delay(0.0) {
}

void VirtualCarEntity::update(double dt) {
    _delay += dt;
    
    Vector3D newPosition =
            _estimatedPosition
            + _estimatedSpeed * _delay
            + _estimatedAcceleration * _delay * _delay;
    _fleeBehavior.setTarget(newPosition);
    
    SteeringEntity::update(dt);
}

void VirtualCarEntity::correct(double delay, Vector3D position, Vector3D speed, Vector3D acceleration) {
    _estimatedPosition = position;
    _estimatedSpeed = speed;
    _estimatedAcceleration = acceleration;
    
    Vector3D newPosition =
            position
            + speed * delay
            + acceleration * delay * delay;
    _fleeBehavior.setTarget(newPosition);
}

double VirtualCarEntity::_getCurrentTime(void) {
    struct timeval t;
    gettimeofday(&t, NULL);
    double sec = (double) t.tv_sec;
    double usec = (double) t.tv_usec * 0.000001;
    return sec + usec;
}
