/* 
 * File:   CornerTableApplication.h
 * Author: allan
 *
 * Created on April 12, 2016, 11:48 PM
 */

#ifndef CORNERTABLEAPPLICATION_H
#define CORNERTABLEAPPLICATION_H

#include "MainWindow.h"
#include "CornerTable.h"
#include "MeshGeometry.h"
#include "WireframeGeometry.h"

class CornerTableApplication 
{
public:
    
    virtual ~CornerTableApplication();
    
    static CornerTableApplication* getInstance();
    
    bool openFile( std::string file );
    
    void generateRandomPoint();
    
private:
    
    CornerTableApplication();
    
    static osg::ref_ptr< osg::Geometry > createPointGeometry( double x, double y );
    
    std::list< int > calculateTrianglePathToPoint( double x, double y );
    
    static CornerTableApplication* _instance;
    
    MainWindow* _window;
    
    CornerTable* _cornerTable;
    
    osg::ref_ptr< osg::Geode > _scene;
    
    osg::ref_ptr< MeshGeometry > _meshGeometry;
    
    osg::ref_ptr< WireframeGeometry > _wireframeGeometry;
    
    osg::ref_ptr< osg::Geometry > _pointGeometry;
};

#endif /* CORNERTABLEAPPLICATION_H */

