#include "stay-on-track-behavior.h"
#include "macros.h"
#include "road-block.h"
#include "car-entity.h"

StayOnTrackBehavior::StayOnTrackBehavior()
{
    setWeight(1.0);
}

StayOnTrackBehavior::~StayOnTrackBehavior()
{
}

Vector3D StayOnTrackBehavior::compute(SteeringEntity* se)
{
    CarEntity* e      = dynamic_cast<CarEntity *>(se);
    Vector3D ePos     = e->getTransform()->getPosition();
    Vector3D eTarget  = e->getCurrentTarget(); 
    Vector3D ePTarget = e->getPreviousTarget();
    Vector3D eForward = e->getForward(); // Entity Orientation
    double tWidth     = e->getTrack()->getTrackWidth();
    Vector3D sotForce(0.0,0.0,0.0);
    Vector3D nextPosition    = ePos + 0.1 * e->getVelocity();
  
    
    // Calculating Wall Points
    Vector3D rbNormalVector(0.,0.,-1.);
    Vector3D rbVector = (eTarget - ePTarget);
    rbVector.normalize();
    Vector3D widthVector          = rbVector.crossProduct( rbNormalVector ) * tWidth ;
    std::cout << "Width Vector = " << widthVector << std::endl;
    Vector3D rightWallStartPoint  = ePTarget  + widthVector  ;
    Vector3D rightWallEndPoint    = eTarget   + widthVector  ;
    Vector3D leftWallStartPoint   = ePTarget  - widthVector  ;
    Vector3D leftWallEndPoint     = eTarget   - widthVector  ;
                                                             
    // Intersection with right wall
    Vector3D rightWallVector = rightWallEndPoint - rightWallStartPoint;
    rightWallVector.normalize();
    
    double rwDist = (nextPosition - rightWallStartPoint ).produitScalaire(rightWallVector);
    Vector3D rwInter = rightWallStartPoint + rightWallVector * rwDist;
    Vector3D rwVectPen = nextPosition - rwInter;
    
    // Intersection with left wall
    Vector3D leftWallVector = leftWallEndPoint - leftWallStartPoint;
    leftWallVector.normalize();
    
    double lwDist = (nextPosition - leftWallStartPoint ).produitScalaire(leftWallVector);
    Vector3D lwInter = leftWallStartPoint + leftWallVector * lwDist;
    Vector3D lwVectPen = nextPosition - lwInter;
    
    widthVector.normalize();
    
    if( widthVector.produitScalaire( rwVectPen ) > 0 )
    {
        sotForce = -2 * rwVectPen ;
    }
    else if( widthVector.produitScalaire( lwVectPen ) > 0 )
    {
        sotForce = -2 * lwVectPen ;
    }
    
        
    
    #ifndef SOT_DEBUG
        //std::cout << "-- SOT Force  : " << sotForce.getX() << "*x + " << sotForce.getY() << "*y + " << sotForce.getZ() << " = 0" << std::endl;
        // std::cout << "-- Equation du mur droit  : " << rightWallA << "*x + " << rightWallB << "*y + " << rightWallC << " = 0" << std::endl;
        // std::cout << "-- Equation du mur gauche : " << leftWallA  << "*x + " << leftWallB  << "*y + " << leftWallC  << " = 0" << std::endl;
    #endif
    
    return sotForce;
}
