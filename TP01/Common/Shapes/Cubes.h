#ifndef Shapes_h
#define Shapes_h


#include "Shapes/ParametricShape.h"


class MulticolorCube : public Shape
{
    public:
        MulticolorCube();

        void initVBO();

    protected:
        void drawShape( const char* shader_name );


    protected:
        bool m_VBO;
};


class TwoColorCube : public Shape
{
    protected:
        void drawShape( const char* shader_name );
};


class MultipleColorCube : public ParametricShape
{
    public:
        MultipleColorCube();
        ~MultipleColorCube();

        void setBorder( GLfloat );
        void setFaceColor( int face_id, GLfloat r, GLfloat g, GLfloat b );

        void initArrays();

    protected:
        void drawShape( const char* shader_name );

    protected:
        int m_NbrIndices;
        GLuint* m_TabIndices;
        GLfloat* m_TabTexCoords;
        GLfloat m_Border;
};



#endif
