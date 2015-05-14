#include "GLMatrix.h"
#include <QMessageBox>
#include <QGLWidget>
#include <limits>
#include "LF_String.h"

using namespace std;


void
GLMatrix::setIdentity()
{
    m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
    m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
    m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
    m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
}

GLMatrix
operator*( const GLMatrix & mat1, const GLMatrix & mat2 )
{
    GLMatrix result;

    for(int idx = 0; idx < 4; idx++)
    {
        for(int idy = 0; idy < 4; idy++)
        {
            result.m[idy][idx] = 0.0f;
            for(int idz = 0; idz < 4; idz++)
            {
                result.m[idy][idx] += mat1.m[idy][idz] * mat2.m[idz][idx];
            }
        }
    }
    return result;
}

GLfloat
det( const GLMatrix & mat )
{
    GLfloat det;

    det = mat.data[0] * (mat.data[5] * mat.data[10] - mat.data[6] * mat.data[9])
        - mat.data[1] * (mat.data[4] * mat.data[10] - mat.data[6] * mat.data[8])
        + mat.data[2] * (mat.data[4] * mat.data[9] - mat.data[5] * mat.data[8]);

    return det;
}


GLMatrix
inverse( const GLMatrix & mat )
{
    GLMatrix result;
    GLfloat d = det(mat);

    if (fabs(d) < 0.0005)
    {
        result.setIdentity();
    }
    else
    {
        d = 1.0f/d;

        result.data[0] =  (mat.data[5] * mat.data[10] - mat.data[6] * mat.data[9]) * d;
        result.data[1] = -(mat.data[1] * mat.data[10] - mat.data[9] * mat.data[2]) * d;
        result.data[2] =  (mat.data[1] * mat.data[6] - mat.data[5] * mat.data[2]) * d;

        result.data[3] = -(mat.data[4] * mat.data[10] - mat.data[6] * mat.data[8]) * d;
        result.data[4] =  (mat.data[0] * mat.data[10] - mat.data[2] * mat.data[8]) * d;
        result.data[5] = -(mat.data[0] * mat.data[6] - mat.data[2] * mat.data[4]) * d;

        result.data[6] =  (mat.data[4] * mat.data[9] - mat.data[5] * mat.data[8]) * d;
        result.data[7] = -(mat.data[0] * mat.data[9] - mat.data[1] * mat.data[8]) * d;
        result.data[8] =  (mat.data[0] * mat.data[5] - mat.data[1] * mat.data[4]) * d;
    }

    return result;
}
