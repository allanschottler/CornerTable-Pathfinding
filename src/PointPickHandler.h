/* 
 * File:   PointPickHandler.h
 * Author: allanws
 *
 * Created on April 19, 2016, 2:13 PM
 */

#ifndef POINTPICKHANDLER_H
#define	POINTPICKHANDLER_H

#include "MeshGeometry.h"
#include <osgUtil/LineSegmentIntersector>
#include <osgGA/GUIEventHandler>

typedef osgUtil::LineSegmentIntersector::Intersection Intersection;
 
class IntersectionSelector
{
public:
    
    virtual bool handle( Intersection &intersection );
};


class PointPickHandler : public osgGA::GUIEventHandler
{
public:
    
    PointPickHandler();
    
    virtual ~PointPickHandler();
    
    bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
    
private:
    
    IntersectionSelector _selector;

};

#endif	/* POINTPICKHANDLER_H */

