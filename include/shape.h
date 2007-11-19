#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "material.h"
#include "transform.h"

#include <GL/gl.h>

#include "shape-part.h"

class Shape
{
public:
  Shape();
  virtual ~Shape();

  inline void addPart(ShapePart* part) {_parts.push_back(part);}
  inline ShapePart* getPart(unsigned int index) {return _parts[index];}

  virtual void compile();

  virtual void render();

protected:
private:
  GLuint _displayList;
  bool _compiled;
  std::vector<ShapePart*> _parts;
};

#endif
