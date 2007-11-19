#include "baseshapes.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include "vector-3d.h"

Teapot::Teapot()
{}

Teapot::~Teapot()
{}

void Teapot::render()
{
  glCullFace(GL_FRONT);
  glutSolidTeapot(1.0);
  glCullFace(GL_BACK);
}

//----------------------

Sphere::Sphere(double res):_res(res)
{}

Sphere::~Sphere()
{}

void Sphere::render()
{
  GLUquadricObj *qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj, GLU_SMOOTH);    
  gluQuadricTexture(qobj,true);
  gluSphere(qobj,1.0,(int)_res,(int)_res);
  gluDeleteQuadric(qobj); 
}

//-------------------------

Cylinder::Cylinder(double bottom,double top,double length,double res):
  _bottom(bottom),_top(top),_length(length),_res(res)
{}

Cylinder::~Cylinder()
{}

void Cylinder::render()
{

  GLUquadricObj *qobj = gluNewQuadric();
  gluQuadricDrawStyle(qobj,GLU_FILL);
  gluQuadricNormals(qobj, GLU_SMOOTH);    
  gluQuadricTexture(qobj,true);
  gluCylinder(qobj,_bottom,_top,_length,(int)_res,(int)_res);
  gluDeleteQuadric(qobj); 
}

//-------------------------

Axis::Axis()
{
  
}

Axis::~Axis()
{}

void Axis::render()
{
  /* 
     Affichage des axes de l'environnement
  */
  glDisable(GL_LIGHTING);
  glBegin(GL_LINES);
  /* X */
  glColor3f(1.0,0,0);
  glVertex3f(0,0,0);
  glVertex3f(1,0,0);
  /* Y */
  glColor3f(0,1,0);
  glVertex3f(0,0,0);
  glVertex3f(0,1,0);
  /* Z */
  glColor3f(0,0,1);
  glVertex3f(0,0,0);
  glVertex3f(0,0,1);
  glEnd();

  glEnable(GL_LIGHTING);
  
}

//-------------------------

Quad::Quad():_width(1),_height(1)
{}

Quad::Quad(double width,double height):_width(width),_height(height)
{
  
}

Quad::~Quad()
{}

void Quad::render()
{
  //render a horizontal quad centered in 0 in local coordinates
  
  glBegin(GL_QUADS);
  glNormal3f(0.0,0.0,1.0);
  glTexCoord2f(1,1);
  glVertex3f(_width/2,_height/2,0);
  glTexCoord2f(0,1);
  glVertex3f(-_width/2,_height/2,0);
  glTexCoord2f(0,0);
  glVertex3f(-_width/2,-_height/2,0);
  glTexCoord2f(1,0);
  glVertex3f(_width/2,-_height/2,0);
  glEnd();

}

//-----------------------------------------------

Polyline::Polyline(bool loop):
  _loop(loop)
{}

Polyline::~Polyline()
{}

void Polyline::render()
{
  glDisable(GL_LIGHTING);
  if (_loop)
    {
      glBegin(GL_LINE_LOOP);
    }
  else
    {
      glBegin(GL_LINE_STRIP);
    }
  glColor3f(1,1,1);
  for (unsigned int i=0;i<_points->size();i++)
    {
      glVertex3f((*_points)[i].getX(),
                 (*_points)[i].getY(),
                 (*_points)[i].getZ());
    }
  glEnd();
  glEnable(GL_LIGHTING);
}

//-----------------------------------------------

Mesh::Mesh()
{}

Mesh::~Mesh()
{}

void Mesh::render()
{
  glDisable(GL_CULL_FACE);
  glBegin(GL_TRIANGLES);
  for (unsigned int i=0;i<_indices.size();i+=3)
    {
      Vector3D vertex0=_vertices[_indices[i]];
      Vector3D vertex1=_vertices[_indices[i+1]];
      Vector3D vertex2=_vertices[_indices[i+2]];
      Vector3D normal0=_normals[_indices[i]];
      Vector3D normal1=_normals[_indices[i+1]];
      Vector3D normal2=_normals[_indices[i+2]];
      
      //    glColor3f(1,0,0);
      glNormal3f(normal0.getX(),normal0.getY(),normal0.getZ());
      glTexCoord2f(_texCoords[_indices[i]].first,_texCoords[_indices[i]].second);
      glVertex3f(vertex0.getX(),vertex0.getY(),vertex0.getZ());
      
      //     glColor3f(0,1,0);
      glNormal3f(normal1.getX(),normal1.getY(),normal1.getZ());
      glTexCoord2f(_texCoords[_indices[i+1]].first,_texCoords[_indices[i+1]].second);
      glVertex3f(vertex1.getX(),vertex1.getY(),vertex1.getZ());
      
      //     glColor3f(0,0,1);
      glNormal3f(normal2.getX(),normal2.getY(),normal2.getZ());
      glTexCoord2f(_texCoords[_indices[i+2]].first,_texCoords[_indices[i+2]].second);
      glVertex3f(vertex2.getX(),vertex2.getY(),vertex2.getZ());

    }
   glEnd();
  glEnable(GL_CULL_FACE);
}

//-----------------------------------------------

Grid::Grid(double width,double  height,unsigned int width_res,unsigned int height_res,double tex_scale)
{
  //Build vertices, normals and texcoords
  for (unsigned int i=0;i<=width_res;i++)
    {
      for (unsigned int j=0;j<=height_res;j++)
	{
	  Vector3D vertex((width/width_res)*i,(height/height_res)*j,0.0);
	  Vector3D normal(0,0,1);
	  _vertices.push_back(vertex);
	  _normals.push_back(normal);
	  _texCoords.push_back(std::make_pair((double)i*tex_scale,(double)j*tex_scale));
	}
    }
  //Build indices
//   unsigned int current_index=0;
//   for (unsigned int i=0;i<width_res*height_res*2;i++)
//     {
//       _indices.push_back(current_index);
//       _indices.push_back(current_index+height_res+1);
//       _indices.push_back(current_index+1);

//       _indices.push_back(current_index+height_res+1);
//       _indices.push_back(current_index+height_res+2);
//       _indices.push_back(current_index+1);

//       current_index+=1;
//     }

  for (unsigned int i=0;i<width_res;i++)
    {
      for (unsigned int j=0;j<height_res;j++)
	{
	  _indices.push_back(i+j*(width_res+1));
	  _indices.push_back(i+(width_res+1)*(j+1));
	  _indices.push_back((i+1)+(width_res+1)*(j+1));

	  _indices.push_back((i+1)+(width_res+1)*(j+1));
	  _indices.push_back((i+1)+(width_res+1)*(j));
	  _indices.push_back((i)+(width_res+1)*(j));

	}
    }

//   std::cout<<"Nb vertices: "<<_vertices.size()<<std::endl;
//   std::cout<<"Nb tex coords: "<<_texCoords.size()<<std::endl;
//   std::cout<<"Nb indices: "<<_indices.size()<<std::endl;
//   for (unsigned int i=0;i<_vertices.size();i++)
//     {
//       std::cout<<"vertex: "<<_vertices[i]<<std::endl;
//     }
//   for (unsigned int i=0;i<_texCoords.size();i++)
//     {
//       std::cout<<"texcoord: "<<_texCoords[i].first<<" "<<_texCoords[i].second<<std::endl;
//     }
//   for (unsigned int i=0;i<_indices.size();i++)
//     {
//       std::cout<<"indice: "<<_indices[i]<<std::endl;
//     }
}

Grid::~Grid()
{}

//-------------------------------------------------------------

AntShape::AntShape()
{
  //Corps
  ShapePart* part1=new Sphere();
  part1->getMaterial()->setAmbient(0.2,0.2,0.3);
  part1->getMaterial()->setShininess(0);
  part1->getTransform()->setScale(2.0,2.0,2.0);
  part1->getTransform()->setPosition(-2.0,0.0,2.0);
  addPart(part1);

  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.2,0.2,0.3);
  part1->getMaterial()->setShininess(0);
  part1->getTransform()->setScale(2.0,2.0,2.0);
  part1->getTransform()->setPosition(0.0,0.0,2.0);
  addPart(part1);
  //Tete
  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.2,0.2,0.3);
  part1->getMaterial()->setShininess(0);
  part1->getTransform()->setPosition(2.0,0.0,2.0);
  addPart(part1);
  //Pate G
  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(75,0,0);
  part1->getTransform()->setPosition(0.0,4.0,2.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);

  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setPosition(0.0,4.0,2.1);
  part1->getTransform()->setScale(0.3,0.3,0.3);
  addPart(part1);

  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(45,0,0);
  part1->getTransform()->setPosition(0.0,6.0,0.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);
  //Pate G
  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(75,0,0);
  part1->getTransform()->setPosition(-1.0,4.0,2.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);

  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setPosition(-1.0,4.0,2.1);
  part1->getTransform()->setScale(0.3,0.3,0.3);
  addPart(part1);

  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(45,0,0);
  part1->getTransform()->setPosition(-1.0,6.0,0.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);
  //Pate G
  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(75,0,0);
  part1->getTransform()->setPosition(1.0,4.0,2.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);

  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setPosition(1.0,4.0,2.1);
  part1->getTransform()->setScale(0.3,0.3,0.3);
  addPart(part1);

  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(45,0,0);
  part1->getTransform()->setPosition(1.0,6.0,0.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);

  //Pate D
  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(-75,0,0);
  part1->getTransform()->setPosition(0.0,-4.0,2.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);

  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setPosition(0.0,-4.0,2.1);
  part1->getTransform()->setScale(0.3,0.3,0.3);
  addPart(part1);

  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(-45,0,0);
  part1->getTransform()->setPosition(0.0,-6.0,0.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);
  //Pate D
  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(-75,0,0);
  part1->getTransform()->setPosition(1.0,-4.0,2.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);

  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setPosition(1.0,-4.0,2.1);
  part1->getTransform()->setScale(0.3,0.3,0.3);
  addPart(part1);

  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(-45,0,0);
  part1->getTransform()->setPosition(1.0,-6.0,0.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);
  //Pate D
  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(-75,0,0);
  part1->getTransform()->setPosition(-1.0,-4.0,2.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);

  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setPosition(-1.0,-4.0,2.1);
  part1->getTransform()->setScale(0.3,0.3,0.3);
  addPart(part1);

  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(-45,0,0);
  part1->getTransform()->setPosition(-1.0,-6.0,0.0);
  part1->getTransform()->setScale(0.2,0.2,3);
  addPart(part1);
  //Antennes
  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(0,60,30);
  part1->getTransform()->setPosition(2.5,0.3,2.0);
  part1->getTransform()->setScale(0.1,0.1,3);
  addPart(part1);
  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setPosition(5.0,0.3,3.5);
  part1->getTransform()->setScale(0.3,0.3,0.3);
  addPart(part1);

  part1=new Cylinder();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setOrientation(0,60,-30);
  part1->getTransform()->setPosition(2.5,-0.3,2.0);
  part1->getTransform()->setScale(0.1,0.1,3);
  addPart(part1);
  part1=new Sphere();
  part1->getMaterial()->setAmbient(0.0,0.0,0.0);
  part1->getTransform()->setPosition(5.0,-0.3,3.5);
  part1->getTransform()->setScale(0.3,0.3,0.3);
  addPart(part1);
}

AntShape::~AntShape()
{
}
