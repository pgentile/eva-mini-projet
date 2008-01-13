#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "entity.h"

class TrafficLight:public Entity
{
public:
  TrafficLight();                          
  virtual ~TrafficLight();

  virtual void update(double dt);

  inline bool isStop()
  {
    return _stop;
  }

  inline void toggle()
  {
    _stop=!_stop;
  }
  
  inline void enable()
  {
      _stop = true;
  }
  
  inline void disable()
  {
      _stop = false;
  }
  
  inline double getDistance() const
  {
    return _distance;
  }

protected:
  virtual void initShape();
private:
  bool _stop;
  double _distance;
};

#endif
