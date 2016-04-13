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

#include <osg/Geode>
#include <osg/LineWidth>
#include <osg/Point>
#include <fstream>
#include <iostream>

CornerTableApplication* CornerTableApplication::_instance = 0;

CornerTableApplication::CornerTableApplication() :
    _window( new MainWindow() ),
    _cornerTable( nullptr )
{
    srand( time( NULL ) );    
            
    _scene = new osg::Geode; 
    
    osg::ref_ptr< osg::LineWidth > linewidth = new osg::LineWidth();
    linewidth->setWidth( 2.0f );
    _scene->getOrCreateStateSet()->setAttributeAndModes( linewidth, osg::StateAttribute::ON ); 
    
    osg::ref_ptr< osg::Point > point = new osg::Point;
    point->setSize( 2.0f );    
    _scene->getOrCreateStateSet()->setAttribute( point, osg::StateAttribute::ON );
    
    osg::ref_ptr< osgGA::TrackballManipulator > manipulator = new osgGA::TrackballManipulator();
    
    osg::Vec3d eye, center, up, newEye( 0.0f, 5.0f, 5.0f );
    manipulator->getHomePosition( eye, center, up );    
    manipulator->setHomePosition( newEye, center, up );    

    _window->getCanvas().setCameraManipulator( manipulator );
    //_window->getCanvas().getCamera()->setClearColor( osg::Vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
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


void CornerTableApplication::openFile( std::string file )
{
    _scene->removeDrawables( 0, _scene->getNumDrawables() );
    
    _cornerTable = MeshLoader().parse( file );
    
    if( !_cornerTable )
        return;
    
    osg::ref_ptr< MeshGeometry > meshGeometry = new MeshGeometry( _cornerTable );   
    _scene->addDrawable( meshGeometry );    
}


void CornerTableApplication::generateRandomPoint()
{
    double x, y;
    PointGenerator().generate( x, y );
    
    _window->clearMessages();
    
    std::string msg( "(" + std::to_string( x ) + ", " + std::to_string( y ) + ")" );    
    _window->printMessage( msg );
}