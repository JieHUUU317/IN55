﻿#include "Object3D.h"


AbstractFramework* Object3D::m_Framework = NULL;


void
Object3D::setFramework( AbstractFramework* fw )
{
	m_Framework = fw;
}


void
Object3D::draw()
{
    if (m_Framework->useShader( "color" ))
    {
        m_Framework->computeAncillaryMatricesRight();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        drawShape( "color" );
    }
    if (m_Framework->useShader( "PerVertexPointSize" ))
    {
        m_Framework->computeAncillaryMatricesRight();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        drawShape( "PerVertexPointSize" );
    }
    if (m_Framework->useShader( "Morphing" ))
    {
        m_Framework->computeAncillaryMatricesRight();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        drawShape( "Morphing" );
    }
}


void
Object3D::draw( const char* shader_name )
{
    if (m_Framework->useShader( shader_name ))
    {
        m_Framework->computeAncillaryMatricesRight();
        GLint var_id = glGetUniformLocation( m_Framework->getCurrentShaderId(), "MVP" );
        m_Framework->transmitMVP( var_id );

        drawShape( shader_name );
    }
}
