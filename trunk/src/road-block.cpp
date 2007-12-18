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
    
    glPushMatrix();
    // ---- Renders a Road Block between StartPoint(xs,ys,zs) and EndPoint(xe,ye,ze)   ----
    
    Vector3D rbVector       = _endPoint - _startPoint ;
    Vector3D rbNormalVector(0.,0.,-1.);
    //Vector3D rbNormalVector = _endPoint - _startPoint ;
    
    
    rbVector.normalize();
    
    // Setting up Normal vector to roadBlock
    //rbNormalVector.normalize();
    //rbNormalVector.rotate( 0 , M_PI /2 , 0 );
   
    
    // Building Road Block Points
    Vector3D widthVector    = rbVector.crossProduct( rbNormalVector ) * _width;
    
    Vector3D firstPoint  = _startPoint + widthVector - rbNormalVector * (ROAD_HEIGHT / 2);
    Vector3D secondPoint = _startPoint - widthVector - rbNormalVector * (ROAD_HEIGHT / 2);
    Vector3D thirdPoint  = _endPoint   - widthVector - rbNormalVector * (ROAD_HEIGHT / 2);
    Vector3D fourthPoint = _endPoint   + widthVector - rbNormalVector * (ROAD_HEIGHT / 2);
    
    #ifdef RB_DEBUG
        std::cout << "-----------"  << std::endl;
        std::cout << "RB : First Point = " << firstPoint << std::endl;
        std::cout << "RB : Second Point = " << secondPoint << std::endl;
        std::cout << "RB : Third Point = " << thirdPoint << std::endl;
        std::cout << "RB : Fourth Point = " << fourthPoint << std::endl;
    #endif
    
    glBegin(GL_QUADS);
        glNormal3f(rbNormalVector.getX(),rbNormalVector.getY(),rbNormalVector.getZ());
        glTexCoord2f(1,1);
        glVertex3f( firstPoint.getX()  , firstPoint.getY()  , 0 );
        glTexCoord2f(0,1);
        glVertex3f( secondPoint.getX() , secondPoint.getY() , 0 );
        glTexCoord2f(0,0);
        glVertex3f( thirdPoint.getX()  , thirdPoint.getY()  , 0 );
        glTexCoord2f(1,0);
        glVertex3f( fourthPoint.getX() , fourthPoint.getY() , 0 );
    glEnd();     
    
    glPopMatrix();
}


