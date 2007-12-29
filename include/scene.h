#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "entity.h"
#include "light.h"

#include <vector>

class Entity;
class Camera;
class Scene
{
public:
  Scene();
  virtual ~Scene();

  virtual void render();
  virtual void update(double dt);
  
  inline void addEntity(Entity* entity) {_entities.push_back(entity);}
  inline Entity* getEntity(unsigned int index) {return _entities[index];}

  inline void addCamera(Camera* camera) {_cameras.push_back(camera);}
  inline Camera* getCamera(unsigned int index) {return _cameras[index];}
  inline unsigned int getNbCameras() const {return _cameras.size();}
 
  static double currentDt_; 

protected:
private:

  
  int _currentCamera;
  std::vector<Camera*> _cameras;
  std::vector<Entity*> _entities;
};

 
#endif
