#define _USE_MATH_DEFINES
#include <cmath>
#include "TP01.h"
#include <GlCamera.h>
#include "Shapes/Basis.h"
#include "Shapes/Cubes.h"
#include "Shapes/Pyramid.h"
#include "Shapes/Cylinder.h"
#include "Shapes/Star.h"
#include "Shapes/BasisPlan.h"
#include <iostream>

using namespace std;

AbstractVec3<float32> mouse;
AbstractVec3<float32> translateMouse;
GLfloat shiftR = 0.0f;
GLfloat shiftN = 0.0f;
GLfloat rotateAngle = 0.0f;
GLfloat rotateLeg = 0.0f;
GLboolean rotateOrder = true;
double eyeAngleR = 0;
double eyeAngleU = 0;

const GLfloat g_AngleSpeed = 10.0f;


Basis* basis;
BasisPlan* basisPlan;
TwoColorCube* cube;
GlCamera* camera;

TP01::TP01()
{
	setWindowTitle(trUtf8("IN55-TP01"));

    basis = new Basis( 30.0 );
    basisPlan = new BasisPlan();
    cube = new TwoColorCube();
    camera = new GlCamera(100.0f,30.0f,100.0f,
                         0.0f,0.0f,0.0f);
    mouse.x = QCursor::pos().x();
    mouse.y = QCursor::pos().y();
    camera->setFOV(180.0f);
    camera->setPlanes(0.1f, 800.0f);
}


TP01::~TP01()
{
    delete basis;
    delete cube;
    // basisPlan;
    //delete camera;
}


bool
TP01::initializeObjects()
{
	// Fond gris
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glEnable( GL_DEPTH_TEST );
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glShadeModel(GL_FLAT);

	// Chargement des shaders
    createShader( "Shaders/color" );

    cout << "Shader color: ";
    if (useShader( "color" ))
    {
        cout << "Loaded!" << endl;
    }
    else
    {
        cout << "NOT Loaded!" << endl;
    }

	return true;
}


void
TP01::render()
{
	// Initialisation de la caméra
    lookAt(camera->getMPosition().x,
           camera->getMPosition().y,
           camera->getMPosition().z,
           camera->getMPosition().x + camera->getMOrientation().x,
           camera->getMPosition().y + camera->getMOrientation().y,
           camera->getMPosition().z + camera->getMOrientation().z);
    setPerspective(45.0f,1.0f,1.0f,500.0f);
    //setCameraPerspective(camera );
    //setCameraOrtho(camera);
    // Rendu des objet
    pushMatrix();
    //camera->translateY(shiftY);
    //camera->translateZ(shiftZ);
    //camera->rotateX(50.0f);
        basis->draw();
        basisPlan->draw();

        rotate(rotateAngle,0.0f,1.0f,0.0f);
        translate( 10.0, 5.0, 0.0 );

        pushMatrix();
        rotate(-rotateLeg,1.0f,0.0f,0.0f);
        translate( -1.0, -2.5, 0 );
        scale(0.5f,2.5f,0.5f);
        cube->draw();
        popMatrix();

        pushMatrix();
        rotate(rotateLeg,1.0f,0.0f,0.0f);
        translate( 1.0, -2.5, 0 );
        scale(0.5f,2.5f,0.5f);
        cube->draw();
        popMatrix();

        translate( 0.0, 5.0, 0 );

        pushMatrix();
        translate( 0.0, -2.5, 0 );
        scale(1.5f,2.5f,1.0f);
        cube->draw();
        popMatrix();

        pushMatrix();
        rotate(rotateLeg,1.0f,0.0f,0.0f);
        translate( -2.0, -2.0, 0 );
        scale(0.5f,2.0f,0.5f);
        cube->draw();
        popMatrix();

        pushMatrix();
        rotate(-rotateLeg,1.0f,0.0f,0.0f);
        translate( 2.0, -2.0, 0 );
        scale(0.5f,2.0f,0.5f);
        cube->draw();
        popMatrix();

        translate( 0.0, 1.0, 0 );
        pushMatrix();
            rotate(rotateLeg,0.0f,1.0f,0.0f);
            scale(1.0f,1.0f,1.0f);
            cube->draw();
        popMatrix();
    popMatrix();
    rotateAngle += 0.5f;

    if(rotateLeg>15.0f){
        rotateOrder = false;
    }
    if(rotateLeg < -15.0f){
        rotateOrder = true;
    }
    if(rotateOrder){
        rotateLeg += 0.5f;
    }
    else{
        rotateLeg -= 0.5f;
    }
}


void
TP01::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Left:
        if(eyeAngleU < M_PI/2){
            camera->rotateU(M_PI/(32*32),0.0f,1.0f,0.0f);
            eyeAngleU += M_PI/(32*32);
        }
        break;

        case Qt::Key_Right:
        if(eyeAngleU > -M_PI/2){
            camera->rotateU(-M_PI/(32*32),0.0f,1.0f,0.0f);
            eyeAngleU -= M_PI/(32*32);
        }
            break;

        case Qt::Key_Up:
        if(eyeAngleR < M_PI/2){
            camera->rotateR(M_PI/(32*32),0.0f,1.0f,0.0f);
            eyeAngleR += M_PI/(32*32);
        }
            break;

        case Qt::Key_Down:
        if(eyeAngleR > -M_PI/2){
            camera->rotateR(-M_PI/(32*32),0.0f,1.0f,0.0f);
            eyeAngleR -= M_PI/(32*32);
        }
            break;

        case Qt::Key_Z:
            camera->translateO(0.5f,0.0f,1.0f,0.0f);
            break;

        case Qt::Key_S:
             camera->translateO(-0.5f,0.0f,1.0f,0.0f);
             break;

        case Qt::Key_Q:
            camera->translateR(-0.5f,0.0f,1.0f,0.0f);
            break;

        case Qt::Key_D:
            camera->translateR(0.5f,0.0f,1.0f,0.0f);
            break;
    }
}

void
TP01::mouseMoveEvent( QMouseEvent* event )
{
    translateMouse.x = mouse.x - event->x();
    translateMouse.y = mouse.y -  event->y();
    //camera->setEye(translateMouse);
    //camera->rotate(M_PI*translateMouse.length()/(100*100),0.0f,1.0f,0.0f);
}
