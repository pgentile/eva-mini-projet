#include "shape.h"
#include <iostream>

#include <GL/gl.h>

//-------------------------------------

Shape::Shape()
{
  _displayList=0;
  _compiled=false;
}

Shape::~Shape()
{
  for (unsigned int i=0;i<_parts.size();i++)
    {
      delete _parts[i];
    }
}

void Shape::compile()
{
  _compiled=true;
  _displayList=glGenLists(1);
  std::cout<<"Compiled in list: "<<_displayList<<std::endl;
  glNewList(_displayList,GL_COMPILE);
  for (unsigned int i=0;i<_parts.size();i++)
    {
      glPushMatrix();
      _parts[i]->transform();
      if (_parts[i]->getMaterial()->hasTexture()) {glEnable(GL_TEXTURE_2D);}
      _parts[i]->applyMaterial();
      _parts[i]->render();
      if (_parts[i]->getMaterial()->hasTexture()) {glDisable(GL_TEXTURE_2D);}
      glPopMatrix();
    }
  glEndList();
}

void Shape::render()
{
  if (_compiled)
    {
      glCallList(_displayList);
    }
  else
    {
      for (unsigned int i=0;i<_parts.size();i++)
        {
          glPushMatrix();
          _parts[i]->transform();
          if (_parts[i]->getMaterial()->hasTexture())
            {glEnable(GL_TEXTURE_2D);}
          _parts[i]->applyMaterial();
          _parts[i]->render();
          if (_parts[i]->getMaterial()->hasTexture())
            {glDisable(GL_TEXTURE_2D);}
          glPopMatrix();
        }
    }
}

