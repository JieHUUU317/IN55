#include "src/Shapes/Object3D.h"
#include "GlCamera.h"
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include <iostream>

using namespace  glm;

GlCamera::GlCamera(float32 px, float32 py, float32 pz, float32 ex, float32 ey, float32 ez){
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
    vec3 fw = vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    normalize(fw);
    vec3  sft = fw*shift;
     m_postion += sft;
}

void GlCamera::translateR(float32 shift, float32 upX, float32 upY, float32 upZ){
    vec3 up = vec3(upX,upY,upZ);
    normalize(up);
    vec3 fw = vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    normalize(fw);
    vec3 rt = cross(up,fw);
    normalize(rt);
    vec3  sft = rt*shift;
    m_postion += sft;

}

void GlCamera::rotateR(float32 angle, float32 upX, float32 upY, float32 upZ){
    vec3 up = vec3(upX,upY,upZ);
    normalize(up);
    vec3 fw = vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    normalize(fw);
    vec3 rt = cross(up,fw);
    normalize(rt);
    m_Orientation = rotate(m_Orientation,angle,rt);
}

void GlCamera::rotateU(float32 angle, float32 upX, float32 upY, float32 upZ){
    vec3 upIn = vec3(upX,upY,upZ);
    normalize(upIn);
    vec3 fw = vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    normalize(fw);
    vec3 rt = cross(upIn,fw);
    vec3 up = cross(rt,fw);
    normalize(up);
    m_Orientation = rotate(m_Orientation,angle,up);
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
