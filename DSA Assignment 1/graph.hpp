#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <map>
#include <list>
#include <limits.h>

using namespace std;

template <typename T> // the template allows the weight of an edge to take any numeric data type (denoted by T).
class Graph {

	public:
        
        /* define your data structure to represent a weighted undirected graph */
        std::map<string,map<string,T>> adjacency_list; //Map of maps that includes Vectors, their Adjacent vectors and the weight of the edge between the two vectors
        int count_edge = 0; //Variable to store the count of edges in the graph
        

        /* test1 */
		Graph(); // the contructor function.
		~Graph(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the graph.
		size_t num_edges(); // returns the total number of edges in the graph.

        /* test2 */
        void add_vertex(const string&); // adds a vertex to the graph -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the graph -- returns true if the graph contains the given vertex; otherwise, returns false.
        
        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the graph.

        /* test4 */
        void add_edge(const string&, const string&, const T&); // adds a weighted edge to the graph -- the two strings represent the incident vertices; the third parameter represents the edge's weight.
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the graph -- returns true if the edge exists; otherwise, returns false.
		
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the graph -- each edge is represented by a pair of vertices incident to the edge.
        
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex by an edge.
        size_t degree(const string&); // returns the degree of a vertex.

        /* test7 */
		void remove_edge(const string&, const string&); // removes the edge between two vertices, if it exists.
        
        /* test8 */
        void remove_vertex(const string&); // delete the given vertex from the graph -- note that, all incident edges of the vertex should be deleted as well.

        /* test9 */
		vector<string> depth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a depth-first traversal from the given vertex.
		
        /* test10 */
        vector<string> breadth_first_traversal(const string&); // returns a vector of all the vertices in the visiting order of a breadth-first traversal from the given vertex.
        
        /* test11 */
		bool contain_cycles(); // check if the graph contains any cycle -- returns true if there exists a path from a vertex to itself; otherwise, return false.
        
        /* test12 */
		Graph<T> minimum_spanning_tree(); // returns a spanning tree of the graph -- the returned tree is preferably a minimum spanning tree.
		
};

/* test1 */

template <typename T>
Graph<T>::Graph() {}

template <typename T>
Graph<T>::~Graph() {}


template <typename T>
size_t Graph<T>::num_vertices() {
    return adjacency_list.size(); //Returns the size of the adjacency_list map keys which are the all vectors in the graph
}

template <typename T>
size_t Graph<T>::num_edges() {
    return count_edge; //Returns the number of edges in the graph
}

/* test2 */

template <typename T>
void Graph<T>::add_vertex(const string& u) {
    adjacency_list[u] = map<string, T>(); //For key u in the adjacency list, set the value to an empty map to add vertex
}

template <typename T>
bool Graph<T>::contains(const string& u) {
    for (auto itr = adjacency_list.begin(); itr != adjacency_list.end(); itr++) { //Iterate through all the vectors in the adjacency_list
        if(itr->first == u){ //If the vector is equal the the vector u, return true. Otherwise return false  
            return true;
        }
    }
    return false;
}

/* test3 */

template <typename T>
vector<string> Graph<T>::get_vertices() {
    vector<string> vert; //Initialise an empty list to store all the found vertices
    for (auto itr = adjacency_list.begin(); itr != adjacency_list.end(); itr++) { //Iterate through all the vectors in the adjacency_list
        vert.push_back(itr->first); //Add the vertex to the list vert
    }
    return vert; //Return all the found vertices as a list
}

/* test4 */

template <typename T>
void Graph<T>::add_edge(const string& u, const string& v, const T& weight) {
    adjacency_list[u][v] = weight; //Sets edge weight for vector "u" to "v"
    adjacency_list[v][u] = weight; //Sets edge weight for vector "v" to "u"
    count_edge++; //Adds count to edge
}

template <typename T>
bool Graph<T>::adjacent(const string& u, const string& v) {
    for (auto itr = adjacency_list[u].begin(); itr != adjacency_list[u].end(); itr++) { //Iterate through all the adjacent vectors in adjacency_list with vertex u
            if(itr->first == v){ //If the vertex adjacent to u is equal to v, return true
                return adjacency_list[u][v];
            } 
    }
    return false;
}

/* test5 */

template <typename T>
vector<pair<string,string>> Graph<T>::get_edges() {
    vector<string> visitedvert; //Initialise a list to contain all the vertices with edges that have already been added
    vector<pair<string,string>> edge; //Initialise a list of pairs to contain all the edges to return
    for (auto itr = adjacency_list.begin(); itr != adjacency_list.end(); itr++) { //Iterate through all the vectices in the adjacency_list
        for (auto ptr = adjacency_list[itr->first].begin(); ptr != adjacency_list[itr->first].end(); ptr++) { //Iterate through all the adjacent vertices for each vertex in adjacency_list
            if(find(visitedvert.begin(), visitedvert.end(), ptr->first) == visitedvert.end()){ //If adjacent key is not found in the vertices that have been added add the edge to the edge list
                edge.push_back(std::make_pair(itr->first , ptr->first));
            }   
        }       
        visitedvert.push_back(itr->first); //Add the visited vertex to vert
    }
    return edge;
}

/* test6 */

template <typename T>
vector<string> Graph<T>::get_neighbours(const string& u) {
    vector<string> neighbour; //Initialise a list to contain all the neibouring vertices to return 
    for (auto itr = adjacency_list[u].begin(); itr != adjacency_list[u].end(); itr++) { //Iterate through adjacency_list for vertex u for each adjacent vertex
        neighbour.push_back(itr->first); //Add adjacent vertex to vert
    }
    return neighbour;
}

template <typename T>
size_t Graph<T>::degree(const string& u) {
    return adjacency_list[u].size(); //Return the size of all adjacent vertices for vertex u
}

/* test7 */

template <typename T>
void Graph<T>::remove_edge(const string& u, const string& v) {
    if(adjacency_list[u].erase(v)){ //If adjacent vertex v is successfully erased from vertex u, reduce the count of count_edge by 1
	    count_edge--;                   
    }
    adjacency_list[v].erase(u); //Erase adjacent vertex u from vertex v
}

/* test8 */

template <typename T>
void Graph<T>::remove_vertex(const string& u) {
    for (auto itr = adjacency_list[u].begin(); itr != adjacency_list[u].end(); itr++) { //Iterate through all the adjacent vertices of vertex u
        adjacency_list[itr->first].erase(u); //For that adjacent vertex, erase vetex u as an adjacent vertex
        count_edge--; //Reduce count_edge by 1                        
    }
    adjacency_list.erase(u); //Erase the vertex u from the adjacency_list
}

/* test9 */

template <typename T>
vector<string> Graph<T>::depth_first_traversal(const string& u) {
    vector<string> visited; //Initialise a list for visited vectors
    stack<string> stack; //Initialise a stack to store the vectors that are currently being visited
    stack.push(u); //Add vector u to the stack as first vector
    while (!stack.empty()){
        string current = stack.top(); //Make current the top of the stack
        stack.pop(); //Remove top element from the stack
        if(find(visited.begin(), visited.end(), current) == visited.end()){ //Check whether the current vertex being visited is in the visited list
            visited.push_back(current); //Add current vertex to the visited list
            for (auto itr = adjacency_list[current].begin(); itr != adjacency_list[current].end(); itr++) { //For each adjacent vertex for current
                stack.push(itr->first); //Push each element into the stack
            }
        }
    }
    return visited; 
}

/* test10 */

template <typename T>
vector<string> Graph<T>::breadth_first_traversal(const string& u) {
    vector<string> visited; //Initialise a list for visited vectors
    queue<string> queue; //Initialise a queue to store the elements to visit
    queue.push(u); //Add vector u to queue as first vector
    while (!queue.empty()){
        string current = queue.front(); //Make current the top of the queue
        queue.pop(); //Remove that element from the queue
        if(find(visited.begin(), visited.end(), current) == visited.end()){ //Check whether the current vertex being visited is in the visited list
            visited.push_back(current); //Add current vertex to the visited list
            for (auto itr = adjacency_list[current].begin(); itr != adjacency_list[current].end(); itr++) { //For each adjacent vertex for current
                queue.push(itr->first); //Push each queue into the stack
            }
        }
    }
    return visited;
}
/* test11 */

template <typename T>
bool Graph<T>::contain_cycles() {
    vector<string> visited; //Make a list for the visited vectors
    vector<pair<string,string>> queue; //Make a list of pairs of strings to store the vertices and the parents that are being searched through
    queue.push_back(make_pair(adjacency_list.begin()->first,"0")); //Add the initial parent vertex to the queue
    while (!queue.empty()){
        string current = queue.back().first; //Make current the vertex of the pair at the back of the queue  
        string parent = queue.back().second; //Make parent the parent of the pair at the back of the queue
        queue.pop_back(); //Remove the last element of the queue
        visited.push_back(current); //Add current vertex to the visited list
        for (auto itr = adjacency_list[current].begin(); itr != adjacency_list[current].end(); itr++) { //Iterate through each adjacent vertex for current
                if((find(visited.begin(), visited.end(),itr->first)==visited.end())){ //Checks if the adjacent vertex is in the visited list
                    queue.push_back(make_pair(itr->first,current)); //Add the pair of the adjacent vertex and the current vertex to the queue
                }
                else if (itr->first != parent){ //Checks if the cycle is a cycle of itself
                    return true; // Return true since there is a cycle
                }
        }     
    }
    return false;
}

/* test12 */

template <typename T>
Graph<T> Graph<T>::minimum_spanning_tree() {
    Graph<T> mst; //Initialise a new graph 
    vector<string> visited; //Initialise a list to store all the visited vectors 
    mst.add_vertex(adjacency_list.begin()->first); //Add the first vertex to the msp graph 
    visited.push_back(adjacency_list.begin()->first); //Add the first vertex to the visited list
    while(mst.num_vertices() < num_vertices()){ 
        int lowest = INT_MAX; //Make the lowest integer the biggest possible number
        pair<string,string> edgelink; //Initialise a pair of strings for the edges between vertices
        for(int i=0; i < visited.size(); i++){ //Iterate through each vertex in visited
            for (auto ptr = adjacency_list[visited[i]].begin(); ptr != adjacency_list[visited[i]].end(); ptr++){ //Iterate through each adjacent vertex in adjacency_list[i]
                if((find(visited.begin(), visited.end(),ptr->first) ==visited.end()) && (ptr->second < lowest) ){ //Check if visited has adjacent vertex and whether weight is smaller than lowest
                    lowest = ptr->second; //Set lowest to the weight between visited[i] and ptr->first
                    edgelink = make_pair(visited[i],ptr->first); //Set link to visited[i] and ptr->first
                }    
            }  
        }  
        visited.push_back(edgelink.second); //Add the adjacent vertex of current to visited
        mst.add_edge(edgelink.first, edgelink.second, adjacency_list[edgelink.first][edgelink.second]); //Add an edge for msp between link.first[visited[i](Vertex of current)] and link.second[ptr->first(Adjacent vertex of current)]
    }   
    return mst;
}