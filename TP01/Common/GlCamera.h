#ifndef GLCAMERA
#define GLCAMERA

#define _USE_MATH_DEFINES
#include <cmath>
#include <QLinkedList>
#include <QImage>
#include <Types.h>
#include "GLMatrix.h"
#include "Vectors.h"
#include <string>
#include "GlQuaternion.h"

class GlCamera {

protected:

    AbstractVec3<float32>  m_postion;
    GlQuaternion m_Orientation;
    GLMatrix m_ViewMatrix, m_ProjectionMatrix;
    GLfloat ratio, FOVAngle, nearp, nearpf;

public:

    GlCamera();
    ~GlCamera();

    GlCamera(float32 px, float32 py, float32 pz, float32 ex,float32 ey,float32 e);

    //void translate(float32 x, float32 y, float32 z);

    void translateO(float32 shift, float32 sX, float32 sY, float32 upZ);

    void translateR(float32 shift, float32 sX, float32 sY, float32 sZ);

    void rotateR(double angle, float32 sX, float32 sY, float32 sZ);

    void rotateU(double angle, float32 upX, float32 upY, float32 upZ);

    /**
     * @brief rotate the camera in angle around the direction (ax,ay,az)
     * @param angle
     * @param ax
     * @param ay
     * @param az
     */
    void rotate(float32 angle, float32 ax, float32 ay, float32 az);

    /**
     * @brief get the view matrix
     * @return
     */
    GLMatrix& getViewMatrix();

    /**
     * @brief get the projection matrix
     * @return
     */

    GLMatrix& getProjectionMatrix();

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
    void setFOV(float32 angle);

    AbstractVec3<float32> getMPosition();

    AbstractVec3<float32> getMOrientation();

    /**
     * @brief builders for the matrixs
     */
    void buildViewMatrix();

    void buildPerspectiveProjectionMatrix();

    void buildOrthoProjectionMatrix();

};

#endif
