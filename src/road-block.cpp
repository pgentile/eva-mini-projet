#include "road-block.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include "vector-3d.h"

RoadBlock::RoadBlock(double width, Vector3D startPoint, Vector3D endPoint)
:_width(width),_startPoint(startPoint),_endPoint(endPoint)
{
  
}

RoadBlock::~RoadBlock()
{}

void RoadBlock::render()
{

}
