#include "src/Shapes/Object3D.h"
#include "GlCamera.h"
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include <iostream>


GlCamera::GlCamera(GLfloat px, GLfloat py, GLfloat pz, GLfloat ex, GLfloat ey, GLfloat ez){
    m_postion.x = px;
    m_postion.y = py;
    m_postion.z = pz;
    m_Orientation.x = ex-px;
    m_Orientation.y = ey-py;
    m_Orientation.z = ez-pz;
    m_Orientation.w = 0.0f;
    glm::normalize(m_Orientation);
    ratio = FOVAngle = nearp = nearpf = 0.0f;
 }

glm::vec3 GlCamera::getMPosition(){
    return m_postion;
}

glm::quat GlCamera::getMOrientation(){
    return m_Orientation;
}

void GlCamera::translateO(GLfloat shift, GLfloat upX, GLfloat upY, GLfloat upZ){
    glm:: vec3 fw =  glm::vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    glm::normalize(fw);
    glm::vec3  sft = fw*shift;
     m_postion += sft;
}

void GlCamera::translateR(GLfloat shift, GLfloat upX, GLfloat upY, GLfloat upZ){
    glm::vec3 up =  glm::vec3(upX,upY,upZ);
    glm::normalize(up);
    glm::vec3 fw = glm::vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    glm::normalize(fw);
    glm::vec3 rt = glm::cross(up,fw);
    glm::normalize(rt);
    glm::vec3  sft = rt*shift;
    m_postion += sft;

}

void GlCamera::rotate(glm::quat x, glm::quat y){
    m_Orientation = y*x*m_Orientation*glm::inverse(x)*glm::inverse(y);
}

void GlCamera::rotateR(GLfloat angle, GLfloat upX, GLfloat upY, GLfloat upZ){
    glm::vec3 up = glm::vec3(upX,upY,upZ);
    glm::normalize(up);
    glm::vec3 fw = glm::vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    glm::normalize(fw);
    glm::vec3 rt = glm::cross(up,fw);
    glm::normalize(rt);
    m_Orientation = glm::rotate(m_Orientation,angle,rt);
}

void GlCamera::rotateU(GLfloat angle, GLfloat upX, GLfloat upY, GLfloat upZ){
    glm::vec3 upIn = glm::vec3(upX,upY,upZ);
    glm::normalize(upIn);
    glm::vec3 fw = glm::vec3(m_Orientation.x,m_Orientation.y,m_Orientation.z);
    glm::normalize(fw);
    glm::vec3 rt = glm::cross(upIn,fw);
    glm::vec3 up = glm::cross(rt,fw);
    glm::normalize(up);
    m_Orientation = glm::rotate(m_Orientation,angle,up);
}

void GlCamera::setAspectRatio(GLfloat aspectRatio){
    ratio = aspectRatio;
}

void GlCamera::setPlanes(GLfloat np, GLfloat fp){
    nearp = np;
    nearpf = fp;
}

void GlCamera::setFOV(GLfloat angle){
    FOVAngle = angle;
}
