#include "texture.h"
#include <iostream>

#include <GL/gl.h>
#include <GL/glu.h>


Texture::Texture(char* filename,unsigned int mode,unsigned int tex_env_mode):_mode(mode),_envMode(tex_env_mode)
{
  unsigned * image;
  int width;
  int height;
  int components;
  glEnable(GL_TEXTURE_2D); 
  image = read_texture(filename, &width, &height, &components);
  glGenTextures(1, &_index);
  glBindTexture(GL_TEXTURE_2D, _index);


  gluBuild2DMipmaps( GL_TEXTURE_2D, components, width, height,GL_RGBA, GL_UNSIGNED_BYTE, image);
  glDisable(GL_TEXTURE_2D);
}

Texture::Texture(const Texture& texture)
{
  _index=texture.getIndex();
}

Texture::~Texture()
{}

void Texture::select() 
{
  
  glBindTexture(GL_TEXTURE_2D, _index);
 
 glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,_mode);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,_mode);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,_envMode);
}
