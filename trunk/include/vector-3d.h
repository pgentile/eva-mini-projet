#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <iostream>
#include <cmath>

class Vector3D
{
public:
  Vector3D();
  Vector3D(double x,double y,double z);
  virtual ~Vector3D();

  inline void setX(double x) {_x=x;}
  inline void setY(double y) {_y=y;}
  inline void setZ(double z) {_z=z;}


  inline double getX() const {return _x;}
  inline double getY() const {return _y;}
  inline double getZ() const {return _z;}

  inline void rotate(double x,double y,double z)
  {
    //FIXME: problem with the order of transformations
    double tmpX,tmpY,tmpZ;
    //rotation around X axis
    tmpX=getX();
    tmpY=getY()*cos(x)-getZ()*sin(x);
    tmpZ=getY()*sin(x)+getZ()*cos(x);
    setX(tmpX);setY(tmpY);setZ(tmpZ);
    //rotation around Y axis
    tmpX=getZ()*sin(y)+getX()*cos(y);
    tmpY=getY();
    tmpZ=getZ()*cos(y)-getX()*sin(y);
    setX(tmpX);setY(tmpY);setZ(tmpZ);
    //rotation around Z axis
    tmpX=getX()*cos(z)-getY()*sin(z);
    tmpY=getX()*sin(z)+getY()*cos(z);
    tmpZ=getZ();
    setX(tmpX);setY(tmpY);setZ(tmpZ);
  }
  inline double produitScalaire(const Vector3D& v) const
  {
    return (getX()*v.getX() + getY()*v.getY() + getZ()*v.getZ());
  }
  inline Vector3D produitVectoriel(const Vector3D& v) const
  {
    Vector3D normal;

    // Calculate the cross product with the non communitive equation
    normal.setX((getY() * v.getZ()) - (getZ() * v.getY()));
    normal.setY((getZ() * v.getX()) - (getX() * v.getZ()));
    normal.setZ((getX() * v.getY()) - (getY() * v.getX()));

    // Return the cross product
    return normal;
  }
  
  inline Vector3D crossProduct(const Vector3D& v) const
  {
      return produitVectoriel(v);
  }
  
  inline double getModule() const
  {
    return (double)sqrt(getX()*getX()+getY()*getY()+getZ()*getZ());
  }
  inline double getSqrModule() const
  {
    return (double)(getX()*getX()+getY()*getY()+getZ()*getZ());
  }

  inline void normalize()
  {
    double mag=getModule();
    if (mag!=0)
      {
        setX(getX()/mag);
        setY(getY()/mag);
        setZ(getZ()/mag);
      }
  }
inline double operator*(const Vector3D& v) const{
    return getX() * v.getX() + getY() * v.getY() + getZ() * v.getZ();
}



inline double getAngle ( const Vector3D& v ) const
{
    //return ( acos ( this->produitScalaire ( v ) ) );
    double vDot = (*this)*(v) / ( this->getModule()*v.getModule());
    if( vDot < -1.0) vDot = -1.0;
    if( vDot >  1.0) vDot =  1.0;
    double dir=-1.0;
    if(this->produitVectoriel(v).getZ()>=0.0){
        dir=1.0;
    }
    return acos(vDot)*dir;
}


//   inline double getAngle(const Vector3D& v) const
//   {
//     return (acos(this->produitScalaire(v)));
//   }
  inline bool approximate(const Vector3D& v,double error)
  {
    //cout<<*this<<endl;
    //cout<<v<<endl;
    return (((v.getX()>=getX()-error)&&(v.getX()<=getX()+error))&&
            ((v.getY()>=getY()-error)&&(v.getY()<=getY()+error))&&
            ((v.getZ()>=getZ()-error)&&(v.getZ()<=getZ()+error)));
  }
  inline void truncate(double normMax)
  {
    double norm=getModule();
    if (norm>normMax)
      {
        setX(getX()*normMax/norm);
        setY(getY()*normMax/norm);
        setZ(getZ()*normMax/norm);
      }
  }

  friend Vector3D operator*(const double& x,const Vector3D& v);
  friend Vector3D operator*(const Vector3D& v,const double& x);
  friend Vector3D operator/(const Vector3D& v,const double& x);
  friend Vector3D operator+(const Vector3D& v1,const Vector3D& v2);
  friend Vector3D operator-(const Vector3D& v1,const Vector3D& v2);
  friend std::ostream& operator<<(std::ostream& s,const Vector3D& v);
  friend bool operator==(const Vector3D& v1,const Vector3D& v2);
  friend bool operator!=(const Vector3D& v1,const Vector3D& v2);
  virtual Vector3D& operator=(const Vector3D& v);

  virtual void display(std::ostream& s) const;


protected:
private:
  double _x,_y,_z;
};

#endif
