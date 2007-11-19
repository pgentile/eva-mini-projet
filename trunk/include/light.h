#ifndef LIGHT_H
#define LIGHT_H

#include <GL/gl.h>



class Light
{
 public:
  Light();//constructeur par défaut=>lumiere blanche omnidirectionnelle en (0,0,0)
  virtual ~Light();

  inline void setPosition(float x,float y,float z)
  {
    _position[0]=x; _position[1]=y; _position[2]=z; _position[3]=1.0;
  }
  inline void setDirection(float x,float y,float z)
  {
    _position[0]=x; _position[1]=y; _position[2]=z; _position[3]=0.0;
  }
  inline void setSpotDirection(float x,float y,float z)
  {
    _spotDirection[0]=x; _spotDirection[1]=y; _spotDirection[2]=z; 
  }

  inline void setAmbient(float r,float g,float b)
  {
    _ambient[0]=r; _ambient[1]=g; _ambient[2]=b; _ambient[3]=1.0;
    glLightfv(_index,GL_AMBIENT,_ambient);
  }
  inline void setDiffuse(float r,float g,float b)
  {
    _diffuse[0]=r; _diffuse[1]=g; _diffuse[2]=b; _diffuse[3]=1.0;
    glLightfv(_index,GL_DIFFUSE,_diffuse);
  }
  inline void setSpecular(float r,float g,float b)
  {
    _specular[0]=r; _specular[1]=g; _specular[2]=b; _specular[3]=1.0;
    glLightfv(_index,GL_SPECULAR,_specular);
  }

  inline void setConstantAttenuation(float value)
  {
    _constantAttenuation=value;
    glLightf(_index,GL_CONSTANT_ATTENUATION,_constantAttenuation);
  }


  inline void setLinearAttenuation(float value)
  {
    _linearAttenuation=value;
    glLightf(_index,GL_LINEAR_ATTENUATION,_linearAttenuation);
  }


  inline void setQuadraticAttenuation(float value)
  {
    _quadraticAttenuation=value;
    glLightf(_index,GL_QUADRATIC_ATTENUATION,_quadraticAttenuation);
  }

  inline void setSpotExponent(float value)
  {
    _spotExponent=value;
    glLightf(_index,GL_SPOT_EXPONENT,_spotExponent);
  }

  inline void setSpotCutOff(float value)
  {
    _spotCutOff=value;
    glLightf(_index,GL_SPOT_CUTOFF,_spotCutOff);
  }

  virtual void apply();
  virtual void on();
  virtual void off();


 private:
  int _index;
  float _constantAttenuation,_linearAttenuation,_quadraticAttenuation,_spotExponent,_spotCutOff;
  float _ambient[4],_diffuse[4],_specular[4],_position[4],_spotDirection[3];
  static int _number;
};

#endif
