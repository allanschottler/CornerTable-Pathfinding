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
    
    void printMessage( std::string message );
    
    void clearMessages();
    
private:
    
    //CALLBACKS
    static gboolean onDestroy();
    static gboolean onIdle( gpointer pointer );
    static gboolean onRandomButtonClicked( GtkWidget* button, gpointer* pointer );
    
    static gboolean onOpenButtonClicked( GtkWidget* button, gpointer* pointer );
    static gboolean onQuitButtonClicked( GtkWidget* button, gpointer* pointer );
    
    OSGGTKDrawingArea _canvas;
    
    GtkWidget* _dialog;
    GtkWidget* _randomButton;
    GtkWidget* _textView;
    
    //Menu
    GtkWidget* _openButton;
    GtkWidget* _quitButton;

};

#endif /* MAINWINDOW_H */

