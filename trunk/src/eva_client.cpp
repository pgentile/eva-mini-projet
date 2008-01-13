#include <iostream>
#include <sys/time.h>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "tcp-text-server.h"
#include "vector-3d.h"
#include "network/usefull.h"
#include "network-command.h"

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
#include "virtual-car-entity.h"

Camera* camera;
unsigned int current_camera = 0;
Light global;
bool zoom = false, rotate = false, state = false;
int OldY, OldX;
double pitch = 0, yaw = 0;
double dt = 1.0;

//The global Scene
Scene scene;
Entity* object = NULL;
SteeringSystem steeringSystem;
TrafficLight* trafficLight = NULL;


std::string server;
TCPTextClient client;
int clientId;
double timeOffset;
double lastCorrection = 0.0;
double lastUpdate = 0.0;

std::vector<SteeringEntity*> cars;


double getCurrentTime(void) {
    struct timeval t;
    gettimeofday(&t, NULL);
    double sec = (double) t.tv_sec;
    double usec = (double) t.tv_usec * 0.000001;
    return sec + usec;
}

void initConnection() {
    client.send("CONNECT_ME");
    bool hasClientId = false, hasTimeOffset = false;
    while (!hasClientId || !hasTimeOffset) {
        if (client.isReady()) {
            NetworkCommand cmd;
            if (cmd.parse(client.receive())) {
                std::string name = cmd.getName();
                // Definir l'ID du client
                if (name == "YOUR_ID_IS") {
                    clientId = cmd.getClientId();
                    hasClientId = true;
                    // Définir l'offset de temps
                } else if (name == "TIME_IS") {
                    double clientTime = getCurrentTime();
                    timeOffset = cmd.getTime() - clientTime;
                    hasTimeOffset = true;
                }
                cmd.display();
            }
        }
    }
}

void createOrUpdateEntity(std::vector<SteeringEntity*>& entities, int netId, Vector3D position, Vector3D speed, Vector3D acceleration) {
    for (std::vector<SteeringEntity*>::iterator i = entities.begin(); i != entities.end(); i++) {
        if ((*i)->getNetId() == netId) {
            (*i)->getTransform()->setPosition(position);
            (*i)->setVelocity(speed);
            (*i)->setAcceleration(acceleration);
            return;
        }
    }
    SteeringEntity* entity = new VirtualCarEntity(&steeringSystem);
    entity->getTransform()->setPosition(position);
    entity->setVelocity(speed);
    entity->setAcceleration(acceleration);
    scene.addEntity(entity);
    entities.push_back(entity);
}

void registerExternalEntities(std::vector<SteeringEntity*>& entities) {
    client.send("I_NEED_ALL_ENTITIES");
    double startTime = getCurrentTime();
    double currentTime = startTime;
    while (currentTime - startTime < 3.0) {
        if (client.isReady()) {
            NetworkCommand cmd;
            if (cmd.parse(client.receive()) && cmd.getName() == "ADD_ENTITY") {
                createOrUpdateEntity(entities, cmd.getEntityId(), cmd.getPosition(), cmd.getSpeed(), cmd.getAcceleration());
            }
        }
        currentTime = getCurrentTime();
    }
}

void registerEntity(std::vector<SteeringEntity*>& entities, SteeringEntity& entity) {
    client.send("GET_ENTITY_ID");
    bool idRecieved = false;
    while (!idRecieved) {
        if (client.isReady()) {
            NetworkCommand cmd;
            if (cmd.parse(client.receive()) && cmd.getName() == "ENTITY_ID_IS") {
                entity.setNetId(cmd.getEntityId());
                entities.push_back(&entity);
                
                NetworkCommand responseCmd("ADD_ENTITY");
                responseCmd.setClientId(clientId);
                responseCmd.setEntityId(cmd.getEntityId());
                responseCmd.setTime(getCurrentTime() + timeOffset);
                responseCmd.setPosition(entity.getTransform()->getPosition());
                responseCmd.setSpeed(entity.getVelocity());
                responseCmd.setAcceleration(entity.getAcceleration());
                client.send(responseCmd.toString());
                
                idRecieved = true;
            }
        }
    }
}

void handlePlayingMessages() {
    if (client.isReady()) {
        NetworkCommand cmd;
        if (cmd.parse(client.receive())) {
            if (cmd.getName() == "I_NEED_ALL_ENTITIES") {
                for (std::vector<SteeringEntity*>::iterator i = cars.begin(); i != cars.end(); i++) {
                    SteeringEntity* car = *i;
                    if (typeid(*car) == typeid(CarEntity)) {
                        NetworkCommand responseCmd("ADD_ENTITY");
                        responseCmd.setClientId(clientId);
                        responseCmd.setEntityId(car->getNetId());
                        responseCmd.setPosition(car->getTransform()->getPosition());
                        responseCmd.setSpeed(car->getVelocity());
                        responseCmd.setAcceleration(car->getAcceleration());
                        responseCmd.setTime(getCurrentTime() + timeOffset);
                        client.send(responseCmd.toString());
                    }
                }
                
            } else if (cmd.getName() == "ADD_ENTITY") {
                createOrUpdateEntity(cars, cmd.getEntityId(), cmd.getPosition(), cmd.getSpeed(), cmd.getAcceleration());
            } else if (cmd.getName() == "CORRECT") {
                for (std::vector<SteeringEntity*>::iterator i = cars.begin(); i != cars.end(); i++) {
                    VirtualCarEntity* car = (VirtualCarEntity*) *i;
                    if (car->getNetId() == cmd.getEntityId()) {
                        car->getTransform()->setPosition(cmd.getPosition());
                        car->setVelocity(cmd.getSpeed());
                        car->setAcceleration(cmd.getAcceleration());
                    }
                }
            } else if (cmd.getName() == "TAKE_FIRE") {
                trafficLight->enable();
            } else if (cmd.getName() == "RELEASE_FIRE") {
                trafficLight->disable();
            } else {
                std::cerr << "Untreatable command" << std::endl;
            }
        } else {
            std::cerr << "Invalid command" << std::endl;
        }
    }
}

void takeFire() {
    NetworkCommand cmd("TAKE_FIRE");
    cmd.setClientId(clientId);
    client.send(cmd.toString());
}

void releaseFire() {
    NetworkCommand cmd("RELEASE_FIRE");
    cmd.setClientId(clientId);
    client.send(cmd.toString());
}


void correctPositions() {
    for (std::vector<SteeringEntity*>::iterator i = cars.begin(); i != cars.end(); i++) {
        SteeringEntity* car = *i;
        NetworkCommand cmd("CORRECT");
        cmd.setTime(getCurrentTime() + timeOffset);
        cmd.setClientId(clientId);
        cmd.setEntityId(car->getNetId());
        cmd.setPosition(car->getTransform()->getPosition());
        cmd.setSpeed(car->getVelocity());
        cmd.setAcceleration(car->getAcceleration());
        client.send(cmd.toString());
    }
}

void renderBitmapString(float x, float y, void* font, char* string) {
    char* c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void renderSpacedBitmapString(float x, float y, int spacing, void* font, char* string) {
    char *c;
    int x1=(int)x;
    for (c=string; *c != '\0'; c++) {
        glRasterPos2f(x1, y);
        glutBitmapCharacter(font, *c);
        x1 = x1 + glutBitmapWidth(font, *c) + spacing;
    }
}


void renderVerticalBitmapString(float x, float y, int bitmapHeight, void* font, char* string) {
    
    char *c;
    int i;
    for (c=string, i=0; *c != '\0'; i++, c++) {
        glRasterPos2f(x, y+bitmapHeight*i);
        glutBitmapCharacter(font, *c);
    }
}

void MouseClick(int button, int state, int x, int y) {
    if ((button==GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN)) {
        zoom=true;OldY=y;OldX=x;
    }
    else {zoom=false;}
    if ((button==GLUT_RIGHT_BUTTON)&&(state==GLUT_DOWN)) {
        rotate=true;OldX=x;OldY=y;
    }
    else {rotate=false;}
}

void MouseMove(int x, int y) {
    if (zoom) {
        camera->up(-(OldY-y));OldY=y;
        camera->strafe((OldX-x));OldX=x;
    }
    if (rotate) {
        yaw= camera->getOrientation().getY()+(OldX-x)*0.5;
        pitch=camera->getOrientation().getX()-(OldY-y)*0.5;
        camera->setOrientation(pitch, yaw, 0);
        OldX=x;
        OldY=y;
    }
}

void MousePassiveMove(int x, int y) {
}


void Key(unsigned char c, int x, int y) {
    switch (c) {
        case 27:/* Sortie de l'application lorsque la touche ESC est pressee*/
            exit(0);
            break;
        case 't':
            if (trafficLight->isStop()) {
                releaseFire();
            } else {
                takeFire();
            }
            break;
        case 'n':
            current_camera++;
            if (current_camera>=scene.getNbCameras()) current_camera=0;
            break;
    }
}

void SpecialKey(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_RIGHT :
            camera->strafe(10);
            break ;
        case GLUT_KEY_LEFT :
            camera->strafe(-10);
            break ;
        case GLUT_KEY_UP :
            camera->move(10);
            break ;
        case GLUT_KEY_DOWN :
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



void Reshape(int w, int h) {
    // Redefinition de la fenetre d'affichage
    glViewport(0, 0, (GLint)w, (GLint)h);
    // On demande un rafraichissement de l'affichage
    glutPostRedisplay();
}

void renderHelp() {
    char* help[] = {"ESC: quitter",
    "Fleches directionnelles: deplacer la camera dans son plan"
            " horizontal",
    "PgUp/Down: augmenter/diminuer le pas de temps",
    "Souris+Clic gauche: deplacer la camera dans son plan vertical",
    "Souris+Clic droit: changer l'orientation de la camera"};
    unsigned int nb_lines = 5;
    renderVerticalBitmapString(10, 10, 8, (void *)GLUT_BITMAP_8_BY_13, "AIDE");
    renderVerticalBitmapString(23, 10, 4, (void *)GLUT_BITMAP_8_BY_13, "$$$$$$$$$$");
    for (unsigned int i = 0; i < nb_lines; i++) {
        renderBitmapString(30, 10 + i * 8, (void *)GLUT_BITMAP_8_BY_13, help[i]);
    }
}

Vector3D pos(0, 0, 10);
void Draw(void) {
    // Clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    scene.getCamera(current_camera)->setPerspective();
    scene.getCamera(current_camera)->setActive();
    
    //mettre les lumiere de position ici.
    
    scene.render();
    
    //Text rendering-------------------------
    //640 480
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 1.0f);
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
    
    // On demande a la machine OpenGL de presenter l'image a l'ecran
    glutSwapBuffers();
}

void Idle(void) {
    double currentTime = getCurrentTime();
    if (lastUpdate == 0.0) {
        lastUpdate = currentTime;
    }
    
    handlePlayingMessages();
    
    if (currentTime - lastCorrection > 0.1) {
        correctPositions();
        lastCorrection = currentTime;
    }
    
    // On fait vivre les entités
    if (currentTime > lastUpdate) {
        scene.update((currentTime - lastUpdate) * 10);
    }
    
    lastUpdate = currentTime;
    
    // On demande le rafraichissement de l'affichage
    glutPostRedisplay();
}


void init() {
    
    // Initialisation du client réseau
    
    if (!client.connect(server, 22222)) {
        std::cerr << "Error during client connection..." << std::endl;
        return;
    }
    initConnection();
    
    // Initialisation d'OpenGL
    
    glShadeModel(GL_SMOOTH);
    glClearColor(.3f, .3f, .3f, 1.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    
    // Initialisation de la caméra
    
    camera = new Camera();
    scene.addCamera(camera);
    
    // On active la lumière d'ambiance
    
    global.on();
    global.setDirection(0, 0, 1);
    global.setAmbient(0.0, 0.0, 0.0);
    global.setDiffuse(1.0, 1.0, 1.0);
    global.setSpecular(1.0, 1.0, 1.0);
    
    // Init random()
    
    struct timeval timestamp;
    gettimeofday(&timestamp, NULL);
    srand(timestamp.tv_usec);
    
    // Init entities
    // Duy entity to draw world axis
    
    object = new Entity();
    Shape* shape = new Shape();
    object->setShape(shape);
    object->getTransform()->setPosition(0, 0, 0);
    ShapePart* axis = new Axis();
    axis->getTransform()->setScale(1000, 1000, 1000);
    shape->addPart(axis);
    scene.addEntity(object);
    
    // Traffic Light
    
    trafficLight = new TrafficLight();
    scene.addEntity(trafficLight);
    
    // Car track
    
    CarTrack* track = new CarTrack(trafficLight);
    scene.addEntity(track);
    
    // Ajout du mur
    
    Wall* wall = new Wall(Vector3D(0.0, 0.0, 0.0), Vector3D(5.0, 7.0, 0.0));
    scene.addEntity(wall);
    
    // Ajout d'autres voitures
    
    for (unsigned int i = 0; i < 10; i++) {
        CarEntity* ent = new CarEntity(&steeringSystem, track, i);
        scene.addEntity(ent);
        ent->setTarget(i + 1);
        Vector3D pos = ent->getTrack()->getPoint(i);
        ent->getTransform()->setPosition(pos.getX(), pos.getY(), 0);
        registerEntity(cars, *ent);
    }
    
    // Enregistrement des entités externes
    
    registerExternalEntities(cars);
    
}

/*
 * Fonction principale.
 */
int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage : eva_client <server>" << std::endl;
        return 1;
    }
    server = argv[1];
    
    // Initialisation de l'application avec Glut
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Ants");
    
    init();
    
    // Definitions des callbacks
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    glutIdleFunc(Idle);
    glutKeyboardFunc(Key);
    glutSpecialFunc(SpecialKey);
    glutMouseFunc(MouseClick);
    glutMotionFunc(MouseMove);
    glutPassiveMotionFunc(MousePassiveMove);
    
    glutMainLoop();
    
    return 0;
}

