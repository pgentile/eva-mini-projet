#include "material.h"

#include <GL/gl.h>

Material::Material()
{ 
  _ambient[0]=1.0;  _ambient[1]=1.0;  _ambient[2]=1.0;  _ambient[3]=1.0;
  _diffuse[0]=1.0;  _diffuse[1]=1.0;  _diffuse[2]=1.0;  _diffuse[3]=1.0;
  _specular[0]=1.0;  _specular[1]=1.0;  _specular[2]=1.0;  _specular[3]=1.0;
  _emission[0]=0.0;  _emission[1]=0.0;  _emission[2]=0.0;  _emission[3]=1.0;
  _shininess=100;

  _texture=NULL;
}

Material::~Material()
{}

void Material::apply()
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, _emission);
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, _shininess);

  if (_texture)
    {
      
      _texture->select();
      
    }

}
