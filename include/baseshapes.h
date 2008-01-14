#ifndef BASESHAPES_H
#define BASESHAPES_H

#include "vector-3d.h"
#include "shape.h"
#include "shape-part.h"


//Some testing & usefull shapes
class Teapot:public ShapePart
{
public:
  Teapot();
  virtual ~Teapot();

  virtual void render();

protected:
private:
};

class Avion:public ShapePart
{
  public:
    Avion();
    virtual ~Avion();

    virtual void render();

  protected:
  private:
};

class Car:public ShapePart
{
  public:
    Car();
    virtual ~Car();

    virtual void render();

  protected:
  private:
};

class Sphere:public ShapePart
{
public:
  Sphere(double res=5.0);
  virtual ~Sphere();

  virtual void render();

protected:
private:
  double _res;
};

class Cylinder:public ShapePart
{
public:
  Cylinder(double bottom=1.0,double top=1.0,double length=1.0,double res=5.0);
  virtual ~Cylinder();

  virtual void render();

protected:
private:
  double _bottom,_top,_length,_res;
};

class Axis:public ShapePart
{
public:
  Axis();
  virtual ~Axis();

  virtual void render();

protected:
private:
};

class Quad:public ShapePart
{
public:
  Quad();
  Quad(double width,double height);
  virtual ~Quad();

  virtual void render();

protected:
private:
  double _width;
  double _height;
};

class Polyline:public ShapePart
{
public:
  Polyline(bool loop=true);
  virtual ~Polyline();

  inline void setPoints(std::vector<Vector3D>* pts)
  {
    _points=pts;
  }

  virtual void render();

protected:
private:
  bool _loop;
  std::vector<Vector3D>* _points;
};

//"Generic" Mesh shape
class Mesh:public ShapePart
{
public:
  Mesh();
  virtual ~Mesh();

  virtual void render();

protected:
  std::vector<Vector3D> _vertices;
  std::vector<Vector3D> _normals;
  std::vector< std::pair< double , double> > _texCoords;
  std::vector<unsigned int> _indices;
private:
};

class Grid:public Mesh
{
public:
  Grid(double width,double height,unsigned int width_res,
       unsigned int height_res,double tex_scale=0.5);
  virtual ~Grid();

protected:
private:
};

//Complex shape with multiple shape parts
class AntShape:public Shape
{
public:
  AntShape();
  virtual ~AntShape();
protected:
private:
};

#endif
