#ifndef TEST_BEHAVIOR_H
#define TEST_BEHAVIOR_H

class TestBehavior:public SteeringBehavior
{
public:
  TestBehavior();
  virtual ~TestBehavior();

  virtual Vector3D compute(SteeringEntity* entity);

protected:
private:
  bool _arrived;
  double up_component;
};

#endif

