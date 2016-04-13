/* 
 * File:   MeshLoader.h
 * Author: allan
 *
 * Created on April 11, 2016, 10:36 PM
 */

#ifndef MESHLOADER_H
#define MESHLOADER_H

#include "CornerTable.h"
#include <string>

class MeshLoader 
{    
public:
    
    MeshLoader();
    
    virtual ~MeshLoader() {};
    
    //CornerTable* load( std::string file );
    
    CornerTable*  parse(std::string filename);
    
private:
    
    std::string _currentPath;

};

#endif /* MESHLOADER_H */

