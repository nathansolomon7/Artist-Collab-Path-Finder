/*
* SixDegrees.h
* 
* COMP 15 project 2 - "Six Degrees of Seperation"
* 
* by Nathan Solomon, 12-12-21
* 
*Purpose of file: The SixDegrees class builds the main functions/ possible
 operations of the CollabGraph, which is interacted with using commands
 in the command loop (accessable through an instance of the SixDegrees class)
 This class relies on the CollabGraph class and its functions, as well as 
 the Artist class.
* 
*/
#include <iostream>
#include <vector>
#include "Artist.h"
#include "CollabGraph.h"
#include <fstream>  
#include <stack>

class SixDegrees{
    public:
        SixDegrees(std::string dataFilename);
        SixDegrees(std::string dataFilename, std::string commandsFilename);
        SixDegrees(std::string dataFilename, std::string commandsFilename, 
                                             std::string outputFilename);
        ~SixDegrees();
    private:
        std::ifstream data_file;
        std::ifstream commands_file;
        std::ofstream output_file;
        std::vector<Artist> artistList;
        CollabGraph graph;
        string sourceArtistname = "";
        string destArtistname = "";
        void commandLoop(std::istream &input, std::ostream &output);
        void printErroropeningFile(std::string filename);
        void printInvalidCommand(std::string userCommand, std::ostream &output);
        void printInvalidpath( std::ostream &output);
        void printPath(std::stack <Artist> path, std::ostream &output);
        bool runBfs(const Artist& sourceArtist, const Artist& destArtist);
        bool areArtistsinGraph(const Artist& sourceArtist, 
            const Artist& destArtist, std::ostream &output);
        void populateArtistList();
        void findPathdfs( std::ostream &output);
        bool runDfs(const Artist& sourceArtist, const Artist& destArtist);
        bool markExcludedArtists(vector <string> excludedArtists,
            std::string userCommand, std::istream &input, std::ostream &output);
        void getSourceandDestartists(std::string userCommand,
                                                        std::istream &input);
        bool isArtistinGraph(const Artist& artist, std::ostream &output);
        void findPathbfs(std::ostream &output);
        
};