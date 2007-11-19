

#include "entity.h"

#include <GL/gl.h>

Entity::Entity()
{
  _shape=NULL;
}

Entity::~Entity()
{
}

void Entity::render()
{
  glPushMatrix();
  _transform.apply();
  if (_shape)
    {
      _shape->render();
    }
  glPopMatrix();
}

//---------------------------------------



