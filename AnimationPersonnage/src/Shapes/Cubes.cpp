//*****************************************************************************
//
// Classes: MulticolorCube, TwoColorCube, MultipleColorCube
// Author: Fabrice LAURI (fabrice.lauri@utbm.fr)
//         (Associate Professor at the
//          "Université de Technologie de Belfort-Montbéliard", France)
// Version: 1.0
// Last update: 2012-05-01
//
//*****************************************************************************


#include "Shapes/Cubes.h"

#include <stdio.h>
#include <string.h>


const GLfloat size = 1.0f;
GLfloat sizex = 1.0f;
GLfloat sizey = 1.0f;
GLfloat sizez = 1.0f;



GLfloat mc_tab_vertices[] =
{
    -sizex, -sizey,  sizez,
     sizex, -sizey,  sizez,
    -sizex,  sizey,  sizez,
     sizex,  sizey,  sizez,
    -sizex, -sizey, -sizez,
     sizex, -sizey, -sizez,
    -sizex,  sizey, -sizez,
     sizex,  sizey, -sizez
};

GLfloat mc_tab_colors[] =
{
    1,0,0,	// Red
    0,1,0,	// Green
    0,0,1,	// Blue
    0,1,1,	// Cyan
    1,1,0,	// Yellow
    1,0,1,	// Purple
    0,0,0,	// Black
    1,1,1	// White
};

GLuint mc_tab_indices[] =
{
    0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
};

GLuint mc_buffers[3];


GLuint g_CubeFaces[] =
{
    4, 0, 6, 2, // Left
    1, 5, 3, 7, // Right
    4, 5, 0, 1,	// Down
    2, 3, 6, 7, // Up
    4, 5, 6, 7,	// Back
    0, 1, 2, 3	// Front
};

GLfloat g_TabTexCoords[] =
{
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
};


GLfloat surf_diffuse[]={0.8,0.8,0.0,1.0};
GLfloat surf_speculaire[]={1.0,1.0,0.0,1.0};
GLfloat surf_shininess[]={100.0};


MulticolorCube::MulticolorCube()
{
    m_VBO = false;
}

void MulticolorCube::initVBO()
{
    glGenBuffers( 3, mc_buffers );
    glBindBuffer( GL_ARRAY_BUFFER, mc_buffers[0] );
    glBufferData( GL_ARRAY_BUFFER, 8*3*sizeof(GLfloat), mc_tab_vertices, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mc_buffers[1] );
    glBufferData( GL_ARRAY_BUFFER, 8*3*sizeof(GLfloat), mc_tab_colors, GL_STATIC_DRAW );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mc_buffers[2] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, 14*sizeof(GLuint), mc_tab_indices, GL_STATIC_DRAW );
    m_VBO = true;
}

void MulticolorCube::drawShape( const char* shader_name )
{
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );

    if (m_VBO)
    {
        glBindBuffer( GL_ARRAY_BUFFER, mc_buffers[0] );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glBindBuffer( GL_ARRAY_BUFFER, mc_buffers[1] );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mc_buffers[2] );
        glDrawElements( GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, 0 );
    }
    else
    {
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, mc_tab_vertices );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, mc_tab_colors );
        glDrawElements( GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, mc_tab_indices );
    }

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
}


GLfloat tfcc_tab_vertices[] =
{
    -sizex, -sizey,  sizez,
     sizex, -sizey,  sizez,
    -sizex,  sizey,  sizez,
     sizex,  sizey,  sizez,
    -sizex, -sizey, -sizez,
     sizex, -sizey, -sizez,
    -sizex,  sizey, -sizez,
     sizex,  sizey, -sizez,

     -sizex, -sizey,  sizez,
      sizex, -sizey,  sizez,
     -sizex,  sizey,  sizez,
      sizex,  sizey,  sizez,
     -sizex, -sizey, -sizez,
      sizex, -sizey, -sizez,
     -sizex,  sizey, -sizez,
      sizex,  sizey, -sizez
};

GLfloat tfcc_tab_colors[] =
{
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,
    1,0,0,

    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1,
    0,0,1
};

GLuint tfcc_tab1_indices[] =
{
    0,1,2,
    1,2,3,
    4,5,6,
    5,6,7,
};

GLuint tfcc_tab2_indices[] =
{
    12,9,13,11,15,10,14,8,12,9
};


void TwoColorCube::drawShape( const char* shader_name )
{
       // GLuint n = glGetUniformLocation( m_Framework->getCurrentShaderId(), "border" );
        //glUniform1f( n, m_Border );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, tfcc_tab_vertices );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, tfcc_tab_colors );
        glDrawElements( GL_TRIANGLES, 12, GL_UNSIGNED_INT, tfcc_tab1_indices );
        glDrawElements( GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, tfcc_tab2_indices );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
}


MultipleColorCube::MultipleColorCube() : ParametricShape( 24 )
{
    int i;
    int n;
    int face_id;
    int vertex_id;

    m_TabTexCoords = new GLfloat [24*2];

    for( i = 0; i < 24; ++i )
    {
        n = g_CubeFaces[i]*3;
        m_TabVertices[i*3+0] = mc_tab_vertices[n+0];
        m_TabVertices[i*3+1] = mc_tab_vertices[n+1];
        m_TabVertices[i*3+2] = mc_tab_vertices[n+2];

        vertex_id = i % 4;
        vertex_id *= 2;
        m_TabTexCoords[i*2+0] = g_TabTexCoords[vertex_id+0];
        m_TabTexCoords[i*2+1] = g_TabTexCoords[vertex_id+1];

        face_id = i/4;
        face_id *= 3;
        m_TabColors[i*3+0] = mc_tab_colors[face_id+0];
        m_TabColors[i*3+1] = mc_tab_colors[face_id+1];
        m_TabColors[i*3+2] = mc_tab_colors[face_id+2];
    }

    m_NbrIndices = 3*2*6;
    m_TabIndices = new GLuint [m_NbrIndices];

    int face;
    int shift;
    face_id = 0;
    for( i = 0; i < 12; ++i )
    {
        face = face_id/2;
        shift = face_id % 2;
        m_TabIndices[i*3+0] = face*4+shift+0;
        m_TabIndices[i*3+1] = face*4+shift+1;
        m_TabIndices[i*3+2] = face*4+shift+2;

        ++face_id;
    }

    m_Border = 0.0f;
}

MultipleColorCube::~MultipleColorCube()
{
    delete [] m_TabIndices;
    delete [] m_TabTexCoords;
}


void
MultipleColorCube::setBorder( GLfloat border )
{
    m_Border = border;
}


void
MultipleColorCube::setFaceColor( int face_id, GLfloat r, GLfloat g, GLfloat b )
{
    face_id *= 12;
    for( int i = 0; i < 12; i += 3 )
    {
        m_TabColors[face_id+i+0] = r;
        m_TabColors[face_id+i+1] = g;
        m_TabColors[face_id+i+2] = b;
    }
}


void
MultipleColorCube::initArrays()
{
    ParametricShape::initArrays();
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, m_TabTexCoords );
}


void
MultipleColorCube::drawShape( const char* shader_name )
{
    if (!strcmp( (char*) shader_name, "colorntex" ))
    {
        GLuint n = glGetUniformLocation( m_Framework->getCurrentShaderId(), "border" );
        glUniform1f( n, m_Border );
        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        glEnableVertexAttribArray( 2 );
        initArrays();
        //glDrawElements( GL_POINTS, m_NbrIndices, GL_UNSIGNED_INT, m_TabIndices );
        glDrawElements( GL_TRIANGLES, m_NbrIndices, GL_UNSIGNED_INT, m_TabIndices );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
        glDisableVertexAttribArray( 2 );
    }
    else
    {

        glEnableVertexAttribArray( 0 );
        glEnableVertexAttribArray( 1 );
        initArrays();
        //glDrawElements( GL_POINTS, m_NbrIndices, GL_UNSIGNED_INT, m_TabIndices );
        glDrawElements( GL_TRIANGLES, m_NbrIndices, GL_UNSIGNED_INT, m_TabIndices );
        glDisableVertexAttribArray( 0 );
        glDisableVertexAttribArray( 1 );
    }
}
