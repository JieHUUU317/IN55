#ifndef GLCAMERA
#define GLCAMERA

#include <QLinkedList>
#include"GL/glew.h"
#include <QImage>
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"

using namespace glm;

class GlCamera {

protected:

    vec3<float32>  m_postion;
    quat m_Orientation;
    mat4 m_ViewMatrix, m_ProjectionMatrix;
    float32 ratio, FOVAngle, nearp, nearpf;

public:

    GlCamera();
    ~GlCamera();

    GlCamera(float32 px, float32 py, float32 pz, float32 ex,float32 ey,float32 e);

    void translateO(float32 shift, float32 sX, float32 sY, float32 upZ);

    void translateR(float32 shift, float32 sX, float32 sY, float32 sZ);

    void rotateR(float32 angle, float32 upX, float32 upY, float32 upZ);

    void rotateU(float32 angle, float32 upX, float32 upY, float32 upZ);

    void setAspectRatio(float32 aspectRatio);

    void setPlanes(float32 nearp, float32 farp);

    void setFOV(float32 angle);

    vec3<float32> getMPosition();

    vec3<float32> getMOrientation();
};

#endif
