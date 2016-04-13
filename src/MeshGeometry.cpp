/* 
 * File:   MeshGeometry.cpp
 * Author: allan
 * 
 * Created on April 13, 2016, 12:30 AM
 */

#include "MeshGeometry.h"

MeshGeometry::MeshGeometry( CornerTable* cornerTable ) :
    _cornerTable( cornerTable )
{
    buildGeometry();
}

MeshGeometry::~MeshGeometry() 
{
}

void MeshGeometry::buildGeometry()
{
    int nTriangles = _cornerTable->getNumTriangles();
    const int* triangles = _cornerTable->getTriangleList();
    int nVertices = _cornerTable->getNumberVertices();
    double* vertices = _cornerTable->getAttributes();
    
    osg::ref_ptr< osg::Vec3Array > vertexArray = new osg::Vec3Array;
    osg::ref_ptr< osg::Vec4Array > colorArray = new osg::Vec4Array;
    
    for( int iVertex = 0; iVertex < nVertices; iVertex++ )
        vertexArray->push_back( osg::Vec3f( (double)vertices[ 3 * iVertex ],
                                           (double)vertices[ 3 * iVertex + 1 ], 
                                           (double)vertices[ 3 * iVertex + 2 ] ) );
    
    for( int iTriangle = 0; iTriangle < nTriangles; iTriangle++ )
    {
        osg::ref_ptr< osg::DrawElementsUInt > indexArray = new osg::DrawElementsUInt( osg::PrimitiveSet::LINE_LOOP, 0 );
        
        indexArray->push_back( triangles[ 3 * iTriangle ] );
        indexArray->push_back( triangles[ 3 * iTriangle+1 ] );
        indexArray->push_back( triangles[ 3 * iTriangle+2 ] );  
        
        addPrimitiveSet( indexArray );
        
        colorArray->push_back( osg::Vec4( 0.0f, 0.0f, 1.0f, 1.0f ) );
    }
    
    setVertexArray( vertexArray );
    setColorArray( colorArray );
    setColorBinding( BIND_PER_PRIMITIVE_SET );
}