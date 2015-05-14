#ifndef BASISPLAN
#define BASISPLAN
#include "Shapes/ParametricShape.h"
#include "Object3D.h"

class BasisPlan : public Object3D
{
public:
    BasisPlan();

protected:
    void drawShape(const char* shader_name);


protected:
    GLuint* m_TabIeIndices;
    GLfloat* m_TableColors;
    GLfloat* m_TabVertices;

};

#endif // BASISPLAN
