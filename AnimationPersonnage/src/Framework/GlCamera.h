#ifndef GLCAMERA
#define GLCAMERA

#include <QLinkedList>
#include"include/GL/glew.h"
#include <QImage>
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include "include/GLM/gtc/quaternion.hpp"
#include <string>

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

    void rotateR(double angle, float32 sX, float32 sY, float32 sZ);

    void rotateU(double angle, float32 upX, float32 upY, float32 upZ);

    /**
     * @brief get the view matrix
     * @return
     */
    vec3<float32>& getViewMatrix();

    /**
     * @brief get the projection matrix
     * @return
     */

  vec3<float32>& getProjectionMatrix();

    /**
     * @brief set the ration of the view of camera
     * @param ar
     */
    void setAspectRatio(float32 aspectRatio);

    /**
     * @brief setPlanes
     * @param np
     * @param fp
     */
    void setPlanes(float32 nearp, float32 farp);

    /**
    * @brief set the field of view
    * @param angle
    */
    void setFOV(float angle);

    vec3<float32> getMPosition();

    vec3<float32> getMOrientation();

    /**
    * @brief builders for the matrix
    */
    void buildViewMatrix();

    void buildPerspectiveProjectionMatrix();

    void buildOrthoProjectionMatrix();

};

#endif
