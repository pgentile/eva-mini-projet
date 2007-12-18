#ifndef CAR_TRACK_H
#define CAR_TRACK_H

#include "baseshapes.h"
#include "traffic-light.h"
#include "road-block.h"

class CarTrack:public Entity
{
public:
    CarTrack(TrafficLight* light);
    virtual ~CarTrack();
    
    inline Vector3D getPoint(unsigned int index) const
    {
        return _trackPoints[index];
    }
    
    inline Vector3D getPreviousPoint(unsigned int index) const
    {
        if( index == 0 ) return _trackPoints[_trackPoints.size() - 1];
        else return _trackPoints[ index - 1 ];
    }
    
    inline unsigned int getNbPoints() const
    {
        return _trackPoints.size();
    }
    inline TrafficLight* getTrafficLight()
    {
        return _light;
    }
    
    inline double getTrackWidth()
    {
        return _trackWidth;
    }
    
    virtual void render();
    
protected:
    virtual void initTrack();
    virtual void initRoadBlocks();
    virtual void initTrackShape();
private:

    double _trackWidth;
    std::vector<RoadBlock *> _roadBlocks;
    std::vector<Vector3D> _trackPoints;
    TrafficLight* _light;
};

#endif
