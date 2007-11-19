#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"

#include <iostream>

class Material
{
public:
  Material();
  virtual ~Material();

  inline void setAmbient(float r,float g,float b,float alpha=1.0)
  {
    _ambient[0]=r;  _ambient[1]=g;  _ambient[2]=b;  _ambient[3]=alpha;
  }
  inline void setDiffuse(float r,float g,float b,float alpha=1.0)
  {
    _diffuse[0]=r;  _diffuse[1]=g;  _diffuse[2]=b;  _diffuse[3]=alpha;
  }
  inline void setSpecular(float r,float g,float b,float alpha=1.0)
  {
    _specular[0]=r;  _specular[1]=g;  _specular[2]=b;  _specular[3]=alpha;
  }
  inline void setEmission(float r,float g,float b,float alpha=1.0)
  {
    _emission[0]=r;  _emission[1]=g;  _emission[2]=b;  _emission[3]=alpha;
  }

  inline void setShininess(int shininess) {_shininess=shininess;}

  inline void setTexture(Texture* texture) {_texture=texture;}

  virtual void apply();

  inline bool hasTexture() {return (_texture!=NULL);}

protected:
private:
  float _ambient[4];
  float _diffuse[4];
  float _specular[4];
  float _emission[4];
  int _shininess;
  Texture* _texture;
};


#endif
