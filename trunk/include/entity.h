#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "transform.h"
#include "shape.h"
#include "scene.h"

//Base scene object
class Entity
{
public:
  Entity();
  virtual ~Entity();

  virtual void render();
  virtual void update(double dt) {}

  inline Shape* getShape() {return _shape;}
  inline void setShape(Shape* shape) {_shape=shape;}

  inline Transform* getTransform() {return &_transform;}

protected:
private:
  Shape* _shape;
  Transform _transform;
};



#endif

