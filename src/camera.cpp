#include "camera.h"

#include <GL/gl.h>
#include <GL/glu.h>

Camera::Camera()
{
  _lookAt=Vector3D(1,0,0);
  _up=Vector3D(0,0,1);
  _position=Vector3D(0,0,0);
  _fov=80;
  _ratio=1;
  _near=1;
  _far=10000;
  //cout<<"up:"<<getUp()<<endl<<"right:"<<getRight()<<endl<<"forward:"<<getForward()<<endl;

  
}

Camera::~Camera()
{}

void Camera::setPosition(Vector3D position) {_position=position;}

void Camera::setLookAt(Vector3D lookAt) 
{
  _lookAt=lookAt;
}

void Camera::setOrientation(Vector3D orientation) 
{
  Vector3D direction;
  float	angle;
  float	sr, sp, sy, cr, cp, cy;
  _orientation=orientation;
	
  angle = orientation.getY() * (M_PI/180);
  sy = sin(angle);
  cy = cos(angle);
  angle = orientation.getX() * (M_PI/180);
  sp = sin(angle);
  cp = cos(angle);
  angle = orientation.getZ() * (M_PI/180);
  sr = sin(angle);
  cr = cos(angle);

  //forward
  direction.setX(cp*cy);
  direction.setY(cp*sy);
  direction.setZ(-sp);
  setLookAt(_position+direction);
  //up
  _up.setX((cr*sp*cy+-sr*-sy));
  _up.setY((cr*sp*sy+-sr*cy));
  _up.setZ(cr*cp);
}

void Camera::setPosition(double x,double y ,double z) {setPosition(Vector3D(x,y,z));}

void Camera::setLookAt(double x,double y ,double z) {setLookAt(Vector3D(x,y,z));}

void Camera::setOrientation(double x,double y ,double z)
{
  setOrientation(Vector3D(x,y,z));
}

Vector3D Camera::getRight()
{
  Vector3D right=getForward().produitVectoriel(getUp());
  right.normalize();
  return right;
}

Vector3D Camera::getForward()
{
  Vector3D view=(_lookAt-_position);
  view.normalize();
  return view;
}

Vector3D Camera::getUp()
{
  _up.normalize();
  return _up;
}

Vector3D Camera::getOrientation()
{
  return _orientation;
}

void Camera::move(double speed)
{
  Vector3D view=getForward();
  view.normalize();
  _position=_position+speed*view;
  _lookAt=_lookAt+speed*view;
  //cout<<"up:"<<getUp()<<endl<<"right:"<<getRight()<<endl<<"forward:"<<getForward()<<endl;
}

void Camera::strafe(double speed)
{
  Vector3D view=getRight();
  view.normalize();
  //cout<<"right:"<<view<<endl;
  _position=_position+speed*view;
  _lookAt=_lookAt+speed*view;
}

void Camera::up(double speed)
{
  Vector3D view=getUp();
  view.normalize();
  //cout<<"right:"<<view<<endl;
  _position=_position+speed*view;
  _lookAt=_lookAt+speed*view;
}

void Camera::setPerspective()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(_fov,_ratio,_near,_far);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
 
}

void Camera::setActive() 
{

  gluLookAt(_position.getX(),_position.getY(),_position.getZ(),_lookAt.getX(),_lookAt.getY(),_lookAt.getZ(),_up.getX(),_up.getY(),_up.getZ());
}
