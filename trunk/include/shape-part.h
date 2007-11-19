#ifndef SHAPE_PART_H
#define SHAPE_PART_H

#include <vector>

#include "material.h"
#include "transform.h"

#include <GL/gl.h>

class ShapePart
{
public:
  ShapePart();
  virtual ~ShapePart();

  inline Transform* getTransform() {return &_transform;}
  inline Material* getMaterial() {return &_material;}

  virtual void applyMaterial();
  virtual void transform();
  virtual void render()=0;

  virtual void compile();

protected:
private:
  GLuint _displayList;
  Material _material;
  Transform _transform;
};

#endif
