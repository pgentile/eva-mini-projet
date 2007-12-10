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
{
}

void CarTrack::initTrack()
{  
  double radius=100;
  double xoffset=200;
  double yoffset=100;
  int i;

  for (i=120;i<360;i+=10)
  {
    double x=radius*cos(i*M_PI/180)+xoffset;
    double y=radius*sin(i*M_PI/180)+yoffset;
    std::cout<<"x= "<<x<<" ; y= "<<y<<std::endl;
    _trackPoints.push_back(Vector3D(x,y,0));
  }
	
  for (i=1;i<60;i+=10)
  {
    double x=radius*cos(i*M_PI/180)+xoffset;
    double y=radius*sin(i*M_PI/180)+yoffset;
    std::cout<<"x= "<<x<<" ; y= "<<y<<std::endl;
    _trackPoints.push_back(Vector3D(x,y,0));
  }

  _trackPoints.push_back(Vector3D(200,200,0));

  xoffset=200;
  yoffset=300;
  for (i=238;i>0;i-=10)
  {
    double x=radius*cos(i*M_PI/180)+xoffset;
    double y=radius*sin(i*M_PI/180)+yoffset;
    std::cout<<"x= "<<x<<" ; y= "<<y<<std::endl;
    _trackPoints.push_back(Vector3D(x,y,0));
  }

  for (i=360;i>300;i-=10)
  {
    double x=radius*cos(i*M_PI/180)+xoffset;
    double y=radius*sin(i*M_PI/180)+yoffset;
    std::cout<<"x= "<<x<<" ; y= "<<y<<std::endl;
    _trackPoints.push_back(Vector3D(x,y,0));
  }
    
  initRoadBlocks();
}

void CarTrack::initRoadBlocks()
{
    // TODO
    std::vector<Vector3D>::iterator it;
    
    for( it = _trackPoints.begin() ; it != _trackPoints.end(); )
    {	
		Vector3D currentPoint = *it;
		if(it!=	_trackPoints.end()- 1)
		{       		
       		Vector3D nextPoint = *(it+1);
       		RoadBlock * tmpRB = new RoadBlock(4.0, currentPoint, nextPoint);
       		_roadBlocks.push_back(tmpRB);
       		++it;
		}
		else
		{
			Vector3D firstPoint = *_trackPoints.begin();
			RoadBlock * tmpRB = new RoadBlock(4.0, currentPoint, firstPoint);
       		_roadBlocks.push_back(tmpRB);
       		++it;
		}
    }
}

void CarTrack::initTrackShape()
{
  Shape* shape   = new Shape();
  Polyline* part = new Polyline();
  part->setPoints(&_trackPoints);
  shape->addPart(part);
  setShape(shape);
}


void CarTrack::render()
{
    glPushMatrix();
        _transform.apply();
        if (_shape)
        {
            _shape->render();
        }
    glPopMatrix();
    
    // Rendering Road Blocks
    std::vector< RoadBlock *>::iterator it;
    for( it = _roadBlocks.begin() ; it != _roadBlocks.end() ; ++it )
    {
        (*it)->render();
    }
    
}

