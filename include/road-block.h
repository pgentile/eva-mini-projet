#ifndef ROAD_BLOCK_H
#define ROAD_BLOCK_H

#define ROAD_HEIGHT 1.0
#include "vector-3d.h"
#include "shape.h"
#include "shape-part.h"

class RoadBlock : public ShapePart
{
public:
    RoadBlock(double width, Vector3D startPoint, Vector3D endPoint);
    virtual ~RoadBlock();

    virtual void render();
    
    /* Getters & setters */
    inline double getWidth(void){ return _width; }
    inline void setWidth(double width) { _width = width; }
    inline Vector3D getStartPoint(){ return _startPoint; }
    inline void setStartPoint(Vector3D startPoint){ _startPoint = startPoint; }
    inline Vector3D getEndPoint(){ return _endPoint; }
    inline void setEndPoint(Vector3D endPoint){ _endPoint = endPoint; }

protected:
private:
  double _width;
  Vector3D _startPoint;
  Vector3D _endPoint;
};

#endif
