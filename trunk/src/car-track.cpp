#include "car-track.h"
#include "macros.h"

CarTrack::CarTrack(TrafficLight* light)
{
  _light=light;
  initTrack();
  initTrackShape();
  //set the light position to the first track point
  _light->getTransform()->setPosition(_trackPoints[0]);
}

CarTrack::~CarTrack()
{}

void CarTrack::initTrack()
{
  //circular track
  //radius=500
  double radius=200;
  double xoffset=100;
  double yoffset=100;
  for (unsigned int i=1;i<360;i+=10)
    {
      double x=(RANDOM_NUMBER(0.0,10.0)+radius)*cos(i*M_PI/180)+xoffset;
      double y=(RANDOM_NUMBER(0.0,10.0)+radius)*sin(i*M_PI/180)+yoffset;
      std::cout<<"x= "<<x<<" ; y= "<<y<<std::endl;
      _trackPoints.push_back(Vector3D(x,y,RANDOM_NUMBER(0.0,20.0)));
    }
}

void CarTrack::initTrackShape()
{
  Shape* shape=new Shape();
  Polyline* part=new Polyline();
  part->setPoints(&_trackPoints);
  shape->addPart(part);
  setShape(shape);
}

