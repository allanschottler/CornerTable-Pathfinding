/* 
 * File:   WireframeGeometry.h
 * Author: allan
 *
 * Created on April 15, 2016, 5:06 PM
 */

#ifndef WIREFRAMEGEOMETRY_H
#define WIREFRAMEGEOMETRY_H

#include <osg/Geometry>

class CornerTable;

class WireframeGeometry : public osg::Geometry
{
public:
    
    WireframeGeometry( CornerTable* cornerTable );
    
    virtual ~WireframeGeometry();
    
private:
    
    void buildGeometry();
    
    CornerTable* _cornerTable;
};

#endif /* WIREFRAMEGEOMETRY_H */

