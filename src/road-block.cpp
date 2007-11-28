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
    // Renders a Road Block between StartPoint(xs,ys,zs) and EndPoint(xe,ye,ze)
    glBegin(GL_QUADS);
        // TODO
    glEnd();     
}


