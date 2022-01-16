/*
 * main.cpp
 *
 * COMP 15 Project 2: Six Degrees of Collaboration
 * 
 * by Nathan Solomon, 12-12-21
 
 *Purpose of file: Instatiates an instance of the SixDegrees class, which
  creates the user interface for the program which is a command loop directed 
  from the terminal. The instance of the Six Degrees class that is created 
  is determined by the parameters given to the prgram

 */
#include <iostream>
using namespace std;
#include "CollabGraph.h"
#include "SixDegrees.h"
#include "Artist.h"

int main(int argc, char *argv[])
{
    if (argc < 2 or argc > 4){
        cerr << "Usage: SixDegrees dataFile [commandFile] [outputFile]";
        cerr << "\n";
        return 0;
    }
    if(argc == 2){
        string dataFile = argv[1];
        SixDegrees test1(dataFile);
    }
    else if(argc == 3){
        
        string dataFile = argv[1];
        string commandFile = argv[2];
        SixDegrees test2(dataFile, commandFile);
    }
    else if(argc == 4){
        string dataFile = argv[1];
        string commandFile = argv[2];
        string outputFile = argv[3];
        SixDegrees test3(dataFile, commandFile, outputFile);
    }
    return 0;
}
