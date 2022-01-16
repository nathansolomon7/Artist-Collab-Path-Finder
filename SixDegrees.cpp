/*
*
* SixDegrees.cpp
* 
* COMP 15 project 2 - "Six Degrees of Seperation"
* 
* by Nathan Solomon, 12-12-21
* 
*Purpose of file: Provides the implementation for the SixDegrees class and
all functions used to run the SixDegrees program. To instantiate the SixDegrees
class and run the program, calling the constructor, which 
initializes an SixDegrees object, can be used to then interact with the 
command loop, where the program is accessible through commands
* 
*/

#include <iostream>
using namespace std;
#include "SixDegrees.h"
#include "Artist.h"
#include "CollabGraph.h"
#include <fstream>  
#include <queue>
#include <stack>
#include <vector>


/*
Purpose: constructor for SixDegrees class for when the file of artist info 
is only given. Runs the command loop
Args:the name of the file containing artist information
Notes: sends all output to cout and all command input from cin
*/
SixDegrees::SixDegrees(string dataFilename) {
    data_file.open(dataFilename);
    //checking to make sure the file containing artist info is opened correctly
    if (not data_file.is_open()) {
        printErroropeningFile(dataFilename);
        return;
    }
    populateArtistList();
     data_file.close();
     commandLoop(cin, cout);    
}

/*
Purpose: constructor for SixDegrees class for when the file of artist info 
and the file of commands to run is given
Args:the name of the file containing artist information and the name of the 
commands file
Notes: sends all output to cout and all command input from the commands file
*/
SixDegrees::SixDegrees(string dataFilename, string commandsFilename) {
    //opening data file with the artist info in it
    data_file.open(dataFilename);
    if (not data_file.is_open()) {
            printErroropeningFile(dataFilename);
            return;
    }
    // opening up the commands file with a list of commands
    commands_file.open(commandsFilename);
    if (not commands_file.is_open()) {
            printErroropeningFile(commandsFilename);
            return;
    }
    // reading in artists and creating a vector of Artists
    populateArtistList();
     data_file.close();
     commandLoop(commands_file, cout);
     commands_file.close();
}

/*
Purpose: constructor for SixDegrees class for when the file of artist info,
 the file of commands to run, and an output File for sending output is given
Args:the name of the file containing artist information, the name of the 
commands file, and the name of the output file
Notes: sends all output to the output file and all command input from the
 commands file
*/
SixDegrees::SixDegrees(string dataFilename, string commandsFilename, 
                                            string outputFilename) {
    //opening data file with the artist info in it
    data_file.open(dataFilename);
    if (not data_file.is_open()) {
            printErroropeningFile(dataFilename);
            return;
    } output_file.open(outputFilename);
    if (not output_file.is_open()) {
            printErroropeningFile(outputFilename);
            return;
    }
    // reading in artists and creating a vector of Artists
    populateArtistList();
    data_file.close();
     //opening the commands file with commands in it
     commands_file.open(commandsFilename);
     if (not commands_file.is_open()) {
        printErroropeningFile(commandsFilename);
        return;
     }
    commandLoop(commands_file, output_file);
    commands_file.close(); 
    output_file.close();    
}
/*
Purpose: Creates a command loop for the user to interact with the program with,
using a set of specific commands
Args: an istream type to receive input from and an ostream type to specify 
where to direct output
Notes: error handles for invalid commands
*/
void SixDegrees::commandLoop(istream &input, ostream &output) {
    graph.populate_graph(artistList);
    string userCommand = "";
    while (userCommand != "quit" and getline(input, userCommand)) {
        if (userCommand == "print") {
            graph.print_graph(output);
        } else if (userCommand == "bfs") {
            getSourceandDestartists(userCommand, input);
            findPathbfs(output);
        } else if (userCommand == "dfs") {
            getSourceandDestartists(userCommand, input);
            findPathdfs(output);
        } else if (userCommand == "not") {
            getSourceandDestartists(userCommand, input);
            vector <string> excludedArtists;
            bool areallArtistsvalid = true;
            Artist sourceArtist(sourceArtistname);
            Artist destArtist(destArtistname);
            if (!areArtistsinGraph(sourceArtist, destArtist, output)) {
                areallArtistsvalid = false;
            } areallArtistsvalid = markExcludedArtists(excludedArtists,
                                                userCommand, input, output);
            if (areallArtistsvalid)
                findPathbfs(output);
        } else if (userCommand == "quit") {
            return;
        } else {
            printInvalidCommand(userCommand, output);
        }
    }
}
/*
Purpose: reads in the source artist and destination artist for searching
Parameters: the user's next command and an istream variable
Returns: none
*/
void SixDegrees::getSourceandDestartists(string userCommand, istream &input) {
    getline(input, userCommand);
    sourceArtistname = userCommand;
    // getting the destination Artist in the graph
    getline(input, userCommand);
    // getting the first artist to be excluded, or reading in an 
    // asterisk to notify not to avoid any artists
    destArtistname = userCommand;
}
/*
Purpose: Marks artists to be excluded for the not command
Parameters: an initially empty vector of excluded artists, the next user 
command, an istream variable, and an ostream variable for output
Returns: true 
*/
bool SixDegrees::markExcludedArtists(vector <string> excludedArtists, 
                        string userCommand, istream &input, ostream &output) {
    bool areAvoidedartistsValid = true;
    userCommand = "";
    getline(input, userCommand);
    do {
        excludedArtists.push_back(userCommand);
        getline(input, userCommand);
        
    } while (userCommand != "*" and !(input.eof()));
    if (excludedArtists.size() == 0) {
        return areAvoidedartistsValid;
    }
    for (size_t i = 0; i < excludedArtists.size();i++) {
        Artist a(excludedArtists[i]);
        // marking the artist specified by input as marked (if it is in 
        //the graph) for avoidance when a bfs is done in graph
        if (isArtistinGraph(a, output)) {
            graph.mark_vertex(a);
        }
        else {
            areAvoidedartistsValid = false;
        }
    }
    return areAvoidedartistsValid;
}

/*
Purpose: prints an error statement regarding the command that is not valid
Parameters: the invalid command and the output to send the error message to
Returns: none
Other: None
*/
void SixDegrees::printInvalidCommand(string userCommand, ostream &output) {
    output << userCommand << " is not a command. Please try again." << endl;
}

SixDegrees::~SixDegrees() {

}

/*
Purpose: prints an error statement regarding the file that can not be opened
Parameters: the file name that can not be opened
Returns: nothing
Other: None
*/
void SixDegrees::printErroropeningFile(string filename) {
    cerr << filename << " cannot be opened." << endl;
}
/*
Purpose: performs a breadth first search in the graph from the 
source Artist in the path to the destination Artist in the search
Parameters: A starting Artist object and an ending Artist object
Returns: true or false depending on if the ending artist was reached 
when starting from the starting artist in its BFS
Other: None
*/
bool SixDegrees::runBfs(const Artist& sourceArtist, const Artist& destArtist) {
    queue<Artist>neighborsQueue;
    vector<Artist>currVertexneighbors;
    if (graph.is_marked(sourceArtist) or graph.is_marked(destArtist)) {
        return false;
    }
    graph.mark_vertex(sourceArtist);
    neighborsQueue.push(sourceArtist);
    while (!neighborsQueue.empty()) {
        Artist currArtist = neighborsQueue.front();
        neighborsQueue.pop();
        currVertexneighbors = graph.get_vertex_neighbors(currArtist);
        //populating neighbors queue with the neighbors of the current vertex 
        //we are at in the bfs
        for (size_t i = 0; i < currVertexneighbors.size(); i++) {
            if (graph.is_marked(currVertexneighbors[i]) == false) {
                graph.mark_vertex(currVertexneighbors[i]);
                //marking the neighbors predecessor then adding to queue
                graph.set_predecessor(currVertexneighbors[i], currArtist);
                neighborsQueue.push(currVertexneighbors[i]);
            }
        }
    }
    if (graph.is_marked(destArtist)) {
        return true;
    }
    else {
        return false;
    }
}
/*
Purpose: wrapper function for runBFS and handles all error handling 
for invalid data input or if a path was not found
Parameters: A starting Artist name,  an ending Artist name, and the 
output variable
Returns: none
Other: None
*/
void SixDegrees::findPathbfs(ostream &output) {
    
    //vector of artists to store the neighbors of each current vertex
    Artist sourceArtist(sourceArtistname);
    Artist destArtist(destArtistname);
    //ensures that both the source and destination artist are in graph
    if (!areArtistsinGraph(sourceArtist, destArtist, output)) {
        return;
    }
    if (sourceArtistname == destArtistname) {
        printInvalidpath(output);
        return;
    }
    
    bool isPath = runBfs(sourceArtist, destArtist);
    if (isPath) {
        stack<Artist>path;
        path = graph.report_path(sourceArtist, destArtist);
        printPath(path, output);
    }
    else {
        printInvalidpath(output);
    }
    graph.clear_metadata();
}
/*
Purpose: prints a path between a starting artist and an ending artist
Parameters: A stack of Artists that build a relation in the path from 
the starting artist to the ending artist
Returns: none
Other: only called when there is a path between two artists in the graph
*/
void SixDegrees::printPath(stack <Artist> path, ostream &output) {
    while (path.size() > 1) {
        Artist top = path.top();
        path.pop();
        Artist next = path.top();
        output << '"' << top.get_name() << '"' << " collaborated with " << '"'
        << next.get_name() << '"' << " in " << '"' 
        << top.get_collaboration(next) << '"' << "." << endl;
    }
    output << "***" << endl;
}

/*
Purpose: output statement when there is no path between two artists
Parameters: A starting Artist name, an ending Artist name, and an output 
variable
Returns: none
*/
void SixDegrees::printInvalidpath(ostream &output) {
    output << "A path does not exist between " << '"' << sourceArtistname 
    << '"' << " and " << '"' << destArtistname << '"' << "." << endl;
}

/*
Purpose: Checks if both the starting artist and ending artist are in the 
graph
Returns: true if both of the artists are in the graph and false if 
otherwise
Other: prints a print statement for the artist that is not in the graph
*/
bool SixDegrees::areArtistsinGraph(const Artist& sourceArtist, 
    const Artist& destArtist, ostream &output) {
    bool areArtistsinGraph = true;
    //print error statement if artist is not found in graph
    if (!graph.is_vertex(sourceArtist)) {
        output << '"' << sourceArtist << '"' 
        << " was not found in the dataset :(" << endl;
        areArtistsinGraph = false;
    }
    if (!graph.is_vertex(destArtist)) {
        output << '"' << destArtist << '"'
        << " was not found in the dataset :(" << endl;
        areArtistsinGraph = false;
    }
    return areArtistsinGraph;
}

/*
Purpose: Checks if a specific artist is valid and can be found in the graph
Returns: true if the artist is in the graph and false if otherwise
Other: prints a print statement for the artist that is not in the graph
*/
bool SixDegrees::isArtistinGraph(const Artist& artist, ostream &output) {
    bool isArtistsinGraph = true;
    if (!graph.is_vertex(artist)) {
        output << '"' << artist.get_name() << '"' 
        << " was not found in the dataset :(" << endl;
        isArtistsinGraph = false;
    }
    return isArtistsinGraph;
    
}



void SixDegrees::populateArtistList() {
    string artistName = "";
    string songName = "";
    // read in artist name and initialize artist object
    while (getline(data_file, artistName)) {
        Artist a(artistName);
        //read lines until an asterik is detected
        while (getline(data_file, songName) and songName != "*") {
            a.add_song(songName);
        }
        artistList.push_back(a);
    }
}

bool SixDegrees::runDfs(const Artist& sourceArtist, 
                                                    const Artist& destArtist) {
    graph.mark_vertex(sourceArtist);
    vector<Artist>currVertexneighbors;
    currVertexneighbors = graph.get_vertex_neighbors(sourceArtist);
    for (size_t i = 0; i < currVertexneighbors.size(); i++) {
        if (graph.is_marked(currVertexneighbors[i]) == false) {
            //the neighbor of the current node is marked with a predecessor,
            //as the neighbor is then used for the next traversal recursively
            graph.set_predecessor(currVertexneighbors[i], sourceArtist);
            runDfs(currVertexneighbors[i], destArtist);
        }
    }
    if (graph.is_marked(destArtist)) {
        return true;
    }
    else {
        return false;
    }
}

void SixDegrees::findPathdfs(ostream &output) {
    if (sourceArtistname == destArtistname) {
        printInvalidpath(output);
        return;
    }
    //vector of artists to store the neighbors of each current vertex
    Artist sourceArtist(sourceArtistname);
    Artist destArtist(destArtistname);
    //ensures that both the source and destination artist are in graph
    if (!areArtistsinGraph(sourceArtist, destArtist, output)) {
        return;
    }
    bool isPath = runDfs(sourceArtist, destArtist);
    if (isPath) {
        stack<Artist>path;
        path = graph.report_path(sourceArtist, destArtist);
        printPath(path, output);
    }
    else {
        printInvalidpath(output);
    }
    graph.clear_metadata();
}




