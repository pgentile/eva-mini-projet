#include "shape-part.h"
#include <iostream>

#include <GL/gl.h>

ShapePart::ShapePart()
{}

ShapePart::~ShapePart()
{

}

void ShapePart::compile()
{
}

void ShapePart::applyMaterial()
{
  _material.apply();
}

void ShapePart::transform()
{
  _transform.apply();
}

