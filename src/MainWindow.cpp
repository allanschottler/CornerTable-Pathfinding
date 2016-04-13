/* 
 * File:   MainWindow.cpp
 * Author: allan
 * 
 * Created on April 12, 2016, 11:49 PM
 */

#include "MainWindow.h"
#include "CornerTableApplication.h"
#include <string>

MainWindow::MainWindow() 
{
    GError* error = NULL;
    GtkBuilder* builder = gtk_builder_new();
    
    std::string gladePath( g_get_current_dir() );
    gladePath.append( "/data/glade/MainWindow.glade" );
    
    if( !gtk_builder_add_from_file( builder, gladePath.c_str(), &error ) )
    {
        g_warning( "Nao foi possivel abrir o arquivo: %s", error->message );
        g_error_free( error );
    }
    
    _dialog = GTK_WIDGET( gtk_builder_get_object( builder, "window1" ) );
    
    GtkWidget* canvasBox = GTK_WIDGET( gtk_builder_get_object( builder, "alignmentCanvas" ) );
    
    if( _canvas.createWidget( 800, 800 ) ) 
    {
        gtk_box_pack_start( GTK_BOX( canvasBox ), _canvas.getWidget(), true, true, 2 );        
    }
    
    _randomButton = GTK_WIDGET( gtk_builder_get_object( builder, "randomButton" ) );
    
    g_timeout_add( 15, (GSourceFunc)( &MainWindow::onIdle ), this );
    
    g_signal_connect( G_OBJECT( _dialog ), "destroy", G_CALLBACK( &MainWindow::onDestroy ), NULL );
    g_signal_connect( G_OBJECT( _dialog ), "delete_event", G_CALLBACK( &MainWindow::onDestroy ), NULL );
    
    g_signal_connect( G_OBJECT( _randomButton ), "clicked", G_CALLBACK( &MainWindow::onRandomButtonClicked ), _dialog );
}


MainWindow::~MainWindow() 
{
    g_object_unref( G_OBJECT( _dialog ) );
}

void MainWindow::show()
{
    gtk_widget_show_all( GTK_WIDGET( _dialog ) );
}

OSGGTKDrawingArea& MainWindow::getCanvas()
{
    return _canvas;
}

gboolean MainWindow::onDestroy()
{
    gtk_main_quit();
    
    return FALSE;
}

gboolean MainWindow::onIdle( gpointer pointer )
{
    MainWindow* dialog = reinterpret_cast< MainWindow* >( pointer );
    
    dialog->_canvas.queueDraw();
    
    return TRUE;
}

gboolean MainWindow::onRandomButtonClicked( GtkWidget* button, gpointer* pointer )
{
    CornerTableApplication::getInstance()->generateRandomPoint();
    
    return TRUE;
}