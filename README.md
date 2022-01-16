# Artist-Collab-Path-Finder
Nathan Solomon

10-28-21

Purpose: Creates a program that can find the shortest path 
of artists between two artists' related collabarations when
given a list of information regarding artists and the songs
each has worked on
 

Known bugs: none

-------------------------------------------------------------------------
Files:
This section will outline all files submitted
main.cpp:
Instantiates an instance of the SixDegrees class, which creates
creates the user interface for the program, a command loop directed 
from the terminal, and runs the program for a given amount of information 
of artists passed in by user. Used to run all testing files and input, as well
as used for comparison of output with reference program 

Artist.cpp: 
Implementation file for the Artist class and all functions that allow 
the client to interact with an artist. 

Artist.h:
The Artist class builds the functions that can be done on Artist, mainly 
used in getting information about an Artist, such as song name and 
discography

artists.txt:
Given file that provides a large list of artists, along with the songs of 
each respective artist. Each artist is seperated by an asterisk, which is 
used as an invariant to create the individual artist objects that make up 
the graph

cmd_basicPrint.txt:
Testing file for SixDegrees, which is mainly just used to ensure that files 
can be sucessfuly read in from a file, an option given by the sixDegrees class.

cmd_BFS.txt:
Testing file for both bfs. Used with the artists.txt file, and 
performs a random assortment of bfs searches between artists in the graph.

cmd_DFS.txt:
Testing file for dfs. Used with the artists.txt file, and 
performs a random assortment of dfs searches between artists in the graph.

cmd_cycleTest.txt:
Testing file for both bfs and dfs. Used with the data_cycleGraph.txt file, and 
performs searches between artists within a cycle in a graph, ensuring that 
infinite searching does not occur.

cmd_disconnectedTest.txt:
Teting file for both bfs and dfs. Used with data_cycleGraph.txt file and 
calls searches between artists, where either the source is connected 
in the graph, while the other is disconnected from the graph. Ensures 
proper handling of a disconnected search.

cmd_Emptylinestest.txt:
Testing file for both bfs and dfs. Ensures that an empty string of a command 
is correctly handled properly and matches with reference implementation 
handling.

cmd_pathArtistonSelf.txt:
Testing file for both bfs and dfs. Used with data_linearGraph.txt. 
Ensures that a search with the same start and end artist is properly 
handled and does not cause a crash in the program.

cmd_notTest.txt:
tests the not function with various restrictions, starting with no 
artists to avoid, then giving more artists to avoid along the path. Artists 
that are also not in the graph is tested in the commands as well to ensure 
proper error handling. The edge case of listing the source or destinatation 
artist under the "not" artists is also checked for handling.

cmd_notEdgecases.txt:
Tests the not function further with more edge cases, placing a focus 
on having artists not known that are being inputted in the list of 
artists to avoid. Ensures the right error statments are being printed 
each time this error shows up.

cmd_notEdgecases2.txt:
Tests the not function further with more edge cases, placing a focus 
on having not being read in without an asterisk, and artists that are the 
source and destination artists that are not known

cmd_notEdgecase3.txt:
Tests the not function by including a source artist name under "not".


cmd_extraLineTest.txt:
Testing file for SixDegrees. Used to test if the program does not crash or 
cause unneccessary line read in when an extra line is left at the end of a 
commands file

cmd_invalidCommands.txt:
Testing file for SixDegrees. Used to test if the program does not crash and 
error handles when given invalid commands. For week 1, these valid commands 
are print and quit.

CollabGraph.cpp: 
Implementation file for CollabGraph class, which provides the main functions 
for creating the graph from the artists file, as well as eventually performing 
search operations.

CollabGraph.h:
The Collab Graph class buids the functions used to create and manipulate the 
graph from the given artist information, as well as accessing information 
in the graph and getting information about the graph (vertices, edges, etc..)

data_emptyLinetest.txt:
Testing file for SixDegrees. Ensures that an error is thrown if an empty line 
for a given artist name is tried to be inserted into the graph. Should throw 
an error instead of causing the program to crash without explanation.

data_extraLinetest.txt:
Testing file for SixDegrees. Ensures that the program does not read in extra 
information or crashes when an extra line is left at the end of the data file 
containing artist information. 

data_linearGraph.txt:
Testing file for both searches. Creates a linear graph. It is used for a simple 
traversal to return the path between one node to the other in a linear 
fashion.

data_cycleGraph.txt:
Testing file for all searches. Creates a graph with a cycle in it and 
ensures that bfs and dfs do not run in indefinete cycles, essentially 
testing the marking of predecessors.

data_disconnectedEnd.txt:
Testing file for all searches. Creates a linear graph with a disconnected 
node. Used with cmd_disconnectedTest.txt to test the proper errors are thrown
for trying to run a search involving a disconnected node in a graph.


SixDegrees.cpp: 
Implementation file for sixDegrees class. Creates the operations that allow 
the program to be ran using CollabGraph functions as well, such as constructors
for different amounts of file arguments and is responsible for file read in 
and command loop implementation 

SixDegrees.h:
The sixDegrees class builds the class responsible for creating the program 
that allows the user to build the graph using collabGraph functions and 
analyze the graph

smallArtists.txt:
Testing file for SixDegrees. Small info file of artists that are all connected
with each other. Used for the same purpose of artists.txt, except used in 
debugging when trying to figure out bug sources by noticing print issues or 
patterns more easily with a smaller sample size than artists.txt 

unit_tests.h:
Testing file used to test report path manually without relying on doing a 
search and also used to test get_vertex_neighbors. Unit testing was not 
used after phase 1. It was not used to test any of the search commands.


----------------------------------------------------------------------------
How to compile and run the program:
This section of the README will outline how to compile and run the program
compile using: make 
run using: ./SixDegrees dataFile [commandsFile] [outPutFile]
Upon running, the program enters a command Loop for the user to interact with 
the program using various keywords. To end the program, type the word "quit". 
This is used only when commands are not given in a file as an optional 
parameter.

for unit testing results, test by running: 
unit_test
-----------------------------------------------------------------------------
tested SixDegrees and program as a whole by:
passing in the intentionally made testing files that test a specfic variation
of a proper input (cycle in graph, empty line, disconnected graph etc..),
 and run using the main driver file, which tests the program using all
possible parameters that can be given for the program.

All outputs were given by running main.cpp with different input files.
The outputs of my program were written to output files and compared using 
diff with the reference program for each case being tested.

Unit testing was used to test report path by creating a set of vertices 
that are manually had to have predecessors marked, then the path given 
when tested under various graph formations.

Read the files section above for a description of each testing file's purpose 
that was ran through with main.cpp and then comapared with reference 
implementation


-----------------------------------------------------------------------------
Outline of Data Structures and algorithms used:



In this program, queues were used in keeping track of which 
neighbor to explore during a breadth first search, as explored neighbors 
were removed from the queue, while its neighbbors were added to the queue.
Vectors were used to the Artists after being created from file read in or 
input by the user. 
Unordered maps in this program were used to create the graph as Artists 
were being populated to the map. 
