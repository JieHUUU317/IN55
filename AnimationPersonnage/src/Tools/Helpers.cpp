#include "Helpers.h"
#include"boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "glm/gtc/matrix_access.hpp"
#include <iostream>

// Remove the quotes from a string
void RemoveQuotes( std::string& str )
{
    size_t n;
    while ( ( n = str.find('\"') ) != std::string::npos ) str.erase(n,1);
}

// Get's the size of the file in bytes.
int GetFileLength( std::istream& file )
{
    int pos = file.tellg();
    file.seekg(0, std::ios::end );
    int length = file.tellg();
    // Restore the position of the get pointer
    file.seekg(pos);

    return length;
}

glm::mat4 ComputeRightHandCoordinate(glm::mat4 matrix){
   /** glm::mat4 m = glm::mat4(matrix);
    glm::vec4 temp = glm::vec4(glm::column(m,1));
    glm::column(m,1,glm::column(m,2));
    glm::column(m,2,temp);
    temp = glm::vec4(glm::row(m,1));
    glm::row(m,1,glm::row(m,2));
    glm::row(m,2,temp);
    return m;
*/
    glm::mat4 t = glm::mat4(0.0);
    t[0][0]=1.0f; t[0][1] =0.0f; t[0][2]=0.0f; t[0][3]=0.0f;
    t[1][0]=0.0f; t[1][1] =0.0f; t[1][2]=-1.0f; t[1][3]=0.0f;
    t[2][0]=0.0f; t[2][1] =1.0f; t[2][2]=0.0f; t[2][3]=0.0f;
    t[3][0]=0.0f; t[3][1] =0.0f; t[3][2]=0.0f; t[3][3]=1.0f;
    return matrix*t;
}

glm::vec4 ComputeRightHandCoordinateVector(glm::vec4 vector){
   /** glm::mat4 m = glm::mat4(matrix);
    glm::vec4 temp = glm::vec4(glm::column(m,1));
    glm::column(m,1,glm::column(m,2));
    glm::column(m,2,temp);
    temp = glm::vec4(glm::row(m,1));
    glm::row(m,1,glm::row(m,2));
    glm::row(m,2,temp);
    return m;
*/
    glm::mat4 t = glm::mat4(0.0);
    t[0][0]=1.0f; t[0][1] =0.0f; t[0][2]=0.0f; t[0][3]=0.0f;
    t[1][0]=0.0f; t[1][1] =0.0f; t[1][2]=-1.0f; t[1][3]=0.0f;
    t[2][0]=0.0f; t[2][1] =1.0f; t[2][2]=0.0f; t[2][3]=0.0f;
    t[3][0]=0.0f; t[3][1] =0.0f; t[3][2]=0.0f; t[3][3]=1.0f;
    return t*vector;
}
void IgnoreLine( std::istream& file, int length )
{
    file.ignore( length, '\n' );
}

// Computes the W component of the quaternion based on the X, Y, and Z components.
// This method assumes the quaternion is of unit length.
void ComputeQuatW( glm::quat& quat )
{
    float t = 1.0f - ( quat.x * quat.x ) - ( quat.y * quat.y ) - ( quat.z * quat.z );
    if ( t < 0.0f )
    {
        quat.w = 0.0f;
    }
    else
    {
        quat.w = -sqrtf(t);
    }
}

ElapsedTime::ElapsedTime( float maxTimeStep /* = 0.01f */ )
: m_fMaxTimeStep( maxTimeStep )
, m_fPrevious ( std::clock() / (float)CLOCKS_PER_SEC )
{}

float ElapsedTime::GetElapsedTime() const
{
    float fCurrentTime = std::clock() / (float)CLOCKS_PER_SEC;
    float fDeltaTime = fCurrentTime - m_fPrevious;
    m_fPrevious = fCurrentTime;

    // Clamp to the max time step
    fDeltaTime = std::min( fDeltaTime, m_fMaxTimeStep );

    return fDeltaTime;
}

