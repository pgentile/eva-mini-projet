#include "light.h"

#ifdef DEBUG
#include <GL/glut.h>
#endif

int Light::_number=0;

Light::Light()
{
  switch (_number)
    {
    case 0:_index=GL_LIGHT0;break;
    case 1:_index=GL_LIGHT1;break;
    case 2:_index=GL_LIGHT2;break;
    case 3:_index=GL_LIGHT3;break;
    case 4:_index=GL_LIGHT4;break;
    case 5:_index=GL_LIGHT5;break;
    case 6:_index=GL_LIGHT6;break;
    case 7:_index=GL_LIGHT7;break;
    }
  _number++;
}

Light::~Light()
{
  //TODO: what happen if we destroy light number 4?
  _number--;
}

void Light::apply()
{
  glLightfv(_index,GL_POSITION,_position);
  glLightfv(_index,GL_SPOT_DIRECTION,_spotDirection);
#ifdef DEBUG
  glPushMatrix();
  glDisable(GL_LIGHTING);
  glTranslatef(_position[0],_position[1],_position[2]);
  glutWireSphere(10.0,5,5);
  glEnable(GL_LIGHTING);
  glPopMatrix();
#endif
}

void Light::on()
{
  glEnable(_index);
}

void Light::off()
{
  glDisable(_index);
}
