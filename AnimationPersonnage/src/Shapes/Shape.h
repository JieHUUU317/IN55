#ifndef Shape_h
#define Shape_h
#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glew.h>
#define QT_NO_OPENGL_ES_2


#include "Object3D.h"
#include "Types.h"
class Shape : public Object3D
{
    public:
		Shape();
		virtual ~Shape();

		void clear();

        uint32 getNbrVertices() const;
		const GLfloat* vertices() const;
		const GLfloat* normals() const;
		const GLfloat* textureCoordinates() const;

		uint32 getNbrIndices() const;
		const GLuint* indices() const;


    protected:
		bool m_DynamicVertices;
		uint32 m_NbrVertices;
		GLfloat* m_TabVertices;
		GLfloat* m_TabNormals;
		GLfloat* m_TabTexCoords;
		bool m_DynamicIndices;
		uint32 m_NbrIndices;
		GLuint* m_TabIndices;
};


#endif
