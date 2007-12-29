#include "scene.h"

double Scene::currentDt_ = 0.1;

Scene::Scene()
{
  
  _currentCamera=-1;
}

Scene::~Scene()
{
  //Clean objects
  for (unsigned int i=0;i<_entities.size();i++)
    {
      delete _entities[i];
    }
  for (unsigned int i=0;i<_cameras.size();i++)
    {
      delete _cameras[i];
    }
}

void Scene::render()
{
  for (unsigned int i=0;i<_entities.size();i++)
  {
     _entities[i]->render();
  }
}

void Scene::update(double dt)
{
  Scene::currentDt_ = dt;
  for (unsigned int i=0;i<_entities.size();i++)
    {
      _entities[i]->update(dt);
    }
}
