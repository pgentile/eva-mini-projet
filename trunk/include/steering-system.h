#ifndef STEERING_SYSTEM_H
#define STEERING_SYSTEM_H

#include <vector>

class SteeringEntity;

class SteeringSystem
{
public:
  SteeringSystem();
  virtual ~SteeringSystem();

  inline unsigned int addEntity(SteeringEntity* entity)
  {
    _entities.push_back(entity);
    return _entities.size();
  }
  inline SteeringEntity* getEntity(unsigned int index)
  {
    return _entities[index];
  }
  inline unsigned int getNbEntities() const
  {
    return _entities.size();
  }

  
private:
  std::vector<SteeringEntity*> _entities;
};

#endif
