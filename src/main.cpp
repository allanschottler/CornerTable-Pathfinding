#include <iostream>

#include <ctime>

#include "MeshLoader.h"
#include "CornerTableApplication.h"

int main( int argc, char** argv )
{
    gtk_init( &argc, &argv );
    gtk_gl_init( &argc, &argv );
    
    CornerTableApplication* application = CornerTableApplication::getInstance();
    
    gtk_main();    
    return 0;
}