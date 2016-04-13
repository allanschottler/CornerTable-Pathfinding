/* 
 * File:   MainWindow.h
 * Author: allan
 *
 * Created on April 12, 2016, 11:49 PM
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*#include <gtk/gtk.h>
#include <gtk/gtkgl.h>*/
#include <gtk/gtk.h>
#include "osggtkdrawingarea.h"

class MainWindow 
{
public:
    
    MainWindow();
    
    virtual ~MainWindow();
    
    void show();
    
    OSGGTKDrawingArea& getCanvas();
    
private:
    
    //CALLBACKS
    static gboolean onDestroy();
    static gboolean onIdle( gpointer pointer );
    
    OSGGTKDrawingArea _canvas;
    
    GtkWidget* _dialog;
    GtkWidget* _randomButton;

};

#endif /* MAINWINDOW_H */

