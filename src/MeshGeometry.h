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
    
private:
    
    void buildGeometry();
    
    CornerTable* _cornerTable;
};

#endif /* MESHGEOMETRY_H */

