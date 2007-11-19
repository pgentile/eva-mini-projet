#include "traffic-light.h"
#include "baseshapes.h"

TrafficLight::TrafficLight()
{
  _stop=false;
  _distance=30.0;
  initShape();
}

TrafficLight::~TrafficLight()
{}

void TrafficLight::update(double dt)
{
  //set material color based on _stop flag
  if (_stop)
    {
      getShape()->getPart(0)->getMaterial()->setAmbient(1.0,0.0,0.0);
    }
  else
    {
      getShape()->getPart(0)->getMaterial()->setAmbient(1.0,1.0,1.0);
    }
}

void TrafficLight::initShape()
{
  Shape* shape=new Shape();
  ShapePart* part=new Teapot();
  part->getTransform()->setScale(10.0,10.0,10.0);
  shape->addPart(part);
  setShape(shape);
}

