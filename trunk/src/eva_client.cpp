/********************************************************************
  Test framework OpenGL
*********************************************************************/

#include <iostream>

#include <sys/time.h>
/*
  Fichiers entete OpenGL
*/
#include "GL/glut.h"
#include "GL/glu.h"
#include "GL/gl.h"

#include "macros.h"

#include "baseshapes.h"
#include "scene.h"

#include "steering-system.h"
#include "traffic-light.h"
#include "car-track.h"
#include "car-entity.h"
#include "wall.h"

Camera* camera;
unsigned int current_camera=0;
Light global;
bool zoom=false,rotate=false,state=false;
int OldY,OldX;
double pitch=0,yaw=0;
double dt=.1;

//The global Scene
Scene scene;
Entity* object=NULL;
SteeringSystem steeringSystem;
TrafficLight* trafficLight=NULL;

void renderBitmapString(float x, float y, void *font,char *string)
{
  char *c;
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void renderSpacedBitmapString(float x, float y,int spacing,
                              void *font,char *string) {
  char *c;
  int x1=(int)x;
  for (c=string; *c != '\0'; c++) {
    glRasterPos2f(x1,y);
    glutBitmapCharacter(font, *c);
    x1 = x1 + glutBitmapWidth(font,*c) + spacing;
  }
}


void renderVerticalBitmapString(float x, float y, int bitmapHeight,
                                void *font,char *string)
{

  char *c;
  int i;
  for (c=string,i=0; *c != '\0'; i++,c++) {
    glRasterPos2f(x, y+bitmapHeight*i);
    glutBitmapCharacter(font, *c);
  }
}

void MouseClick(int button,int state,int x,int y)
{
  if ((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN))
    {
      zoom=true;OldY=y;OldX=x;
    }
  else {zoom=false;}
  if ((button==GLUT_RIGHT_BUTTON)&&(state==GLUT_DOWN))
    {
      rotate=true;OldX=x;OldY=y;
    }
  else {rotate=false;}
}

void MouseMove(int x,int y)
{
  if (zoom)
    {
      camera->up(-(OldY-y));OldY=y;
      camera->strafe((OldX-x));OldX=x;
    }
  if (rotate)
    {
      yaw= camera->getOrientation().getY()+(OldX-x)*0.5;
      pitch=camera->getOrientation().getX()-(OldY-y)*0.5;
      camera->setOrientation(pitch,yaw,0);
      OldX=x;
      OldY=y;
    }
}

void MousePassiveMove(int x,int y)
{
}


void Key(unsigned char c,int x,int y)
{
  switch (c)
    {
    case 27:/* Sortie de l'application lorsque la touche ESC est pressee*/
      exit(0);
      break;
    case 't':
      trafficLight->toggle();
      break;
    case 'n':
      current_camera++;
      if (current_camera>=scene.getNbCameras()) current_camera=0;
      break;
    }
}

void SpecialKey(int key, int x, int y)
{
  switch (key)
    {
    case  GLUT_KEY_RIGHT :
      camera->strafe(10);
      break ;
    case  GLUT_KEY_LEFT :
      camera->strafe(-10);
      break ;
    case  GLUT_KEY_UP :
      camera->move(10);
      break ;
    case  GLUT_KEY_DOWN :
      camera->move(-10);
      break ;
    case GLUT_KEY_PAGE_UP:
      dt+=0.05;
      break;
    case GLUT_KEY_PAGE_DOWN:
      dt-=0.05;
      break;

    default :
      break ;
    }
  glutPostRedisplay() ;
}



void Reshape(int w,int h)
{
  /* Redefinition de la fenetre d'affichage */
  glViewport(0, 0, (GLint)w, (GLint)h);
  /* On demande un rafraichissement de l'affichage */
  glutPostRedisplay();
}

void renderHelp()
{
  char* help[]={"ESC: quitter",
                "Fleches directionnelles: deplacer la camera dans son plan"
                " horizontal",
                "PgUp/Down: augmenter/diminuer le pas de temps",
                "Souris+Clic gauche: deplacer la camera dans son plan vertical",
                "Souris+Clic droit: changer l'orientation de la camera"};
  unsigned int nb_lines=5;
  renderVerticalBitmapString(10,10,8,(void *)GLUT_BITMAP_8_BY_13,
                             "AIDE");
  renderVerticalBitmapString(23,10,4,(void *)GLUT_BITMAP_8_BY_13,
                             "$$$$$$$$$$");
  for (unsigned int i=0;i<nb_lines;i++)
    {
      renderBitmapString(30,10+i*8,(void *)GLUT_BITMAP_8_BY_13,help[i]);
    }
}

Vector3D pos(0,0,10);
void Draw(void)
{
  /*
    Clear screen and depth buffer
  */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  scene.getCamera(current_camera)->setPerspective();

  scene.getCamera(current_camera)->setActive();

  //mettre les lumiere de position ici.

  scene.render();

  //Text rendering-------------------------
  //640 480
  glPushMatrix();
  glColor3f(0.0f,1.0f,1.0f);
  // switch to projection mode
  glMatrixMode(GL_PROJECTION);
  // save previous matrix which contains the
  //settings for the perspective projection
  glPushMatrix();
  // reset matrix
  glLoadIdentity();
  // set a 2D orthographic projection
  gluOrtho2D(0, 640, 0, 480);
  // invert the y axis, down is positive
  glScalef(1, -1, 1);
  // mover the origin from the bottom left corner
  // to the upper left corner
  glTranslatef(0, -480, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  renderHelp();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

  /*  On demande a la machine OpenGL de pr�senter l'image � l�cran*/
  glutSwapBuffers();
}

void Idle(void)
{

  /* On fait vivre les entit�s */
  scene.update(dt);

  /* On demande le rafraichissement de l'affichage*/
  glutPostRedisplay();
}


void init()
{

  /* Initialisation d'OpenGL*/
  glShadeModel(GL_SMOOTH);
  glClearColor(.3f,.3f,.3f,1.0f);/* On remplit le buffer de rendu
                                    avec la couleur bleue */
  glClearDepth(1.0);             /* On remplit le buffer de profondeur
                                    avec la valeur 1.0 */
  glEnable(GL_DEPTH_TEST);       /* On active le test de profondeur */
  glEnable(GL_CULL_FACE);        /* N'afficher que les facettes d�crites
                                    dans un certain ordre */
  glFrontFace(GL_CCW);           /* Cet ordre est le sens trigonometrique
                                    (inverse des aiguilles d'une montre) */
  glCullFace(GL_BACK);           /* Ne pas afficher la face arriere de
                                    ces facettes */
  glEnable(GL_LIGHTING);

  glEnable(GL_NORMALIZE);
  //init the camera
  camera=new Camera();
  //ajout camera
  scene.addCamera(camera);
  //on active la lumi�re d'ambiance
  global.on();
  global.setDirection(0,0,1);
  global.setAmbient(0.0,0.0,0.0);
  global.setDiffuse(1.0,1.0,1.0);
  global.setSpecular(1.0,1.0,1.0);

  //init random()
  struct timeval timestamp;
  gettimeofday(&timestamp,NULL);
  srand(timestamp.tv_usec);

  //Init entities
  //Duy entity to draw world axis
  object=new Entity();
  Shape* shape=new Shape();
  object->setShape(shape);
  object->getTransform()->setPosition(0,0,0);
  ShapePart* axis=new Axis();
  axis->getTransform()->setScale(1000,1000,1000);
  shape->addPart(axis);
  scene.addEntity(object);

  //Traffic Light
  trafficLight=new TrafficLight();
  scene.addEntity(trafficLight);

  //Car track
  CarTrack* track=new CarTrack(trafficLight);
  scene.addEntity(track);
  
  CarEntity* ent=new CarEntity(&steeringSystem,track);
  ent->getTransform()->setPosition(RANDOM_NUMBER(0,-300),
                                       RANDOM_NUMBER(0,-300),
                                       0);
                                       
  Wall* wall = new Wall(Vector3D(0.0, 0.0, 0.0), Vector3D(5.0, 7.0, 0.0));
  scene.addEntity(wall);
                                       
  Camera* cam=new Camera();
  scene.addCamera(cam);
  ent->setCamera(cam);
  scene.addEntity(ent);
  for (unsigned int i=0;i<10;i++)
  {
      CarEntity* ent=new CarEntity(&steeringSystem,track);
      ent->getTransform()->setPosition(RANDOM_NUMBER(0,-300),
                                       RANDOM_NUMBER(0,-300),
                                       0);
      scene.addEntity(ent);
  }

//   //Add our steering entities
//   for (unsigned int i=0;i<1;i++)
//     {
//       SteeringEntity* ent= new SteeringEntity(&steeringSystem);
//       ent->getTransform()->setPosition(500,500,0);
//       ent->setMaxVelocity(10.0);
//       ent->setMaxAcceleration(10.0);
//       ent->setMass(1.0);
//       WanderBehavior* bhv1=new WanderBehavior();
//       ent->addBehavior(bhv1);
//       scene.addEntity(ent);
//     }

}

/*
  Fonction principale.
*/
int main( int argc,char** argv )
{
  /* Initialisation de l'application avec Glut */
  glutInit(&argc, argv);                                       /* Init. Glut */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);   /* Initialisation
                                                                  des parametres
                                                                  de la fenetre
                                                                  de rendu */
  glutInitWindowSize(600, 600);                                /* Definition de
                                                                  la taille de
                                                                  la fenetre de
                                                                  rendu */
  glutCreateWindow("Ants");                               /* Creation de la
                                                             fenetre de rendu */

  init();


  /* Definitions des callbacks */
  glutReshapeFunc(Reshape);                /* Redimensionnement de la fenetre
                                              de rendu */
  glutDisplayFunc(Draw);                   /* Affichage */
  glutIdleFunc(Idle);                      /* Animation */
  glutKeyboardFunc(Key);                   /* Interactions clavier */
  glutSpecialFunc(SpecialKey);
  glutMouseFunc(MouseClick);
  glutMotionFunc(MouseMove);
  glutPassiveMotionFunc(MousePassiveMove);
  /* Boucle Glut (boucle infinie) */
  glutMainLoop();


  /*On n'atteint jamais ce point !!!!!!!!*/
  return 0;
}

