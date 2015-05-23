#ifndef MD5MODEL
#define MD5MODEL
#include "GLM/fwd.hpp"
#include "GLM/glm.hpp"
#include "src/Shapes/Object3D.h"
#include <glm/gtc/type_ptr.hpp>
#include"include/GL/glew.h"
#include "MD5Animation.h"
#include<src/Framework/AbstractFramework.h>
#include"GL/glew.h"
#include <vector>
#include <string>
class MD5Model:public Object3D
{
public:
    MD5Model();
    //virtual ~MD5Model()
    static void setFramework( AbstractFramework* );
    bool LoadModel( const std::string & filename );
    bool LoadAnim( const std::string& filename );
    void Update( GLfloat fDeltaTime );
    void Render();
     void drawShape( const char* shader_name );
protected:

    typedef std::vector<glm::vec3> PositionBuffer;
    typedef std::vector<glm::vec3> NormalBuffer;
    typedef std::vector<glm::vec2> Tex2DBuffer;
    typedef std::vector<GLuint> IndexBuffer;

    static AbstractFramework* m_Framework;
    //To store the data of vertex in the MD5 mesh file
    struct Vertex
    {
        glm::vec3   m_Pos;
        glm::vec3   m_Normal;
        glm::vec2   m_Tex0;                 //define the texture coordinates of the vertex
        int         m_StartWeight;         //start index of weight
        int         m_WeightCount;       //number of weights associated with this vertex
    };
    typedef std::vector<Vertex> VertexList;

    //To store the data of triangle (3 vertex) in the MD5 mesh file
    struct Triangle
    {
        int             m_Indices[3];
    };
    typedef std::vector<Triangle> TriangleList;

    //To store the data of the weight
    struct Weight
    {
        int             m_JointID; //index of joint
        float           m_Bias;     //ratio that determines how much of the
                                             //joint's orientation and position is applied to the final position
        glm::vec3       m_Pos;
    };
    typedef std::vector<Weight> WeightList;

    struct Joint
    {
        std::string     m_Name;
        int             m_ParentID;
        glm::vec3       m_Pos;
        glm::quat       m_Orient;
    };
    typedef std::vector<Joint> JointList;

    struct Mesh
    {
        std::string     m_Shader;
        // This vertex list stores the vertices in the bind pose.
        VertexList      m_Verts;
        TriangleList    m_Tris;
        WeightList      m_Weights;

        // A texture ID for the material
        GLuint          m_TexID;

        // These buffers are used for rendering the animated mesh
        PositionBuffer  m_PositionBuffer;   // Vertex position stream
        NormalBuffer    m_NormalBuffer;     // Vertex normals stream
        Tex2DBuffer     m_Tex2DBuffer;      // Texture coordinate set
        IndexBuffer     m_IndexBuffer;      // Vertex index buffer
    };
    typedef std::vector<Mesh> MeshList;

    // Prepare the mesh for rendering
    // Compute vertex positions and normals
    bool PrepareMesh( Mesh& mesh );
    bool PrepareMesh( Mesh& mesh, const MD5Animation::FrameSkeleton& skel );
    bool PrepareNormals( Mesh& mesh );

    // Render a single mesh of the model
    void RenderMesh( const Mesh& mesh );
    void RenderNormals( const Mesh& mesh );

    // Draw the skeleton of the mesh for debugging purposes.
    void RenderSkeleton( const JointList& joints );

    bool CheckAnimation( const MD5Animation& animation ) const;
private:

    int                 m_iMD5Version;
    int                 m_iNumJoints;
    int                 m_iNumMeshes;

    bool                m_bHasAnimation;

    JointList           m_Joints;
    MeshList            m_Meshes;

    MD5Animation        m_Animation;

    glm::mat4        m_LocalToWorldMatrix;

};

#endif // MD5MODEL

