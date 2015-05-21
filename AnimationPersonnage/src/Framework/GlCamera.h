#ifndef GLCAMERA
#define GLCAMERA

#include <QLinkedList>
#include"GL/glew.h"
#include <QImage>
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"

class GlCamera {

protected:

    glm::vec3  m_postion;
    glm::quat m_Orientation;
    glm::mat4 m_ViewMatrix, m_ProjectionMatrix;
    GLfloat ratio, FOVAngle, nearp, nearpf;

public:

    GlCamera(GLfloat px, GLfloat py, GLfloat pz, GLfloat ex,GLfloat ey,GLfloat e);

    void translateO(GLfloat shift, GLfloat sX, GLfloat sY, GLfloat upZ);

    void translateR(GLfloat shift, GLfloat sX, GLfloat sY, GLfloat sZ);

    void rotateR(GLfloat angle, GLfloat upX, GLfloat upY, GLfloat upZ);

    void rotateU(GLfloat angle, GLfloat upX, GLfloat upY, GLfloat upZ);

    void setAspectRatio(GLfloat aspectRatio);

    void setPlanes(GLfloat nearp, GLfloat farp);

    void setFOV(GLfloat angle);

    glm::vec3 getMPosition();

    glm::quat getMOrientation();
};

#endif
