/* 
 * File:   MeshLoader.cpp
 * Author: allan
 * 
 * Created on April 11, 2016, 10:36 PM
 */

#include "MeshLoader.h"
#include <gtk/gtk.h>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <clocale>

using namespace std;

MeshLoader::MeshLoader() :
    _currentPath( g_get_current_dir() ) 
{
}

CornerTable* MeshLoader::parse( string filename ) 
{
    setlocale(LC_ALL, "C");
            
    //std::string filePath(_currentPath + "/data/" + filename);
    std::string filePath( filename );
    
    int nv, nf;
    
    // Container holding last line read
    string readLine;
    // Containers for delimiter positions
    int delimiterPos_1, delimiterPos_2, delimiterPos_3, delimiterPos_4, delimiterPos_5;

    // Open file for reading
    ifstream in(filePath.c_str());

    // Check if file is in OFF format
    getline(in, readLine);
    if (readLine != "OFF") {
        cout << "The file to read is not in OFF format." << endl;
        return 0;
    }

    // Read values for Nv and Nf
    getline(in, readLine);
    delimiterPos_1 = readLine.find(" ", 0);
    nv = atoi(readLine.substr(0, delimiterPos_1 + 1).c_str());
    delimiterPos_2 = readLine.find(" ", delimiterPos_1);
    nf = atoi(readLine.substr(delimiterPos_1, delimiterPos_2 + 1).c_str());

    // Read the vertices
    std::vector< double > vertexes;
    vertexes.reserve(nv*3);
    int index = 0;
    
    for (int n = 0; n < nv; n++) {        
        getline(in, readLine);
        
        delimiterPos_1 = readLine.find(" ", 0);
        vertexes[index++] = ( stod(readLine.substr(0, delimiterPos_1).c_str()) );
        //vertexes.push_back( atof(readLine.substr(0, delimiterPos_1).c_str()) );
        //vertexes.push_back( strtod( buffer, &buffer ) );
        delimiterPos_2 = readLine.find(" ", delimiterPos_1 + 1);
        vertexes[index++] = ( stod(readLine.substr(delimiterPos_1, delimiterPos_2).c_str()) );
        //vertexes.push_back( atof(readLine.substr(delimiterPos_1, delimiterPos_2).c_str()));
        //vertexes.push_back( strtod( buffer, &buffer ) );
        delimiterPos_3 = readLine.find(" ", delimiterPos_2 + 1);
        vertexes[index++] = ( stod(readLine.substr(delimiterPos_2, delimiterPos_3).c_str()) );
        //vertexes.push_back( atof(readLine.substr(delimiterPos_2, delimiterPos_3).c_str()) );
        //vertexes.push_back( strtod( buffer, &buffer ) );

        /*cout << vertexes[n] << "\t" << vertexes[n+1] << "\t" <<
                vertexes[n+2] << "\t" << endl;*/
    }

    // Read the facades
    std::vector< int > indices;
    indices.reserve(nf*3);
    
    for (int n = 0; n < nf; n++) {
        getline(in, readLine);
        delimiterPos_1 = readLine.find(" ", 0);
        delimiterPos_2 = readLine.find(" ", delimiterPos_1 + 1);
//        indices.push_back(
//                atoi(readLine.substr(delimiterPos_1, delimiterPos_2).c_str()));
        delimiterPos_3 = readLine.find(" ", delimiterPos_2 + 1);
        indices.push_back(
                atoi(readLine.substr(delimiterPos_2, delimiterPos_3).c_str()));
        delimiterPos_4 = readLine.find(" ", delimiterPos_3 + 1);
        indices.push_back(
                atoi(readLine.substr(delimiterPos_3, delimiterPos_4).c_str()));
        delimiterPos_5 = readLine.find(" ", delimiterPos_4 + 1);
        indices.push_back(
                atoi(readLine.substr(delimiterPos_4, delimiterPos_5).c_str()));

        /*cout << indices[n] << "\t" << indices[n+1] << "\t" <<
                indices[n+2] << "\t" << endl;*/
    }    
    
    return new CornerTable( &indices[ 0 ], &vertexes[ 0 ], nf, nv, 3 );
}

