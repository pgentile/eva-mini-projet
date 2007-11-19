#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <cmath>

#include "vector-3d.h"


class Transform
{
public:
  Transform();
  virtual ~Transform();

  inline void setPosition(double x,double y,double z)
  {
    _position.setX(x);
    _position.setY(y);
    _position.setZ(z);
  }
  inline void setPosition(const Vector3D& pos)
  {
    _position=pos;
  }
  inline void setOrientation(double x,double y,double z)
  {
    _orientation.setX(x);
    _orientation.setY(y);
    _orientation.setZ(z);
  }
  inline void setOrientation(const Vector3D& orient)
  {
    _orientation=orient;
  }
  inline void setScale(double x,double y,double z)
  {
    _scale.setX(x);
    _scale.setY(y);
    _scale.setZ(z);
  }
  inline void setScale(const Vector3D& scale)
  {
    _scale=scale;
  }

  inline Vector3D getPosition() const {return _position;}
  inline Vector3D getOrientation() const {return _orientation;}
  inline Vector3D getScale() const {return _scale;}

  virtual void apply();

protected:
private:
  Vector3D _position;
  Vector3D _orientation;
  Vector3D _scale;
  Vector3D _forward,_up,_right;//cached local axis
};


#endif
