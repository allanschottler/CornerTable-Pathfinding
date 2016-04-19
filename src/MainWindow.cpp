/* 
 * File:   MainWindow.cpp
 * Author: allan
 * 
 * Created on April 12, 2016, 11:49 PM
 */

#include "MainWindow.h"
#include "CornerTableApplication.h"
#include <string>
#include <iostream>

MainWindow::MainWindow( std::string title ) :
    _title( title ) 
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
    
    gtk_window_set_title( GTK_WINDOW( _dialog ), _title.c_str() );
    
    GtkWidget* canvasBox = GTK_WIDGET( gtk_builder_get_object( builder, "alignmentCanvas" ) );
    
    if( _canvas.createWidget( 800, 800 ) ) 
    {
        gtk_box_pack_start( GTK_BOX( canvasBox ), _canvas.getWidget(), true, true, 2 );        
    }
    
    _randomButton = GTK_WIDGET( gtk_builder_get_object( builder, "randomButton" ) );
    _textView = GTK_WIDGET( gtk_builder_get_object( builder, "textview1" ) );    
    _aboutDialog = GTK_WIDGET( gtk_builder_get_object( builder, "aboutdialog1" ) );  
    
    _openButton = GTK_WIDGET( gtk_builder_get_object( builder, "imagemenuitem2" ) );
    _quitButton = GTK_WIDGET( gtk_builder_get_object( builder, "imagemenuitem5" ) );
    _aboutButton = GTK_WIDGET( gtk_builder_get_object( builder, "imagemenuitem10" ) );
    
    g_timeout_add( 15, (GSourceFunc)( &MainWindow::onIdle ), this );
    
    g_signal_connect( G_OBJECT( _dialog ), "destroy", G_CALLBACK( &MainWindow::onDestroy ), NULL );
    g_signal_connect( G_OBJECT( _dialog ), "delete_event", G_CALLBACK( &MainWindow::onDestroy ), NULL );
    
    g_signal_connect( G_OBJECT( _randomButton ), "clicked", G_CALLBACK( &MainWindow::onRandomButtonClicked ), NULL );
    
    g_signal_connect( G_OBJECT( _openButton ), "activate", G_CALLBACK( &MainWindow::onOpenButtonClicked ), _dialog );
    g_signal_connect( G_OBJECT( _quitButton ), "activate", G_CALLBACK( &MainWindow::onQuitButtonClicked ), _dialog );
    g_signal_connect( G_OBJECT( _aboutButton ), "activate", G_CALLBACK( &MainWindow::onAboutButtonClicked ), _dialog );
    
    g_object_set_data( ( GObject* ) _dialog, "THIS", ( gpointer )this );
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

void MainWindow::printMessage( std::string message )
{
    GtkTextBuffer* buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( _textView ) );
    GtkTextIter start;
    GtkTextIter end;
    gchar *text;

    /* Obtain iters for the start and end of points of the buffer */
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    /* Get the entire buffer text. */
    text = gtk_text_buffer_get_text( buffer, &start, &end, FALSE );
    
    std::string newText( text + message + "\n" );
    gtk_text_buffer_set_text( buffer, newText.c_str(), newText.size() );
}

void MainWindow::clearMessages()
{
    GtkTextBuffer* buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW( _textView ) );
    gtk_text_buffer_set_text( buffer, "", 0 );
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

gboolean MainWindow::onOpenButtonClicked( GtkWidget* button, gpointer pointer )
{
    gpointer result = g_object_get_data( ( GObject* ) pointer, "THIS" );
    
    if( result == NULL )
        return FALSE;
    
    MainWindow* dialog = reinterpret_cast< MainWindow* >( result );
    
    GtkWidget* chooseDialog;
    chooseDialog = gtk_file_chooser_dialog_new( "Open File",
                                          GTK_WINDOW( dialog->_dialog ),
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL );
    
    if( gtk_dialog_run( GTK_DIALOG( chooseDialog ) ) == GTK_RESPONSE_ACCEPT )
    {
        char *filename;
        filename = gtk_file_chooser_get_filename( GTK_FILE_CHOOSER( chooseDialog ) );        
        std::string filenameStr( filename );
        gtk_window_set_title( GTK_WINDOW( dialog->_dialog ), dialog->_title.c_str() );
        
        if( CornerTableApplication::getInstance()->openFile( filenameStr ) )
        {
            std::string newTitle( dialog->_title + " - " + filenameStr );
            gtk_window_set_title( GTK_WINDOW( dialog->_dialog ), newTitle.c_str() );
        }
        
        g_free( filename );
    }
    
    gtk_widget_destroy( chooseDialog );
    
    return TRUE;
}

gboolean MainWindow::onQuitButtonClicked( GtkWidget* button, gpointer pointer )
{
    return MainWindow::onDestroy();
}

gboolean MainWindow::onAboutButtonClicked( GtkWidget* button, gpointer pointer )
{
    gpointer result = g_object_get_data( ( GObject* ) pointer, "THIS" );
    
    if( result == NULL )
        return FALSE;
    
    MainWindow* dialog = reinterpret_cast< MainWindow* >( result );
    
    gtk_widget_destroy( dialog->_aboutDialog );
    
    dialog->_aboutDialog = gtk_about_dialog_new();
    gtk_about_dialog_set_name( GTK_ABOUT_DIALOG( dialog->_aboutDialog ), "[FCG] Trabalho 2" );
    gtk_about_dialog_set_version( GTK_ABOUT_DIALOG( dialog->_aboutDialog ), "v1.0" );
    gtk_about_dialog_set_comments( GTK_ABOUT_DIALOG( dialog->_aboutDialog ), "Trabalho sobre Corner Tables.\nProf. Marcelo Gattass\n19/04/2016" );
    //gtk_about_dialog_set_authors( GTK_ABOUT_DIALOG( aboutDialog ), "Allan Werner Schöttler" );
    
    gtk_widget_show_all( dialog->_aboutDialog );
    
    return TRUE;
}