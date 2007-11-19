#include "transform.h"
#include <iostream>
#include <GL/gl.h>


//-------------------------------------

Transform::Transform():_position(0,0,0),_orientation(0,0,0),_scale(1,1,1)
{
}

Transform::~Transform()
{}

void Transform::apply()
{
  //TODO: problem with the order of transformations
  glTranslatef(_position.getX(),_position.getY(),_position.getZ());
  glRotatef(_orientation.getZ(),0,0,1);
  glRotatef(_orientation.getY(),0,1,0);
  glRotatef(_orientation.getX(),1,0,0);
  glScalef(_scale.getX(),_scale.getY(),_scale.getZ());
}
