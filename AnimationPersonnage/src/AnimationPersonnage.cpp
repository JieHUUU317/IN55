#define _USE_MATH_DEFINES
#include <cmath>
#include "AnimationPersonnage.h"
#include "Framework/GlCamera.h"
#include "Shapes/Basis.h"
#include "Shapes/Cubes.h"
#include "Shapes/BasisPlan.h"
#include "Model/MD5Model.h"
#include <iostream>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

GLfloat shiftR = 0.0f;
GLfloat shiftN = 0.0f;
GLfloat rotateAngle = 0.0f;
GLfloat rotateLeg = 0.0f;
boolean rotateOrder = true;
GLfloat eyeAngleR = 0.0f;
GLfloat eyeAngleU = 0.0f;
QPoint dragStartPosition;

Basis* basis;
BasisPlan* basisPlan;
TwoColorCube* cube;
GlCamera* camera;
MD5Model* g_Model;
GLfloat g_LighPos[] = { -39.749374, -6.182379, 46.334176, 1.0f };       // This is the position of the 'lamp' joint in the test mesh in object-local space
GLfloat g_LightAmbient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat g_LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat g_LighAttenuation0 = 1.0f;
GLfloat g_LighAttenuation1 = 0.0f;
GLfloat g_LighAttenuation2 = 0.0f;

AnimationPersonnage::AnimationPersonnage()
{
    setWindowTitle(trUtf8("AnimationPersonnage"));

    basis = new Basis( 30.0 );
    basisPlan = new BasisPlan();
    cube = new TwoColorCube();
    camera = new GlCamera(100.0f,30.0f,100.0f,
                         0.0f,0.0f,0.0f);
    g_Model = new MD5Model();
    camera->setFOV(180.0f);
    camera->setPlanes(0.1f, 800.0f);
}


AnimationPersonnage::~AnimationPersonnage()
{
    delete basis;
    delete cube;
    delete basisPlan;
    delete camera;
}


bool
AnimationPersonnage::initializeObjects()
{
	// Fond gris
    glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
    glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
    glShadeModel( GL_SMOOTH );
    glEnable( GL_TEXTURE_2D );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, g_LightAmbient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, g_LightDiffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, g_LightSpecular );
    glLightf( GL_LIGHT0, GL_CONSTANT_ATTENUATION, g_LighAttenuation0 );
    glLightf( GL_LIGHT0, GL_LINEAR_ATTENUATION, g_LighAttenuation1 );
    glLightf( GL_LIGHT0, GL_QUADRATIC_ATTENUATION, g_LighAttenuation2 );
    glColorMaterial( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );

    // Chargement des shaders
    createShader( "Shaders/color" );

    std::cout << "Shader color: ";
    if (useShader( "color" ))
    {
        std::cout << "Loaded!" << std::endl;
    }
    else
    {
        std::cout << "NOT Loaded!" << std::endl;
    }
    g_Model->LoadModel( "data/Person/boblampclean.md5mesh" );
    g_Model->LoadAnim( "data/Person/boblampclean.md5anim" );
	return true;
}
void AnimationPersonnage::updateAnimation(float fDeltaTime){
    g_Model->Update( fDeltaTime );
}
void
AnimationPersonnage::render()
{
    glm::vec3 eye = glm::vec3(camera->getMPosition().x,
                    camera->getMPosition().y,
                    camera->getMPosition().z);
    glm::vec3 center = glm::vec3(camera->getMPosition().x + camera->getMOrientation().x,
                       camera->getMPosition().y + camera->getMOrientation().y,
                       camera->getMPosition().z + camera->getMOrientation().z);

    // Initialisation de la caméra
    setLookAt(eye,center);
    setPerspective(45.0f,1.0f,1.0f,500.0f);
    // Rendu des objet
    pushMatrix();
        //basis->draw();
        basisPlan->draw();
        glLightfv( GL_LIGHT0, GL_POSITION, g_LighPos );
        pushMatrix();
        g_Model->Render();
        popMatrix();
/**
        rotateFramework(rotateAngle,0.0f,1.0f,0.0f);
        translateFramework( 10.0, 5.0, 0.0 );

        pushMatrix();
        rotateFramework(-rotateLeg,1.0f,0.0f,0.0f);
        translateFramework( -1.0, -2.5, 0 );
        scaleFramework(0.5f,2.5f,0.5f);
        cube->draw();
        popMatrix();

        pushMatrix();
        rotateFramework(rotateLeg,1.0f,0.0f,0.0f);
        translateFramework( 1.0, -2.5, 0 );
        scaleFramework(0.5f,2.5f,0.5f);
        cube->draw();
        popMatrix();

        translateFramework( 0.0, 5.0, 0 );

        pushMatrix();
        translateFramework( 0.0, -2.5, 0 );
        scaleFramework(1.5f,2.5f,1.0f);
        cube->draw();
        popMatrix();

        pushMatrix();
        rotateFramework(rotateLeg,1.0f,0.0f,0.0f);
        translateFramework( -2.0, -2.0, 0 );
        scaleFramework(0.5f,2.0f,0.5f);
        cube->draw();
        popMatrix();

        pushMatrix();
        rotateFramework(-rotateLeg,1.0f,0.0f,0.0f);
        translateFramework( 2.0, -2.0, 0 );
        scaleFramework(0.5f,2.0f,0.5f);
        cube->draw();
        popMatrix();

        translateFramework( 0.0, 1.0, 0 );
        pushMatrix();
            rotateFramework(rotateLeg,0.0f,1.0f,0.0f);
            scaleFramework(1.0f,1.0f,1.0f);
            cube->draw();
        popMatrix();
       */
    popMatrix();
    rotateAngle += 0.5f/10;

    if(rotateLeg>15.0f/40){
        rotateOrder = false;
    }
    if(rotateLeg < -15.0f/40){
        rotateOrder = true;
    }
    if(rotateOrder){
        rotateLeg += 0.5f/10;
    }
    else{
        rotateLeg -= 0.5f/10;
    }

}


void
AnimationPersonnage::keyPressEvent( QKeyEvent* event )
{
    switch( event->key())
    {
        case Qt::Key_Escape:
            close();
            break;

        case Qt::Key_Left:
        if(eyeAngleU < 90.0f){
            camera->rotateU(3.0f/100,0.0f,1.0f,0.0f);
            eyeAngleU += 3.0f/100;
        }
        break;

        case Qt::Key_Right:
        if(eyeAngleU > -90.0f){
            camera->rotateU(-3.0f/100,0.0f,1.0f,0.0f);
            eyeAngleU -= 3.0f/100;
        }
            break;

        case Qt::Key_Up:
        if(eyeAngleR < 90.0f){
            camera->rotateR(3.0f/100,0.0f,1.0f,0.0f);
            eyeAngleR += 3.0f/100;
        }
            break;

        case Qt::Key_Down:
        if(eyeAngleR > -90.0f){
            camera->rotateR(-3.0f/100,0.0f,1.0f,0.0f);
            eyeAngleR -= 3.0f/100;
        }
            break;

        case Qt::Key_Z:
            camera->translateO(0.5f/30,0.0f,1.0f,0.0f);
            break;

        case Qt::Key_S:
             camera->translateO(-0.5f/30,0.0f,1.0f,0.0f);
             break;

        case Qt::Key_Q:
            camera->translateR(0.5f/30,0.0f,1.0f,0.0f);
            break;

        case Qt::Key_D:
            camera->translateR(-0.5f/30,0.0f,1.0f,0.0f);
            break;
    }
}

void
AnimationPersonnage::mouseMoveEvent( QMouseEvent* event )
{
    if (!(event->buttons() & Qt::LeftButton))
            return;
    QPoint p = event->pos()-dragStartPosition;
    glm::vec2 delta = glm::vec2(-p.x(),-p.y());
    glm::quat rotX = glm::angleAxis<float>( glm::radians(delta.y) * 0.005f, glm::vec3(1, 0, 0) );
    glm::quat rotY = glm::angleAxis<float>( glm::radians(delta.x) * 0.005f, glm::vec3(0, 1, 0) );
    camera->rotate(rotX,rotY);
}

void AnimationPersonnage::mousePressEvent(QMouseEvent *event)
{
     if (event->button() == Qt::LeftButton)
         dragStartPosition = event->pos();
}
