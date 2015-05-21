#ifndef GlFramework_h
#define GlFramework_h

#include "AbstractFramework.h"
#include "GlCamera.h"
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include <QLinkedList>
#include <QImage>
#include <vector>
#include "LF_String.h"

class GlFramework : public AbstractFramework
{
    public:
        GlFramework();
        ~GlFramework();

		ABSTRACT_FRAMEWORK_INTERFACE

        /*!
        *\brief Fonction de création d'un shader.
        */
        GLint createShader( const char* shader_prefix );

        void setPerspective(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar);

        void setOrtho(GLfloat fovY, GLfloat ratio, GLfloat zNear, GLfloat zFar);

        void setLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up = glm::vec3(0.0,1.0,0.0));

    protected:
		/*!
		*\brief Fonction de chargement d'un shader.
		*/
		char* loadShader( const char* file_name );

		/*!
        *\brief Fonction d'initialization d'OpenGL, appelée à la création du
        *contexte de rendu.
        */
        bool init();


	protected:
        glm::mat4 pProjMatrix, pViewMatrix, pModelMatrix;
        glm::mat4 pModelViewMatrix, pNormalMatrix, pMVPMatrix;
        QLinkedList<glm::mat4> pMatrixStack;
		std::vector<std::string> m_ShaderNames;
		std::vector<GLint> m_Shader;
		GLint m_CurrentShader;
};


#endif
