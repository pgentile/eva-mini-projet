#ifndef TEXTURE_H
#define TEXTURE_H

#include "load_texture.h"

class Texture
{
 public:
  Texture(char* filename,unsigned int mode,unsigned int tex_env_mode);
  Texture(const Texture& texture);
  virtual ~Texture();

  virtual unsigned int getIndex() const {return _index;}

  virtual void select();//choisi cet objet comme texture courante opengl

 private:
  unsigned int _index;
  unsigned int _mode,_envMode;
};

#endif
