#ifndef GLMATRIX
#define GLMATRIX
#include <QGLWidget>
#include <limits>
#include "LF_String.h"

struct GLMatrix
{
    union
    {
        GLfloat m[4][4];
        GLfloat data[16];
    };

    void setIdentity();
};

GLMatrix operator*(const GLMatrix &, const GLMatrix &);
GLMatrix inverse( const GLMatrix & );
GLfloat det( const GLMatrix & );



#endif // GLMATRIX
