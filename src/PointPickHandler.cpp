/* 
 * File:   PointPickHandler.cpp
 * Author: allanws
 * 
 * Created on April 19, 2016, 2:13 PM
 */

#include "PointPickHandler.h"
#include "CornerTableApplication.h"
#include <osgViewer/Viewer>
#include <iostream>

PointPickHandler::PointPickHandler() 
{
}


PointPickHandler::~PointPickHandler() 
{
}


bool PointPickHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
{
    osgViewer::Viewer* viewer = dynamic_cast< osgViewer::Viewer* >( &aa );
    
    if( !viewer )
        return false;
        
    switch( ea.getEventType() )
    {
        case osgGA::GUIEventAdapter::PUSH:
        {            
            switch( ea.getButton() )
            {
                case osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON:
                {
                    osg::ref_ptr< osgUtil::LineSegmentIntersector > ray = 
                            new osgUtil::LineSegmentIntersector( osgUtil::Intersector::PROJECTION, ea.getXnormalized(), ea.getYnormalized() );
                    osgUtil::IntersectionVisitor visitor( ray );

                    viewer->getCamera()->accept( visitor );

                    if( ray->containsIntersections() )
                    {
                        IntersectionSelector selector;
                        Intersection intersection = ray->getFirstIntersection();

                        if( selector.handle( intersection ) )
                            return true;
                    }
                }

                default:
                    return false;
            }

        }
        
        default:
            return false;
    }
}


bool IntersectionSelector::handle( Intersection &intersection )
{
   osg::NodePath &nodes = intersection.nodePath;

    for( int i = nodes.size() - 1; i >= 0; i-- )
    {
        osg::Geode* meshGeode = dynamic_cast< osg::Geode* >( nodes[ i ] );

        if( meshGeode )
        {
            const osg::Vec3 &p = intersection.getLocalIntersectPoint();
            
            CornerTableApplication::getInstance()->pickPoint( p[0], p[1] );
            
            return true;
        }
    }

    return false;
}