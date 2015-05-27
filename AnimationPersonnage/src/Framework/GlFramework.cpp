#define _USE_MATH_DEFINES
#include <cmath>
#include "GlFramework.h"
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/matrix_inverse.hpp>
#include "src/Shapes/Object3D.h"
#include "src/Model/MD5Model.h"
#include "src/Tools/Helpers.h"
#include "GlCamera.h"
#include <QMessageBox>
#include <QDebug>
#include <QGLWidget>
#include "LF_String.h"
#include <limits>
#include <iostream>

GlFramework::GlFramework()
{
    pViewMatrix = glm::mat4(1.0);
    loadIdentity();

    m_CurrentShader = -1;
}

GlFramework::~GlFramework()
{
    for( GLuint i = 0; i < m_Shader.size(); ++i )
    {
        glDeleteProgram( m_Shader[i] );
    }
}


bool
GlFramework::init()
{
    std::cout << "Init GLEW" << std::endl;

    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if(error != GLEW_OK)
    {
        return false;
//QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec de l'initialization de GLEW: %1").arg(reinterpret_cast<const char *>(glewGetErrorString(error))));
        exit(-1);
    }
    Object3D::setFramework( this );
    MD5Model::setFramework(this);
}


char*
GlFramework::loadShader( const char* file_name )
{
    FILE* fp;
    char* content = NULL;
    long length;

    fp = fopen( file_name, "rb" );
    if (fp)
    {
        fseek( fp, 0, SEEK_END );
        length = ftell( fp );
        fseek( fp, 0, SEEK_SET );
        content = new char [length+1];
        fread( content, sizeof( char ), length, fp );
        fclose( fp );
        content[length] = '\0';
    }

    return content;
}

GLint
GlFramework::createShader( const char* shader_prefix )
{
    char shader_name[128];

    sprintf( shader_name, "%s.vs", shader_prefix );
    const GLchar* vs_content = loadShader( shader_name );

    sprintf( shader_name, "%s.fs", shader_prefix );
    const GLchar* fs_content = loadShader( shader_name );

    if (vs_content == NULL)
    {
        return -1;
//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec du chargement d'un shader\n"));
    }

    GLint status, logSize;
    QByteArray log;
    GLuint pProgram;

    pProgram = glCreateProgram();

    GLuint vshader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vshader, 1, &vs_content, NULL);
    glCompileShader(vshader);
    glGetShaderiv(vshader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetShaderiv(vshader, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetShaderInfoLog(vshader, logSize, &logSize, log.data());

        std::cout << "Error: " << QString(log).toStdString().c_str() << std::endl;

        return -1;
//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec de la compilation du vertex shader:\n\n%1").arg(QString(log)));
//        exit(-1);
    }
    glAttachShader(pProgram, vshader);

    GLuint fshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fshader, 1, &fs_content, NULL);
    glCompileShader(fshader);
    if(status != GL_TRUE)
    {
        glGetShaderiv(fshader, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetShaderInfoLog(fshader, logSize, &logSize, log.data());

        std::cout << "Error: " << QString(log).toStdString().c_str() << std::endl;

		return -1;
//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec de la compilation du fragment shader:\n\n%1").arg(QString(log)));
//        exit(-1);
    }
    glAttachShader(pProgram, fshader);

    glLinkProgram(pProgram);
    glGetProgramiv(pProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        glGetProgramiv(pProgram, GL_INFO_LOG_LENGTH, &logSize);
        log.resize(logSize - 1);
        glGetProgramInfoLog(pProgram, logSize, &logSize, log.data());

        std::cout << "Error: " << QString(log).toStdString().c_str() << std::endl;

		return -1;

//        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Echec du linkage du programme:\n\n%1").arg(QString(log)));
//        exit(-1);
    }

    delete [] vs_content;
    delete [] fs_content;

    m_ShaderNames.push_back( shader_prefix );
    m_Shader.push_back( pProgram );

    return m_Shader.size()-1;
}


bool
GlFramework::useShader( GLint shader_id )
{
    if (shader_id < m_Shader.size())
    {
        if (m_CurrentShader != shader_id)
        {
//            std::cout << "Use shader: " << shader_id << std::endl;
            m_CurrentShader = shader_id;
            glUseProgram( m_Shader[shader_id] );
        }

        return true;
    }
    else
    {
        m_CurrentShader = -1;
        glUseProgram( 0 );

        return false;
    }
}

bool
GlFramework::useShader( const char* shader_name )
{
    for( GLuint id = 0; id < m_ShaderNames.size(); ++id )
    {
        if (strstr( m_ShaderNames[id].c_str(), shader_name ))
        {
            if (m_CurrentShader != id)
            {
//                std::cout << "Use shader: " << id << std::endl;
                m_CurrentShader = id;
                glUseProgram( m_Shader[id] );
            }

            return true;
        }
    }

    m_CurrentShader = -1;
    glUseProgram( 0 );
    return false;
}

GLint
GlFramework::getCurrentShaderId() const
{
    return m_Shader[m_CurrentShader];
}

void
GlFramework::transmitMVP( GLuint var_id )
{
    glUniformMatrix4fv( var_id, 1, GL_FALSE, glm::value_ptr(pMVPMatrix));
}

void
GlFramework::transmitMV( GLuint var_id )
{
    glUniformMatrix4fv( var_id, 1, GL_FALSE, glm::value_ptr(pModelViewMatrix));
}

void
GlFramework::transmitNM( GLuint var_id )
{
    glUniformMatrix3fv( var_id, 1, GL_FALSE,glm::value_ptr(pNormalMatrix));
}

void
GlFramework::transmitM( GLuint var_id )
{
    glUniformMatrix4fv( var_id, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
}

void
GlFramework::transmitV( GLuint var_id )
{
    glUniformMatrix4fv( var_id, 1, GL_FALSE,glm::value_ptr(pViewMatrix));
}

void
GlFramework::transmitP( GLuint var_id )
{
   glUniformMatrix4fv( var_id, 1, GL_FALSE, glm::value_ptr(pProjMatrix));
}

void
GlFramework::setPerspective(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar)
{
    pProjMatrix = glm::perspective(fovY,ratio,zNear,zFar);
}

void
GlFramework::setOrtho(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar)
{
}

void
GlFramework::setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    pViewMatrix = glm::lookAt(eye,center,up);
}

void
GlFramework::pushMatrix()
{
    pMatrixStack.append(pModelMatrix);
}

void
GlFramework::popMatrix()
{
    pModelMatrix = pMatrixStack.takeLast();
}

void
GlFramework::loadIdentity()
{
    pModelMatrix = glm::mat4(1.0);
}

void
GlFramework::translateFramework(GLfloat x, GLfloat y, GLfloat z)
{
    pModelMatrix = glm::translate(pModelMatrix, glm::vec3(x, y, z));
}

void
GlFramework::rotateFramework(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    pModelMatrix = glm::rotate(pModelMatrix, angle, glm::vec3(x,y,z));
}

void
GlFramework::scaleFramework(GLfloat x, GLfloat y, GLfloat z)
{
    pModelMatrix = glm::scale(pModelMatrix, glm::vec3(x,y,z));
}


void
GlFramework::computeAncillaryMatrices()
{
    pModelViewMatrix = (pViewMatrix * pModelMatrix);
    pNormalMatrix =(glm::affineInverse( pModelViewMatrix ));
    pMVPMatrix =(pProjMatrix * pModelViewMatrix);
}

void
GlFramework::computeAncillaryMatricesRight()
{
    pModelViewMatrix = (pViewMatrix * (ComputeRightHandCoordinate(pModelMatrix)));
    pNormalMatrix =(glm::affineInverse( pModelViewMatrix ));
    pMVPMatrix =(pProjMatrix * pModelViewMatrix);
}


char* cubemaps[] =
{
  "_pX",
  "_nX",
  "_pY",
  "_nY",
  "_pZ",
  "_nZ"
};


GLuint
GlFramework::createTexture( const char* filename )
{
    GLuint texId = 0;
    QImage image;

    if (strstr( filename, "cubemap_" ))
    {
        lf::String name;

        glGenTextures( 1, &texId );
        std::cout << "Texture #" << texId << ": " << filename << " loaded!" <<std::endl;

//		glEnable( GL_TEXTURE_CUBE_MAP );
        glBindTexture( GL_TEXTURE_CUBE_MAP, texId );
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP);

        for( int i = 0; i < 6; ++i )
        {
            name = filename;
            name += cubemaps[i];

            if (image.load( name.c_str() ))
            {
                std::cout << name.c_str() << " (" << image.width() << "," << image.height() << ") loaded!" << std::endl;

                image = QGLWidget::convertToGLFormat( image );
                glTexImage2D( GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
            }
        }
    }
    else if (strstr( filename, "tex2d_" ))
    {
        if (image.load( filename ))
        {
            image = QGLWidget::convertToGLFormat( image );

            glGenTextures( 1, &texId );
            std::cout << "Texture #" << texId << ": " << filename << " (" << image.width() << "," << image.height() << ") loaded!" << std::endl;

//			glEnable( GL_TEXTURE_2D );
            glBindTexture( GL_TEXTURE_2D, texId );
            glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
    }
    else if (strstr( filename, "tex1d_" ))
    {
        if (image.load( filename ))
        {
            image = QGLWidget::convertToGLFormat( image );

            glGenTextures( 1, &texId );
            std::cout << "Texture #" << texId << ": " << filename << " (" << image.width() << "," << image.height() << ") loaded!" << std::endl;

//			glDisable( GL_TEXTURE_CUBE_MAP );
//			glEnable( GL_TEXTURE_1D );
            glBindTexture( GL_TEXTURE_1D, texId );
            glTexImage1D( GL_TEXTURE_1D, 0, GL_RGBA, image.width(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits() );
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP );
        }
    }

    return texId;
}
