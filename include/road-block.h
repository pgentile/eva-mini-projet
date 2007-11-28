#ifndef ROAD_BLOCK_H
#define ROAD_BLOCK_H

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
    double getWidth(void);
    void setWidth(width);
    Vector3D getStartPoint();
    void setStartPoint(Vector3D startPoint);
    Vector3D getEndPoint();
    void setEndPoint(Vector3D endPoint);

protected:
private:
  double _width;
  Vector3D _startPoint;
  Vector3D _endPoint;
};

#endif
