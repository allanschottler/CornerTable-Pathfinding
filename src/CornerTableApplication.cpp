/* 
 * File:   CornerTableApplication.cpp
 * Author: allan
 * 
 * Created on April 12, 2016, 11:48 PM
 */

#include "CornerTableApplication.h"
#include "MeshLoader.h"
#include "MeshGeometry.h"

#include <osg/Geode>

CornerTableApplication* CornerTableApplication::_instance = 0;

CornerTableApplication::CornerTableApplication() :
    _window( new MainWindow() )
{
    srand( time( NULL ) );
    
    _cornerTable = MeshLoader().parse( "mesh10.mesh" );
    
    osg::ref_ptr< MeshGeometry > meshGeometry = new MeshGeometry( _cornerTable );        
    osg::ref_ptr< osg::Geode > scene = new osg::Geode;    
    scene->addDrawable( meshGeometry );
    
    osg::ref_ptr< osgGA::TrackballManipulator > manipulator = new osgGA::TrackballManipulator();
    
    /*osg::Vec3d eye, center, up, newEye( 0.0f, 0.0f, 1.0f );
    manipulator->getHomePosition( eye, center, up );    
    manipulator->setHomePosition( newEye, center, up );*/
    
    _window->getCanvas().setCameraManipulator( manipulator );
    //_window->getCanvas().getCamera()->setClearColor( osg::Vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
    _window->getCanvas().setSceneData( scene );
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