#pragma once;
#include"GL/glew.h"
#include <vector>
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include "GLM/gtc/quaternion.hpp"

// Remove the quotes from a string
void RemoveQuotes( std::string& str );

// Get's the size of the file in bytes.
int GetFileLength( std::istream& file );

// Ignore everything else that comes on the line, up to 'length' characters.
void IgnoreLine( std::istream& file, int length);

// Computes the W component of the quaternion based on the X, Y, and Z components.
// This method assumes the quaternion is of unit length.
void ComputeQuatW( glm::quat& quat);

glm::mat4 ComputeRightHandCoordinate(glm::mat4 matrix);


glm::vec4 ComputeRightHandCoordinateVector(glm::vec4 vector);

// Helper class to count frame time
class ElapsedTime
{
public:
    ElapsedTime( float maxTimeStep = 0.03333f );
    float GetElapsedTime() const;

private:
    float m_fMaxTimeStep;
    mutable float m_fPrevious;
};

