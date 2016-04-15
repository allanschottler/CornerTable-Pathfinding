/* 
 * File:   MeshGeometry.h
 * Author: allan
 *
 * Created on April 13, 2016, 12:30 AM
 */

#ifndef MESHGEOMETRY_H
#define MESHGEOMETRY_H

#include <osg/Geometry>

#include "CornerTable.h"

class MeshGeometry : public osg::Geometry
{
public:
    
    MeshGeometry( CornerTable* cornerTable );
    
    virtual ~MeshGeometry();
    
    void highlightTriangles( std::list< int > triangles );
    
private:
    
    void buildGeometry();
    
    CornerTable* _cornerTable;
    
    std::list< int > _highlightedTriangles;
};

#endif /* MESHGEOMETRY_H */

