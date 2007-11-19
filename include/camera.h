#ifndef CAMERA_H
#define CAMERA_H

#include "entity.h"

class Camera
{
 public:
  Camera();
  virtual ~Camera();

  virtual void setPosition(Vector3D position);
  virtual void setLookAt(Vector3D lookAt);
  virtual void setOrientation(Vector3D orientation);

  virtual void setPosition(double x,double y ,double z);
  virtual void setLookAt(double x,double y ,double z);
  virtual void setOrientation(double x,double y ,double z);

  virtual Vector3D getPosition() const {return _position;}
  virtual Vector3D getOrientation();

  inline void setFov(double fov) {_fov=fov;}
  inline void setRatio(double ratio) {_ratio=ratio;}

  virtual Vector3D getRight();
  virtual Vector3D getForward();
  virtual Vector3D getUp();

  virtual void move(double speed);
  virtual void strafe(double speed);
  virtual void up(double speed);

  virtual void setPerspective();
  virtual void setActive();

 private:
  Vector3D _orientation;//temporairement ne attendant de les calculer
  Vector3D _position,_lookAt,_up;
  double _fov,_ratio,_near,_far;
};

#endif
