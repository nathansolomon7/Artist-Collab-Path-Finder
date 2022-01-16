/* 
 * unit_tests.h
 * 
 * CS 15 Six Degrees
 * by Nathan Solomon, January 2021
 * 
 * Purpose: tests the report_path implementation in the CollabGraph class
 */


#include "CollabGraph.h"
#include "Artist.h"
#include "SixDegrees.h"
#include <cassert>
#include <stack>
using namespace std;
// note: all function contracts do not contain information about 
// the arguments and return of each function, since every test 
//function do not take in arguments and not return anything

/*
Purpose: tests the functionality of the report_path function for a linear 
graph (like a linked list) where the start of the graph has no predecessors,
and the end of the graph has no "to" vertices
*/
void reportPath_test(){
    CollabGraph graph1;
    vector<Artist> artistList;
    Artist a1("Calvin Harris");
    a1.add_song("Over Now");
    a1.add_song("Animals");
    artistList.push_back(a1);
    Artist a2("Weeknd");
    a2.add_song("Wake up");
    a2.add_song("pray 4 luv");
    a2.add_song("Rolling Stone");
    a2.add_song("Over Now");
    artistList.push_back(a2);
    Artist a3("Travis Scott");
    a3.add_song("Goosebumps");
    a3.add_song("Sicko Mode");
    a3.add_song("Yosemite");
    a3.add_song("pray 4 luv");
    artistList.push_back(a3);
    Artist a4("Nav");
    a4.add_song("Yosemite");
    a4.add_song("Turks");
    artistList.push_back(a4);
    graph1.populate_graph(artistList);
    // to, then from
    graph1.set_predecessor(a2, a1);
    graph1.set_predecessor(a3, a2);
    graph1.set_predecessor(a4, a3);
    stack <Artist> path;
    // should be a valid path;
    path = graph1.report_path(a1, a4);
    if(path.size() == 0){
        cout << "path does not exist" << endl;
    }
    while (path.size() > 1){
        Artist top = path.top();
        path.pop();
        Artist next = path.top();
        cout << top.get_name() << " collabarated with " 
        << next.get_name() << " in " << top.get_collaboration(next) << endl;
    }
}

/*
Purpose: tests the functionality of the report_path function for an input of 
two artists with a collaboration between them
*/
void reportPathtwoArtists_test(){
        CollabGraph graph1;
        vector<Artist> artistList;
        Artist a3("Travis Scott");
        a3.add_song("Goosebumps");
        a3.add_song("Sicko Mode");
        a3.add_song("Yosemite");
        a3.add_song("pray 4 luv");
        artistList.push_back(a3);
        Artist a4("Nav");
        a4.add_song("Yosemite");
        a4.add_song("Turks");
        artistList.push_back(a4);
        graph1.populate_graph(artistList);
        graph1.set_predecessor(a4, a3);
        stack <Artist> path;
        
        path = graph1.report_path(a3, a4);
        if(path.size() == 0){
            cout << "path does not exist" << endl;
        }
        while (path.size() > 1){
            Artist top = path.top();
            path.pop();
            Artist next = path.top();
            cout << top.get_name() << " collabarated with " 
            << next.get_name() << " in " << top.get_collaboration(next) << endl;
        }
}
/*
Purpose: tests the functionality of the report_path function for a graph 
with a source that is within a cycle in a graph and the destination is in
the cycle as well. For this case, the cycle is a triangle shape with 3 vertices
*/

void reportPathcycle_test(){
    CollabGraph graph1;
    vector<Artist> artistList;
    Artist a1("21 Savage");
    a1.add_song("Yosemite");
    artistList.push_back(a1);
    Artist a3("Travis Scott");
    a3.add_song("Goosebumps");
    a3.add_song("Sicko Mode");
    a3.add_song("Yosemite");
    a3.add_song("pray 4 luv");
    artistList.push_back(a3);
    Artist a4("Nav");
    a4.add_song("Yosemite");
    a4.add_song("Turks");
    artistList.push_back(a4);
    graph1.populate_graph(artistList);
    // to, then from
    graph1.set_predecessor(a4, a3);
    graph1.set_predecessor(a1, a4);
    stack <Artist> path;
    // should be a valid path;
    path = graph1.report_path(a3, a1);
    if(path.size() == 0){
        cout << "path does not exist" << endl;
    }
    while (path.size() > 1){
        Artist top = path.top();
        path.pop();
        Artist next = path.top();
        cout << top.get_name() << " collabarated with " 
        << next.get_name() << " in " << top.get_collaboration(next) << endl;
    }
}

/*
Purpose: tests the functionality of the report_path function for a graph 
with a source that is within a cycle in a graph and the destination is not in
the cycle. For this case, the cycle is a triangle with a a node adjacent 
to one vertex that makes up the triangle
*/

void reportPathcycle2_test(){
    CollabGraph graph1;
    vector<Artist> artistList;
    Artist a1("21 Savage");
    a1.add_song("Yosemite");
    artistList.push_back(a1);
    Artist a2("Weeknd");
    a2.add_song("Wake up");
    a2.add_song("pray 4 luv");
    a2.add_song("Rolling Stone");
    a2.add_song("Over Now");
    artistList.push_back(a2);
    Artist a3("Travis Scott");
    a3.add_song("Goosebumps");
    a3.add_song("Sicko Mode");
    a3.add_song("Yosemite");
    a3.add_song("pray 4 luv");
    artistList.push_back(a3);
    Artist a4("Nav");
    a4.add_song("Yosemite");
    a4.add_song("Turks");
    artistList.push_back(a4);
    graph1.populate_graph(artistList);
    // to, then from
    graph1.set_predecessor(a3, a2);
    graph1.set_predecessor(a1, a3);
    graph1.set_predecessor(a4, a1);
    stack <Artist> path;
    // should be a valid path;
    path = graph1.report_path(a2, a4);
    if(path.size() == 0){
        cout << "path does not exist" << endl;
    }
    while (path.size() > 1){
        Artist top = path.top();
        path.pop();
        Artist next = path.top();
        cout << top.get_name() << " collabarated with " 
        << next.get_name() << " in " << top.get_collaboration(next) << endl;
    }
}

/*
Purpose: tests the functionality of the report_path function for a disconnected
graph, where the destination is seperated from the graph and can never reach
the source.
Notes: For this case, the graph consists of a cycle shaped in a triangle with 
three vertices, where the source vertex is within the cycle. The destination 
is a vertex that is disconnected from the graph, as 
the artist has no collaborations with the artists in the cycle. The test 
should "path does not exist"
*/

void reportPathdisconnected_test(){
    CollabGraph graph1;
    vector<Artist> artistList;
    Artist a1("21 Savage");
    a1.add_song("Yosemite");
    artistList.push_back(a1);
    
    Artist a3("Travis Scott");
    a3.add_song("Goosebumps");
    a3.add_song("Sicko Mode");
    a3.add_song("Yosemite");
    a3.add_song("pray 4 luv");
    artistList.push_back(a3);
    Artist a4("Nav");
    a4.add_song("Yosemite");
    a4.add_song("Turks");
    artistList.push_back(a4);
    // this node is disconnected from the cycle 
    
    Artist a6("Doja Cat");
    a6.add_song("Rules");
    a6.add_song("Die For You Remix");
    artistList.push_back(a6);
    graph1.populate_graph(artistList);
    // to, then from
    graph1.set_predecessor(a1, a3);
    graph1.set_predecessor(a4, a1);
    
    stack <Artist> path;
    // should be a valid path;
    path = graph1.report_path(a3, a6);
    
    if(path.size() == 0){
        cerr << "path does not exist" << endl;
    }
    while (path.size() > 1){
        Artist top = path.top();
        path.pop();
        Artist next = path.top();
        cout << top.get_name() << " collabarated with " 
        << next.get_name() << " in " << top.get_collaboration(next) << endl;
    }
}

/*
Purpose: tests the functionality of the get vertex_neighbors test
*/

void getVertexneighbors_test(){
    CollabGraph graph1;
    vector<Artist> artistList;
    Artist a1("Calvin Harris");
    a1.add_song("Over Now");
    a1.add_song("Animals");
    artistList.push_back(a1);
    Artist a2("Weeknd");
    a2.add_song("Wake up");
    a2.add_song("pray 4 luv");
    a2.add_song("Rolling Stone");
    a2.add_song("Over Now");
    artistList.push_back(a2);
    Artist a3("Travis Scott");
    a3.add_song("Goosebumps");
    a3.add_song("Sicko Mode");
    a3.add_song("Yosemite");
    a3.add_song("pray 4 luv");
    artistList.push_back(a3);
    Artist a4("Nav");
    a4.add_song("Yosemite");
    a4.add_song("Turks");
    artistList.push_back(a4);
    
    graph1.populate_graph(artistList);
    graph1.print_graph(cout);
    vector <Artist> neighbors1list;
    neighbors1list = graph1.get_vertex_neighbors(a1);
    cout << a1.get_name() << "'s neighbors: " << endl;
    for(size_t i = 0; i < neighbors1list.size();i++){
        cout << neighbors1list[i].get_name() << endl;
    }
    vector <Artist> neighbors2list;
    neighbors2list = graph1.get_vertex_neighbors(a2);
    cout << a2.get_name() << "'s neighbors: " << endl;
    for(size_t i = 0; i < neighbors2list.size();i++){
        cout << neighbors2list[i].get_name() << endl;
    }
    vector <Artist> neighbors3list;
    neighbors3list = graph1.get_vertex_neighbors(a3);
    cout << a3.get_name() << "'s neighbors: " << endl;
    for(size_t i = 0; i < neighbors3list.size();i++){
        cout << neighbors3list[i].get_name() << endl;
    }
    
    
}





