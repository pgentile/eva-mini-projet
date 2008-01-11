#ifndef STEERING_ENTITY_H
#define STEERING_ENTITY_H

#include "entity.h"

#include "steering-system.h"
#include "steering-behavior.h"


class SteeringEntity:public Entity
{
public:
  SteeringEntity(SteeringSystem* system);
  virtual ~SteeringEntity();

  virtual void update(double dt);

  inline SteeringSystem* getSteeringSystem()
  {
    return _system;
  }

  inline unsigned int addBehavior(SteeringBehavior* behavior)
  {
    _behaviors.push_back(behavior);
    return _behaviors.size();
  }
  inline SteeringBehavior* getBehavior(unsigned int index)
  {
    return _behaviors[index];
  }
  inline unsigned int getId() const
  {
    return _id;
  }
  inline double getMass() const
  {
    return _mass;
  }
  inline void setMass(double mass)
  {
    _mass=mass;
  }
  inline void setMaxVelocity(double max)
  {
    _maxVelocity=max;
  }
  inline double getMaxVelocity() const
  {
    return _maxVelocity;
  }
  inline void setMaxAcceleration(double max)
  {
    _maxAcceleration=max;
  }
  inline double getMaxAcceleration() const
  {
    return _maxAcceleration;
  }
  inline void setVelocity(const Vector3D& vec)
  {
    _velocity=vec;
  }
  inline Vector3D getVelocity() const
  {
    return _velocity;
  }
  inline void setForward(const Vector3D& vec)
  {
    //extract X,Y and Z angles
    Vector3D dir=vec;
    dir.normalize();
    double ya=-asin(dir.getZ())*180/M_PI;
    double za=atan2(dir.getY(),dir.getX())*180/M_PI;
    //La direction seule ne permet pas de
    //d�erminer le roll on travaille dans le plan
    //pour simplifier les calculs donc on maintient
    //la rotation autour de l'axe X
    double xa=getTransform()->getOrientation().getX();
    getTransform()->setOrientation(xa,ya,za);
  }
  inline Vector3D getSide()
  {
    Vector3D result(0,1,0);
    Vector3D orientation=getTransform()->getOrientation();
    result.rotate(orientation.getX()*M_PI/180,
                  orientation.getY()*M_PI/180,
                  orientation.getZ()*M_PI/180);
    return result;
  }
  inline Vector3D getForward()
  {
    Vector3D result(1,0,0);
    Vector3D orientation=getTransform()->getOrientation();
    result.rotate(orientation.getX()*M_PI/180,
                  orientation.getY()*M_PI/180,
                  orientation.getZ()*M_PI/180);
    return result;
  }
  inline Vector3D getUp()
  {
    Vector3D result(0,0,1);
    Vector3D orientation=getTransform()->getOrientation();
    result.rotate(orientation.getX()*M_PI/180,
                  orientation.getY()*M_PI/180,
                  orientation.getZ()*M_PI/180);
    return result;
  }
  inline unsigned int getTarget()
  {
    return _currentTarget;
  }
  inline void setTarget(unsigned int pos)
  {
      _currentTarget=pos;
  }
  
  inline Vector3D getAcceleration()
  {
      return _acceleration;
  }
  
  inline void setAcceleration(Vector3D acceleration)
  {
      _acceleration = acceleration;
  }

protected:
  void initShape();
  unsigned int _currentTarget;
private:
  static Shape* _steeringShape;
  unsigned int _id;
  SteeringSystem* _system;
  double _maxVelocity;
  double _maxAcceleration;
  double _mass;
  Vector3D _velocity;
  Vector3D _acceleration;
  std::vector<SteeringBehavior*> _behaviors;
};

#endif
