#include "vector-3d.h"
#include <iostream>
#include <GL/gl.h>

Vector3D::Vector3D():_x(0),_y(0),_z(0)
{}

Vector3D::Vector3D(double x,double y,double z):_x(x),_y(y),_z(z)
{}

Vector3D::~Vector3D()
{}

Vector3D operator*(const double& x,const Vector3D& v)
{
 Vector3D result=Vector3D();
 result.setX(x*v.getX());
 result.setY(x*v.getY());
 result.setZ(x*v.getZ());
 return result;
}

Vector3D operator*(const Vector3D& v,const double& x)
{
 Vector3D result=Vector3D();
 result.setX(x*v.getX());
 result.setY(x*v.getY());
 result.setZ(x*v.getZ());
 return result;
}

Vector3D operator/(const Vector3D& v,const double& x)
{
 Vector3D result=Vector3D();
 result.setX(v.getX()/x);
 result.setY(v.getY()/x);
 result.setZ(v.getZ()/x);
 return result;
}

Vector3D operator+(const Vector3D& v1,const Vector3D& v2)
{
 Vector3D result=Vector3D();
 result.setX(v1.getX()+v2.getX());
 result.setY(v1.getY()+v2.getY());
 result.setZ(v1.getZ()+v2.getZ());
 return result;
}

Vector3D operator-(const Vector3D& v1,const Vector3D& v2)
{
 Vector3D result=Vector3D();
 result.setX(v1.getX()-v2.getX());
 result.setY(v1.getY()-v2.getY());
 result.setZ(v1.getZ()-v2.getZ());
 return result;
}

std::ostream& operator<<(std::ostream& s,const Vector3D& v)
{
 v.display(s);
 return s;
}

bool operator==(const Vector3D& v1,const Vector3D& v2)
{
  return((v1.getX()==v2.getX())&&
         (v1.getY()==v2.getY())&&
         (v1.getZ()==v2.getZ()));
}

bool operator!=(const Vector3D& v1,const Vector3D& v2)
{
  return (!operator==(v1,v2));
}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
  setX(v.getX());
  setY(v.getY());
  setZ(v.getZ());
  return *this;
}

void Vector3D::display(std::ostream& s) const
{
  s<<"("<<_x<<","<<_y<<","<<_z<<")"<<std::endl;
}


