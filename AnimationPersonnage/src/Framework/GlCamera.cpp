#include "src/Shapes/Object3D.h"
#include "GlCamera.h"
//#include <cmath>
//#include <limits>
//#include "LF_String.h"
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include <iostream>

using namespace  glm;

GlCamera::GlCamera(float32 px, float32 py, float32 pz, float32 ex,float32 ey,float32 ez){
    m_postion.x = px;
    m_postion.y = py;
    m_postion.z = pz;
    m_Orientation.x=ex-px;
    m_Orientation.y=ey-py;
    m_Orientation.z=ez-pz;
    m_Orientation.w=0.0f;
    normalize(m_Orientation);
    ratio = FOVAngle = nearp = nearpf =0.0f;
 }

mat3<float32> GlCamera::getMPosition(){
    return m_postion;
}

quat GlCamera::getMOrientation(){
    return m_Orientation;
}

void GlCamera::translateO(float32 shift, float32 upX, float32 upY, float32 upZ){

    GLfloat forwardX = m_Orientation.x;
    GLfloat forwardY = m_Orientation.y;
    GLfloat forwardZ = m_Orientation.z;

    GLfloat forwardLen = glm::sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    if(forwardLen > (GLfloat)epsilon())
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

   /** GLfloat forwardX = m_Orientation.x;
    GLfloat forwardY = m_Orientation.y;
    GLfloat forwardZ = m_Orientation.z;

    GLfloat forwardLen = std::sqrt(forwardX * forwardX + forwardY * forwardY + forwardZ * forwardZ);
    if(forwardLen > std::numeric_limits<GLfloat>::epsilon())
    {
    forwardX /= forwardLen;
    forwardY /= forwardLen;
    forwardZ /= forwardLen;
    }
    GLfloat sX = forwardY * upZ - forwardZ * upY;
    GLfloat sY = forwardZ * upX - forwardX * upZ;
    GLfloat sZ = forwardX * upY - forwardY * upX;
    GLfloat shiftX = rt*shift;
    GLfloat shiftY = sY*shift;
    GLfloat shiftZ = sZ*shift;
    m_postion.x = m_postion.x + shiftX;
    m_postion.y = m_postion.y + shiftY;
    m_postion.z = m_postion.z + shiftZ;
    */

    vec3 up = vec3(upX,upY,upZ);
    normalize(up);
    vec3 fw = vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    normalize(fw);
    vec3 rt = cross(up,fw);
    normalize(rt);
    vec3  sft = rt*shift;
    m_postion += sft;

}

void GlCamera::rotateR(double angle, float32 upX, float32 upY, float32 upZ){
    /**
    GLfloat forwardX = m_Orientation.x;
    GLfloat forwardY = m_Orientation.y;
    GLfloat forwardZ = m_Orientation.z;

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
    GLfloat c = std::cos(angle/2.0f);
    GLfloat s = std::sin(angle/2.0f);
    GLfloat upX = (sY * forwardZ - sZ * forwardY)*s;
    GLfloat upY = (sZ * forwardX - sX * forwardZ)*s;
    GLfloat upZ = (sX * forwardY - sY * forwardX)*s;

    quat rotation = quat(c,upX*s,upY*s,upZ*s);
    normalize(rotation);
    rotate(m_Orientation,);
    m_Orientation = rotation*(m_Orientation)*conjugate(rotation);
    */
    vec3 up = vec3(upX,upY,upZ);
    normalize(up);
    vec3 fw = vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    normalize(fw);
    vec3 rt = cross(up,fw);
    normalize(rt);
    m_Orientation = rotate(m_Orientation,angle,rt);

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

vec3<float32>& GlCamera::getViewMatrix(){
    return m_ViewMatrix;
}

vec3<float32>& GlCamera::getProjectionMatrix(){
    return m_ProjectionMatrix;
}

void GlCamera::setAspectRatio(float32 aspectRatio){
    ratio = aspectRatio;
}

void GlCamera::setPlanes(float32 np, float32 fp){
    nearp = np;
    nearpf = fp;
}

void GlCamera::setFOV(float angle){
    FOVAngle = angle;
}

void GlCamera:: buildViewMatrix(){
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
