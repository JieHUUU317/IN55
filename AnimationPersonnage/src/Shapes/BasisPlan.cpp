#include "BasisPlan.h"
#include <stdio.h>
#include <string.h>



BasisPlan::BasisPlan()
{
    m_TabVertices = new GLfloat[612];
    m_TableColors = new GLfloat[612];
    m_TabIeIndices = new GLuint[204];

    for(GLuint j = 0; j <= 150; j+=3){
        m_TabVertices[j] = -250.0f + j/3*10;
        m_TabVertices[j+1] =  0.0f;;
        m_TabVertices[j+2] =  -250.0f;
    }

    for(GLuint j = 153; j <= 303; j+=3){
        m_TabVertices[j] = -250.0f + (j-153)/3*10;
        m_TabVertices[j+1] =  0.0f;
        m_TabVertices[j+2] =  250.0f;
    }
    for(GLuint j = 306; j <= 456; j+=3){
        m_TabVertices[j] = -250.0f;
        m_TabVertices[j+1] =  0.0f;
        m_TabVertices[j+2] =  -250.0f + (j-306)/3*10;
    }

    for(GLuint j = 459; j <= 609; j+=3){
        m_TabVertices[j] = 250.0f;
        m_TabVertices[j+1] =  0.0f;
        m_TabVertices[j+2] =  -250.0f + (j-459)/3*10;
    }

    for(GLuint j = 0; j <= 609; j+=3){
        m_TableColors[j] = 1;
        m_TableColors[j+1] =  1;
        m_TableColors[j+2] =  1;
    }

    for(GLuint i = 0; i <= 100; i+=2){
        m_TabIeIndices[i] = i/2;
        m_TabIeIndices[i+1] = i/2+51;
    }
    for(GLuint i = 102, k =0; i <= 202; i+=2,k++){
        m_TabIeIndices[i] = i-k;
        m_TabIeIndices[i+1] = i-k+51;
    }

}


void
BasisPlan::drawShape(const char *shader_name)
{
    GLint var1 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "position" );
    glEnableVertexAttribArray( var1 );
    glVertexAttribPointer( var1, 3, GL_FLOAT, GL_FALSE, 0, m_TabVertices );
    GLint var2 = glGetAttribLocation( m_Framework->getCurrentShaderId(), "color" );
    glEnableVertexAttribArray( var2 );
    glVertexAttribPointer( var2, 3, GL_FLOAT, GL_FALSE, 0, m_TableColors );
    glDrawElements( GL_LINES, 204, GL_UNSIGNED_INT, m_TabIeIndices );
    glDisableVertexAttribArray( var1 );
    glDisableVertexAttribArray( var2 );
}

