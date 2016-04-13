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

class CornerTableApplication 
{
public:
    
    virtual ~CornerTableApplication();
    
    static CornerTableApplication* getInstance();
    
    void generateRandomPoint();
    
private:
    
    CornerTableApplication();
    
    static CornerTableApplication* _instance;
    
    MainWindow* _window;
    
    CornerTable* _cornerTable;
    
};

#endif /* CORNERTABLEAPPLICATION_H */

