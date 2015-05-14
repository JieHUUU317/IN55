#define _USE_MATH_DEFINES


#include "Object3D.h"
#include "GlCamera.h"
#include "GlQuaternion.h"
#include <cmath>
#include "GLMatrix.h"
#include <limits>
#include "LF_String.h"
#include <iostream>

using namespace  std;

GlCamera::GlCamera(float32 px, float32 py, float32 pz, float32 ex,float32 ey,float32 ez){
    m_postion.x = px;
    m_postion.y = py;
    m_postion.z = pz;
    m_Orientation.setX(ex - px);
    m_Orientation.setY(ey - py);
    m_Orientation.setZ(ez - pz);
    m_Orientation.setScalar(0.0f);
    m_Orientation.normalize();
    ratio = FOVAngle = nearp = nearpf =0.0f;
 }

AbstractVec3<float32> GlCamera::getMPosition(){
    return m_postion;
}

AbstractVec3<float32> GlCamera::getMOrientation(){
    return m_Orientation.vector();
}

void GlCamera::translateO(float32 shift, float32 upX, float32 upY, float32 upZ){

    GLfloat forwardX = m_Orientation.x();
    GLfloat forwardY = m_Orientation.y();
    GLfloat forwardZ = m_Orientation.z();

    GLfloat forwardLen = std::sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    if(forwardLen > std::numeric_limits<GLfloat>::epsilon())
    {
    forwardX /= forwardLen;
    forwardY /= forwardLen;
    forwardZ /= forwardLen;
    }
    GLfloat shiftX = forwardX*shift;
    GLfloat shiftY = forwardY*shift;
    GLfloat shiftZ = forwardZ*shift;

    m_postion.x = m_postion.x + shiftX;
    m_postion.y = m_postion.y + shiftY;
    m_postion.z = m_postion.z + shiftZ;

}

void GlCamera::translateR(float32 shift, float32 upX, float32 upY, float32 upZ){

    GLfloat forwardX = m_Orientation.x();
    GLfloat forwardY = m_Orientation.y();
    GLfloat forwardZ = m_Orientation.z();

    GLfloat forwardLen = std::sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    if(forwardLen > std::numeric_limits<GLfloat>::epsilon())
    {
    forwardX /= forwardLen;
    forwardY /= forwardLen;
    forwardZ /= forwardLen;
    }

    GLfloat upLen = std::sqrt(upX * upX + upY * upY + upZ * upZ);
    if(upLen > std::numeric_limits<GLfloat>::epsilon())
    {
    upX /= upLen;
    upY /= upLen;
    upZ /= upLen;
    }

    GLfloat sX = forwardY * upZ - forwardZ * upY;
    GLfloat sY = forwardZ * upX - forwardX * upZ;
    GLfloat sZ = forwardX * upY - forwardY * upX;

    GLfloat shiftX = sX*shift;
    GLfloat shiftY = sY*shift;
    GLfloat shiftZ = sZ*shift;

    m_postion.x = m_postion.x + shiftX;
    m_postion.y = m_postion.y + shiftY;
    m_postion.z = m_postion.z + shiftZ;

}

void GlCamera::rotateR(double angle, float32 sX, float32 sY, float32 sZ){
    GLfloat forwardX = m_Orientation.x();
    GLfloat forwardY = m_Orientation.y();
    GLfloat forwardZ = m_Orientation.z();

    GLfloat forwardLen = std::sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    if(forwardLen > std::numeric_limits<GLfloat>::epsilon())
    {
    forwardX /= forwardLen;
    forwardY /= forwardLen;
    forwardZ /= forwardLen;
    }

    GLfloat upLen = std::sqrt(sX * sX + sY * sY + sZ * sZ);
    if(upLen > std::numeric_limits<GLfloat>::epsilon())
    {
    sX /= upLen;
    sY /= upLen;
    sZ /= upLen;
    }

    GLfloat upX = sY * forwardZ - sZ * forwardY;
    GLfloat upY = sZ * forwardX - sX * forwardZ;
    GLfloat upZ = sX * forwardY - sY * forwardX;

    GLfloat c = std::cos(angle/2.0f);
    GLfloat s = std::sin(angle/2.0f);
    GlQuaternion* rotation = new GlQuaternion(c,upX*s,upY*s,upZ*s);
    rotation->normalize();
    m_Orientation = (*rotation)*(m_Orientation)*rotation->conjugate();
}


void GlCamera::rotateU(double angle, float32 upX, float32 upY, float32 upZ){
    GLfloat forwardX = m_Orientation.x();
    GLfloat forwardY = m_Orientation.y();
    GLfloat forwardZ = m_Orientation.z();

    GLfloat forwardLen = std::sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    if(forwardLen > std::numeric_limits<GLfloat>::epsilon())
    {
    forwardX /= forwardLen;
    forwardY /= forwardLen;
    forwardZ /= forwardLen;
    }

    GLfloat upLen = std::sqrt(upX * upX + upY * upY + upZ * upZ);
    if(upLen > std::numeric_limits<GLfloat>::epsilon())
    {
    upX /= upLen;
    upY /= upLen;
    upZ /= upLen;
    }

    GLfloat sX = forwardY * upZ - forwardZ * upY;
    GLfloat sY = forwardZ * upX - forwardX * upZ;
    GLfloat sZ = forwardX * upY - forwardY * upX;

    GLfloat uX = sY * forwardZ - sZ * forwardY;
    GLfloat uY = sZ * forwardX - sX * forwardZ;
    GLfloat uZ = sX * forwardY - sY * forwardX;

    GLfloat c = std::cos(angle/2.0f);
    GLfloat s = std::sin(angle/2.0f);
    GlQuaternion* rotation = new GlQuaternion(c,uX*s,uY*s,uZ*s);
    rotation->normalize();

    m_Orientation = (*rotation)*(m_Orientation)*rotation->conjugate();
}


void GlCamera::rotate(float32 angle, float32 x, float32 y, float32 z){
    /**

    m_forward.x = newOrientation.x();
    m_forward.y = newOrientation.y();
    m_forward.z = newOrientation.z();

    m_up.x = 0.0f;
    m_up.y = 1.0f;
    m_up.z = 0.0f;

    m_right = m_forward.crossProduct(m_up);
    m_right.normalize();
    m_up = m_right.crossProduct(m_forward);
    m_up.normalize();
    std::cout << "m_forward : " << m_forward.x << "," << m_forward.y << "," << m_forward.z << std::endl;
    std::cout << "m_up : " << m_up.x << "," << m_up.y << "," << m_up.z << std::endl;
    std::cout << "m_right : " << m_right.x << "," << m_right.y << "," << m_right.z << std::endl;
     std::cout << "m_postion : " << m_postion.x << "," << m_postion.y << "," << m_postion.z << std::endl;

    GLfloat Tx = -(m_right.x)*m_postion.x - (m_right.y)*m_postion.y - (m_right.z)*m_postion.z;
    GLfloat Ty = -(m_up.x)*m_postion.x - (m_up.y)*m_postion.y - (m_up.z)*m_postion.z;
    GLfloat Tz = - (m_forward.x)*m_postion.x - (m_forward.y)*m_postion.y - (m_forward.z)*m_postion.z;

    m_ViewMatrix.m[0][0] = m_right.x;        m_ViewMatrix.m[0][1] = m_right.y;        m_ViewMatrix.m[0][2] = m_right.z;        m_ViewMatrix.m[0][3] = Tx;
    m_ViewMatrix.m[1][0] = m_up.x;        m_ViewMatrix.m[1][1] = m_up.y;        m_ViewMatrix.m[1][2] = m_up.z;        m_ViewMatrix.m[1][3] = Ty;
    m_ViewMatrix.m[2][0] = m_forward.x; m_ViewMatrix.m[2][1] = m_forward.y; m_ViewMatrix.m[2][2] = m_forward.z; m_ViewMatrix.m[2][3] = Tz;
    m_ViewMatrix.m[3][0] = 0.0f;      m_ViewMatrix.m[3][1] = 0.0f;      m_ViewMatrix.m[3][2] = 0.0f;      m_ViewMatrix.m[3][3] = 1.0f;

    GLfloat nw = newOrientation.scalar();
    GLfloat nx = newOrientation.x();
    GLfloat ny = newOrientation.y();
    GLfloat nz = newOrientation.z();
    //std::cout << "newOrientation : " << newOrientation.x() << "," << newOrientation.y() << "," << newOrientation.z() << std::endl;

    m_ViewMatrix.m[0][0] = 1 - 2*ny*ny -2*nz*nz;        m_ViewMatrix.m[0][1] = 2*nx*ny - 2*nw*nz;        m_ViewMatrix.m[0][2] = 2*nx*nz + 2*nw*ny;
    m_ViewMatrix.m[1][0] = 2*nx*ny + 2*nw*nz;        m_ViewMatrix.m[1][1] = 1 - 2*nx*nx - 2*nz*nz;        m_ViewMatrix.m[1][2] = 2*ny*nz - 2*nw*nx;
    m_ViewMatrix.m[2][0] = 2*nx*nz - 2*nw*ny;        m_ViewMatrix.m[2][1] = 2*ny*nz + 2*nw*nx; m_ViewMatrix.m[2][2] = 1 - 2*nx*nx - 2*ny*ny;
*/}

GLMatrix& GlCamera::getViewMatrix(){
    return m_ViewMatrix;
}

GLMatrix &GlCamera::getProjectionMatrix(){
    return m_ProjectionMatrix;
}

void GlCamera::setAspectRatio(float32 aspectRatio){
    ratio = aspectRatio;
}

void GlCamera::setPlanes(float32 np, float32 fp){
    nearp = np;
    nearpf = fp;
}

void GlCamera::setFOV(float32 angle){
    FOVAngle = angle;
}

void GlCamera:: buildViewMatrix(){
    /**
    m_Orientation.normalize();
    AbstractVec3 m_forward = new AbstractVec3();
    AbstractVec3 m_up = new AbstractVec3();
    AbstractVec3 m_right = new AbstractVec3();

    m_forward.x = m_Orientation.x();
    m_forward.y = m_Orientation.y();
    m_forward.z = m_Orientation.z();

    m_up.x = 0.0f;
    m_up.y = 1.0f;
    m_up.z = 0.0f;

    m_right = m_forward.crossProduct(m_up);
    m_right.normalize();
    m_up = m_right.crossProduct(m_forward);
    m_up.normalize();
    GLfloat Tx =  (- 1 + 2*y*y + 2*z*z)*m_postion.x - (2*x*y - 2*w*z)*m_postion.y - (2*x*z + 2*w*y)*m_postion.z;
    GLfloat Ty = - (2*x*y + 2*w*z)*m_postion.x - (1 - 2*x*x - 2*z*z)*m_postion.y - (2*y*z - 2*w*x)*m_postion.z;
    GLfloat Tz = - (2*x*z - 2*w*y)*m_postion.x - (2*y*z + 2*w*x)*m_postion.y - (1 - 2*x*x - 2*y*y)*m_postion.z;

    GLfloat Tx = -(m_right.x)*m_postion.x - (m_right.y)*m_postion.y - (m_right.z)*m_postion.z;
    GLfloat Ty = -(m_up.x)*m_postion.x - (m_up.y)*m_postion.y - (m_up.z)*m_postion.z;
    GLfloat Tz = - (m_forward.x)*m_postion.x - (m_forward.y)*m_postion.y - (m_forward.z)*m_postion.z;

    m_ViewMatrix.m[0][0] = 0.0f;        m_ViewMatrix.m[0][1] = 0.0f;        m_ViewMatrix.m[0][2] = 0.0f;        m_ViewMatrix.m[0][3] = 0.0f;
    m_ViewMatrix.m[1][0] = 0.0f;        m_ViewMatrix.m[1][1] = 0.0f;        m_ViewMatrix.m[1][2] = 0.0f;        m_ViewMatrix.m[1][3] = 0.0f;
    m_ViewMatrix.m[2][0] = 0.0f;        m_ViewMatrix.m[2][1] = 0.0f;        m_ViewMatrix.m[2][2] = 0.0f;        m_ViewMatrix.m[2][3] = 0.0f;
    m_ViewMatrix.m[3][0] = 0.0f;       m_ViewMatrix.m[3][1] = 0.0f;         m_ViewMatrix.m[3][2] = 0.0f;        m_ViewMatrix.m[3][3] = 1.0f;

    GLMatrix t;
    t.m[0][0] = 1.0f; t.m[0][1] = 0.0f; t.m[0][2] = 0.0f; t.m[0][3] = -m_postion.x;
    t.m[1][0] = 0.0f; t.m[1][1] = 1.0f; t.m[1][2] = 0.0f; t.m[1][3] = -m_postion.y;
    t.m[2][0] = 0.0f; t.m[2][1] = 0.0f; t.m[2][2] = 1.0f; t.m[2][3] = -m_postion.z;
    t.m[3][0] = 0.0f; t.m[3][1] = 0.0f; t.m[3][2] = 0.0f; t.m[3][3] = 1.0f;

    m_ViewMatrix = m_ViewMatrix * t;
    GLfloat w = m_Orientation.scalar();
    GLfloat x = m_Orientation.x();
    GLfloat y = m_Orientation.y();
    GLfloat z = m_Orientation.z();



    m_ViewMatrix.m[0][0] = 1 - 2*y*y -2*z*z;        m_ViewMatrix.m[0][1] = 2*x*y - 2*w*z;        m_ViewMatrix.m[0][2] = 2*x*z + 2*w*y;      m_ViewMatrix.m[0][3] = Tx;
    m_ViewMatrix.m[1][0] = 2*x*y + 2*w*z;          m_ViewMatrix.m[1][1] = 1 - 2*x*x - 2*z*z;    m_ViewMatrix.m[1][2] = 2*y*z - 2*w*x;       m_ViewMatrix.m[1][3] = Ty;
    m_ViewMatrix.m[2][0] = 2*x*z - 2*w*y;           m_ViewMatrix.m[2][1] = 2*y*z + 2*w*x;       m_ViewMatrix.m[2][2] = 1 - 2*x*x - 2*y*y;   m_ViewMatrix.m[2][3] = Tz;
    m_ViewMatrix.m[3][0] = 0.0f;                          m_ViewMatrix.m[3][1] = 0.0f;                        m_ViewMatrix.m[3][2] = 0.0f;                       m_ViewMatrix.m[3][3] = 1.0f;
        */
}

void GlCamera::buildPerspectiveProjectionMatrix(){
    GLfloat thetaY = 0.5f * (M_PI * FOVAngle / 180.0f);
    GLfloat tanThetaY = tan(thetaY);
    GLfloat tanThetaX = tanThetaY * ratio;
    GLfloat halfW   =  tanThetaX * nearp;
    GLfloat halfH   =  tanThetaY * nearp;
    GLfloat left    = -halfW;
    GLfloat right   =  halfW;
    GLfloat bottom  = -halfH;
    GLfloat top     =  halfH;
    GLfloat iWidth  = 1.0f / (right - left);
    GLfloat iHeight = 1.0f / (top - bottom);
    GLfloat iDepth  = 1.0f / (nearpf - nearp);

    m_ProjectionMatrix.m[0][0] = 2.0f * nearp * iWidth; m_ProjectionMatrix.m[0][1] = 0.0f;                   m_ProjectionMatrix.m[0][2] =  (right + left) * iWidth;  m_ProjectionMatrix.m[0][3] =  0.0f;
    m_ProjectionMatrix.m[1][0] = 0.0f;                  m_ProjectionMatrix.m[1][1] = 2.0f * nearp * iHeight; m_ProjectionMatrix.m[1][2] =  (top + bottom) * iHeight; m_ProjectionMatrix.m[1][3] =  0.0f;
    m_ProjectionMatrix.m[2][0] = 0.0f;                  m_ProjectionMatrix.m[2][1] = 0.0f;                   m_ProjectionMatrix.m[2][2] = -(nearpf + nearp) * iDepth;  m_ProjectionMatrix.m[2][3] = -2.0f * (nearpf * nearp) * iDepth;
    m_ProjectionMatrix.m[3][0] = 0.0f;                  m_ProjectionMatrix.m[3][1] = 0.0f;                   m_ProjectionMatrix.m[3][2] = -1.0f;                     m_ProjectionMatrix.m[3][3] =  0.0f;
}

void GlCamera::buildOrthoProjectionMatrix(){
    GLfloat thetaY = 0.5f * (M_PI * FOVAngle / 180.0f);
    GLfloat tanThetaY = tan(thetaY);
    GLfloat tanThetaX = tanThetaY * ratio;
    GLfloat halfW   =  tanThetaX * nearp;
    GLfloat halfH   =  tanThetaY * nearp;
    GLfloat left    = -halfW;
    GLfloat right   =  halfW;
    GLfloat bottom  = -halfH;
    GLfloat top     =  halfH;
    GLfloat iWidth  = 1.0f / (right - left);
    GLfloat iHeight = 1.0f / (top - bottom);
    GLfloat iDepth  = 1.0f / (nearpf - nearp);

    m_ProjectionMatrix.m[0][0] = 2.0f * iWidth;    m_ProjectionMatrix.m[0][1] = 0.0f;             m_ProjectionMatrix.m[0][2] = 0.0f;             m_ProjectionMatrix.m[0][3] = -(right+left) * iWidth;
    m_ProjectionMatrix.m[1][0] = 0.0f;             m_ProjectionMatrix.m[1][1] = 2.0f * iHeight;   m_ProjectionMatrix.m[1][2] = 0.0f;             m_ProjectionMatrix.m[1][3] =  -(top+bottom) * iHeight;
    m_ProjectionMatrix.m[2][0] = 0.0f;             m_ProjectionMatrix.m[2][1] = 0.0f;             m_ProjectionMatrix.m[2][2] = 2.0f * iDepth;    m_ProjectionMatrix.m[2][3] = (nearpf+nearp) * iDepth;
    m_ProjectionMatrix.m[3][0] = 0.0f;             m_ProjectionMatrix.m[3][1] = 0.0f;             m_ProjectionMatrix.m[3][2] = 0.0f;             m_ProjectionMatrix.m[3][3] =  1.0f;
}
