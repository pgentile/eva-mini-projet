#ifndef CAR_TRACK_H
#define CAR_TRACK_H

#include "baseshapes.h"
#include "traffic-light.h"

class CarTrack:public Entity
{
public:
    CarTrack(TrafficLight* light);
    virtual ~CarTrack();
    
    inline Vector3D getPoint(unsigned int index) const
    {
        return _trackPoints[index];
    }
    inline unsigned int getNbPoints() const
    {
        return _trackPoints.size();
    }
    inline TrafficLight* getTrafficLight()
    {
        return _light;
    }
    
    virtual void render();
    
protected:
    virtual void initTrack();
    virtual void initTrackShape();
private:
    std::vector<Vector3D> _trackPoints;
    TrafficLight* _light;
};

#endif
