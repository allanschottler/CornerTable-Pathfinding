/* 
 * File:   CornerTableApplication.cpp
 * Author: allan
 * 
 * Created on April 12, 2016, 11:48 PM
 */

#include "CornerTableApplication.h"
#include "MeshLoader.h"
#include "MeshGeometry.h"
#include "PointGenerator.h"
#include "WireframeGeometry.h"

#include <osg/Geode>
#include <osg/LineWidth>
#include <osg/Point>
#include <fstream>
#include <iostream>
#include <assert.h>

CornerTableApplication* CornerTableApplication::_instance = 0;

CornerTableApplication::CornerTableApplication() :
    _window( new MainWindow( "[FCG] Trabalho 2" ) ),
    _cornerTable( nullptr )
{
    srand( time( NULL ) );    
            
    _scene = new osg::Geode; 
    
    osg::ref_ptr< osg::LineWidth > linewidth = new osg::LineWidth();
    linewidth->setWidth( 2.0f );
    _scene->getOrCreateStateSet()->setAttributeAndModes( linewidth, osg::StateAttribute::ON ); 
    
    osg::ref_ptr< osg::Point > point = new osg::Point;
    point->setSize( 9.0f );    
    _scene->getOrCreateStateSet()->setAttribute( point, osg::StateAttribute::ON );
    
    _scene->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    
    osg::ref_ptr< osgGA::TrackballManipulator > manipulator = new osgGA::TrackballManipulator();
    
    osg::Vec3d eye, center, up, newEye( 0.0f, 5.0f, 5.0f );
    manipulator->getHomePosition( eye, center, up );    
    manipulator->setHomePosition( newEye, center, up );    

    _window->getCanvas().setCameraManipulator( manipulator );
    _window->getCanvas().setSceneData( _scene );
    _window->show();
}


CornerTableApplication::~CornerTableApplication()
{
    delete _cornerTable;
    delete _instance;    
    _instance = 0;
}


CornerTableApplication* CornerTableApplication::getInstance()
{
    if( !_instance )
        _instance = new CornerTableApplication();
    
    return _instance;
}


bool CornerTableApplication::openFile( std::string file )
{
    _scene->removeDrawables( 0, _scene->getNumDrawables() );
    
    _cornerTable = MeshLoader().parse( file );
    
    if( !_cornerTable )
        return false;
    
    _meshGeometry = new MeshGeometry( _cornerTable );   
    _wireframeGeometry = new WireframeGeometry( _cornerTable );
    
    _scene->addDrawable( _meshGeometry );   
    _scene->addDrawable( _wireframeGeometry );   
    
    _window->clearMessages();
    
    return true;
}


void CornerTableApplication::generateRandomPoint()
{
    if( !_cornerTable )
        return;    
    
    _window->clearMessages();
    _scene->removeDrawable( _pointGeometry );
    
    double x, y;
    PointGenerator().generate( x, y );    
    
    std::string msg( "(" + std::to_string( x ) + ", " + std::to_string( y ) + ")" );   
    
    _window->printMessage( msg );
    
    osg::BoundingBox bb = _meshGeometry->getBound();
    x = ( ( ( x - (-1) ) * ( bb._max.x() - bb._min.x() ) ) / ( 1 - (-1) ) ) + bb._min.x();
    y = ( ( ( y - (-1) ) * ( bb._max.y() - bb._min.y() ) ) / ( 1 - (-1) ) ) + bb._min.y();
    
    /*msg =  "(" + std::to_string( x ) + ", " + std::to_string( y ) + ")";
     
    _window->printMessage( msg );*/
    
    _pointGeometry = createPointGeometry( x, y );
    _scene->addDrawable( _pointGeometry );
    
    std::list< int > trianglePath = calculateTrianglePathToPoint( x, y );
    _meshGeometry->highlightTriangles( trianglePath );
    
    for( auto& triangle : trianglePath )
        _window->printMessage( std::string( std::to_string( triangle ) ) );
}


osg::ref_ptr< osg::Geometry > CornerTableApplication::createPointGeometry( double x, double y )
{
    osg::ref_ptr< osg::Geometry > point = new osg::Geometry;
    
    osg::ref_ptr< osg::Vec3Array > vertexArray = new osg::Vec3Array;
    osg::ref_ptr< osg::Vec4Array > colorArray = new osg::Vec4Array;;
    osg::ref_ptr< osg::DrawElementsUInt > primitive = new osg::DrawElementsUInt( osg::PrimitiveSet::POINTS, 0 );
    
    vertexArray->push_back( osg::Vec3( x, y, 0. ) );
    colorArray->push_back( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );    
    primitive->push_back( 0 );
    
    point->setVertexArray( vertexArray );
    point->setColorArray( colorArray );
    point->setColorBinding( osg::Geometry::BIND_OVERALL );
    point->addPrimitiveSet( primitive );
    
    return point;
}

std::list< int > CornerTableApplication::calculateTrianglePathToPoint( double x, double y )
{
    std::list< int > triangles;
    int currentCorner = 0;
    double point[3];
    
    point[0] = x;
    point[1] = y;
    point[2] = 0.;
    
    while( currentCorner != CornerTable::BORDER_CORNER )
    {
        int i;

        for( i = 0; i < 3; i++ )
        {        
            int pos = _cornerTable->edgeOriented( currentCorner, point );

            if( pos == 0 )
            {
                triangles.push_back( _cornerTable->cornerTriangle( currentCorner ) );
                return triangles;
            }

            if( pos == 1 )
            {
                triangles.push_back( _cornerTable->cornerTriangle( currentCorner ) );
                int opposite = _cornerTable->cornerOpposite( currentCorner );
                
                if( opposite == CornerTable::BORDER_CORNER )
                    return triangles;
                
                currentCorner = _cornerTable->cornerNext( opposite );
                break;
            }

            if( pos == -1 )
                currentCorner = _cornerTable->cornerNext( currentCorner );
        }

        if( i == 3 )
        {
            triangles.push_back( _cornerTable->cornerTriangle( currentCorner ) );
            return triangles;
        }
    }
    
    return triangles;
}