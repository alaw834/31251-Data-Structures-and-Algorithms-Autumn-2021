#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <limits>
#include <utility> 
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

template <typename T>
class Node{ //Node class 
    public: 
        string vertex; 
        T weight; 
        Node *left, *right, *parent;
        Node(const string& u, const T& w);
};

template <typename T>
class BST {
	public:
        Node<T> *root; //Creates pointer towards root
        int count_vertex = 0; 
        int count_edge = 0;
        T count_weight = 0;

        /* test1 */
		BST(); // the contructor function.
		~BST(); // the destructor function.
		size_t num_vertices(); // returns the total number of vertices in the bst.
		size_t num_edges(); // returns the total number of edges in the bst.
        T sum_weight(); // return the total weight of all the vertices in the bst.
        /* test2 */
        void add_vertex(const string&, const T&); // adds a vertex, which has a weight, to the tree -- every vertex uses a string as its unique identifier.
        bool contains(const string&); // checks if a vertex is in the bst -- returns true if the bst contains the given vertex; otherwise, returns false.
        /* test3 */
        vector<string> get_vertices(); // returns a vector of all the vertices in the bst.
        vector< string> get_leaves(); // returns a vector of all the leaves in the bst.
                                     //     Leaves are the vertices that do not have any children in the bst.
        /* test4 */
        bool adjacent(const string&, const string&); // check if there is an edge between the two vertices in the bst -- returns true if the edge exists; otherwise, returns false.
        /* test5 */
        vector<pair<string,string>> get_edges(); // returns a vector of all the edges in the bst -- each edge is represented by a pair of vertices incident to the edge.
        /* test6 */
        vector<string> get_neighbours(const string&); // returns a vector of all the vertices, each of which is directly connected with the given vertex via an edge.
        size_t degree(const string&); // returns the degree of a vertex.
        /* test7 */
		vector<string> preorder_traversal(); // returns a vector of all the vertices in the visiting order of a preorder traversal over the bst.
        /* test8 */
        vector<string> inorder_traversal(); // returns a vector of all the vertices in the visiting order of an inorder traversal over the bst.
        /* test9 */
        vector<string> postorder_traversal(); // returns a vector of all the vertices in the visiting order of a postorder traversal over the bst.
        /* test10 */
        vector<string> breadth_first_traversal(); // returns a vector of all the vertices in the visiting order of a breadth first traversal over the bst.
        /* test11 */
        Node<T>* get_vertex(const string&);
        Node<T>* lowestcommonancestor(Node<T>*, Node<T>*);
        vector<string> path(const string&, const string&); // returns a vector of all the vertices in the path from the first vertex to the second vertex.
                                                            //     A path should include the source and destination vertices at the begining and the end, respectively.
        /* test12 */
        vector<string> path_with_largest_weight(); // returns a path that has the largest weight in the bst.
                                       //    The weight of a path is the sum of the weights of all the vertices (including the source and destination vertices) in the path.
        /* test13 */
        size_t height(); // returns the height of bst. Height of a tree is the number of edges that form the longest path from root to any leaf.
        /* test14 */
        void remove_vertex(const string&); // delete the given vertex from bst -- note that, all incident edges of the vertex should be deleted as well.
};
/* test1 */
template <typename T>
Node<T>::Node(const string& u, const T& w){
    vertex=u; //Assigns u as the vertex of the node
    weight=w; //Assigns w as the weight of the node
    left = right = NULL; //Assigns NULL to the pointers of potential children for the node
}

template <typename T>
BST<T>::BST(){
    root = NULL; 
}

template <typename T>
BST<T>::~BST() {}

template <typename T>
size_t BST<T>::num_vertices() {
    return count_vertex; //Return the number of vertices in the tree
}

template <typename T>
size_t BST<T>::num_edges() {
    return count_edge; //Return the number of edges in the tree
}

template <typename T>
T BST<T>::sum_weight() {
    return count_weight; //Return the weight of the tree 
}
/* test2 */
template <typename T>
void BST<T>::add_vertex(const string& u, const T& w) {  
    Node<T> *toinsert = new Node(u,w); //Assign the new vertex to pointer "toinsert"
    Node<T> *visiting = root; //Assign the root of the tree to visiting 
    Node<T> *prev; //Initialise a pointer for previous nodes 

    while (visiting){ //Visit child vertices until a leaf is visited
        prev = visiting; //Assign the vertex being visited to previous
        if (w < visiting->weight) //If the weight of the vertex to insert is lower than the visiting vertex weight, visit the left vertex
            visiting = visiting->left;
        else // If the weight of vertex to insert it higher than the visiting vertex, visit the right vertex
            visiting = visiting->right; 
    }
    if (!root){ //If root is NULL. Make root the vertex to insert. 
        prev = toinsert; 
        root = prev; 
        count_vertex++;
        count_weight += w;
    }  
    else if (w < prev->weight){ //If weight of vertex to insert is lower than the weight of the leaf, make its left child the vertex to insert
        prev->left = toinsert;
        toinsert->parent = prev;
        count_vertex++;
        count_edge++;
        count_weight += w;
    }
    else{ //If the weight of vertex to insert is higher than the weight of the leaf, make its right child the vertex to insert
        prev->right = toinsert;
        toinsert->parent = prev;
        count_vertex++;
        count_edge++;
        count_weight += w;
    }
}

template <typename T>
bool BST<T>::contains(const string& u) {
    if (root == NULL) 
        return false;
    queue<Node<T>*> queue; //Create a queue with Nodes
    queue.push(root); //Add the root of the tree to the queue
    while(!queue.empty()){ //While there are vertices in the tree to visit 
        Node<T> *visiting = queue.front(); //Assign the front node in the queue to visiting
        queue.pop(); //Delete the front node in queue 
        if(visiting->vertex == u) //I
            return true; 
        if(visiting->left) //If the left child of visiting is not NULL, add it to queue
            queue.push(visiting->left);
        if(visiting->right) //If the right child of visiting is not NULL, add it to queue
            queue.push(visiting->right);
    }
    return false;
}
/* test3 */
template <typename T>
vector<string> BST<T>::get_vertices() {
    return preorder_traversal(); //Get all vertices in the tree by using pre order traversal
}

template <typename T> 
vector<string> BST<T>::get_leaves(){
    vector<string> leaves; //Create a vector to contain all the leaves that are found in the tree
    stack<Node<T>*> stack; //Create a stack to be able to use an implementation of preorder traversal
    stack.push(root); //Push the root of the tree into the stack
    while (!stack.empty()){ 
        struct Node<T>* visiting = stack.top(); //Assign the top of the stack to visiting
        stack.pop(); //Remove the top element of the stack
        if(visiting -> left != NULL) //If visiting has a left child, add it to the stack
            stack.push(visiting->left);
        if(visiting -> right != NULL) //If visiting has a right child, add it to the stack 
            stack.push(visiting->right);
        else if (visiting->left == NULL && visiting->right == NULL) //Otherwise if there are no children, add it to the vector that contains all the leaves
            leaves.push_back(visiting->vertex);
    }
    return leaves;
}
/* test4 */
template <typename T>
bool BST<T>::adjacent(const string& u, const string& v) {
    if (root == NULL)
        return false;
    queue<Node<T>*> queue; //Create a queue with vertices to visit
    queue.push(root); //Add the root of the tree to the queue
    while(!queue.empty()){
        Node<T> *visiting = queue.front(); //Make visitng the front of the queue
        queue.pop(); //Remove the elemenet from the front of the queue
        if(visiting->vertex == u){ //If the visiting vertex is one the the vertices to check adjacency for. Check if its children or parent has the other vertex
           if(visiting->left && visiting->left->vertex == v)
               return true; 
           else if (visiting->right && visiting->right->vertex == v)
               return true;
        }
        if(visiting->vertex == v){//If the visiting vertex is one the the vertices to check adjacency for. Check if its children or parent has the other vertex
           if(visiting->left != NULL && visiting->left->vertex == u)
               return true; 
           else if (visiting->right != NULL && visiting->right->vertex == u)
               return true;
        }
        if(visiting->left) //If visiting has a left child, push that child to the queue 
            queue.push(visiting->left);
        if(visiting->right) //If visiting has a right child, push that child to the queue 
            queue.push(visiting->right);
    }
    return false;
}
/* test5 */
template <typename T>
vector<pair<string,string>> BST<T>::get_edges() {
    vector<pair<string,string>> edges; //Create a vector of a pair of strings to hold the pairs within the tree
    if (root == NULL) 
        return edges;
    queue<Node<T>*> queue; //Create a queue with all the vertices to traverse through 
    queue.push(root); //Push root to the queue 
    while(!queue.empty()){ 
        Node<T> *visiting = queue.front(); //Make visiting the front of the queue 
        queue.pop(); //Remove the front element of the queue
        if(visiting->left){ //If visiting has a left child, add that edge to edges and add the child to the queue
            edges.push_back(make_pair(visiting->vertex,visiting->left->vertex));
            queue.push(visiting->left);
        }
        if(visiting->right){ //If visiting has a right child, add that edge to edges and add the child to the queue
            edges.push_back(make_pair(visiting->vertex,visiting->right->vertex));
            queue.push(visiting->right);
        }
    }
    return edges;
}
/* test6 */
template <typename T>
vector<string> BST<T>::get_neighbours(const string& u) {
    vector<string> neighbours; //Create a vector of strings to hold all the neighbours of the given vertex 
    queue<Node<T>*> queue; //Make a queue to include vertices to visit
    queue.push(root); //Push the root of the tree into the queue
    if (root == NULL)
        return neighbours;
    while(!queue.empty()){
        Node<T> *visiting = queue.front(); //Make visiting the front element in the queue
        queue.pop(); //Remove the front element of the queue
        if(visiting->vertex == u){ //If visiting is the vertex that was passed the the function, add its children vertices and its parent vertices to neighbours
           if(visiting->parent != NULL) 
               neighbours.push_back(visiting->parent->vertex);
           if(visiting->left != NULL)
               neighbours.push_back(visiting->left->vertex); 
           if(visiting->right != NULL)
               neighbours.push_back(visiting->right->vertex); 
        }
        if(visiting->left){ //Add left child node of visiting if it exists
            visiting->left->parent = visiting;
            queue.push(visiting->left); 
        }
        if(visiting->right){ //Add right child node of visiting if it exists
            visiting->right->parent = visiting;
            queue.push(visiting->right);
        }
    }
    return neighbours;
}

template <typename T>
size_t BST<T>::degree(const string& u) {
    return get_neighbours(u).size();
}
/* test7 */
template <typename T>
vector<string> BST<T>::preorder_traversal() {
    vector<string> vectors; //Create a vector of strings to store all the vectors found during traversal 
    if (root == NULL)
        return vectors;
    stack<Node<T>*> stack; //Use stack as it is LIFO and suits preorder traversal
    stack.push(root); //Push the root of the tree into the stack 
    while (stack.empty() == false){
        Node<T>* visiting = stack.top();  //Make visitng the top of the stack
        vectors.push_back(visiting->vertex); //Add the vertex to the vector
        stack.pop(); //Remove the top element of the stack
        if (visiting->right) //If visiting has a right child, add it to stack
            stack.push(visiting->right);
        if (visiting->left) //If visiting has a left child, add it to stack
            stack.push(visiting->left);
    }
    return vectors;
}
/* test8 */
template <typename T>
vector<string> BST<T>::inorder_traversal() {
    vector<string> vectors; //Create a vector to contain the vertices found during traversal
    if (root == NULL)
        return vectors;
    stack<Node<T>*> stack; //Use stack as it is LIFO and suits inorder traversal
    Node<T>* visiting = root; //Make root the initial node to visit
    while (visiting || stack.empty() == false){ //While visiting is not a leaf or the stack is empty 
        while (visiting){ //Make visiting the most left child of the tree
            stack.push(visiting); 
            visiting = visiting->left; 
        }
        visiting = stack.top(); //Visiting becomes the top of the stack 
        stack.pop(); //Remove the top element of the stack
        vectors.push_back(visiting->vertex); //Add the nodes vertex to the vector
        visiting = visiting->right; //Visit becomes the right child
    }
    return vectors;
}
/* test9 */
template <typename T>
vector<string> BST<T>::postorder_traversal() {
    vector<string> vectors; //Create a vector to contain the vertices during traversal
    if (root == NULL)
        return vectors;
    stack<Node<T>*> traversing, postordervertices; //Create two stacks, one for traversing iteratively and one for holding post order vertices
    traversing.push(root); //Push the root of the tree into traversing stack
    Node<T>* visiting; 
    while (!traversing.empty()){
        visiting = traversing.top(); //Make visiting the top of the stack
        traversing.pop(); //Remove the top element of the stack
        postordervertices.push(visiting); //Add visiting to the psotorder stack
        if (visiting->left) //If visitng has a child node on the left, add it to the stack
            traversing.push(visiting->left);
        if (visiting->right) //If visitng has a child node on the right, add it to the stack
            traversing.push(visiting->right);
    }
    while(!postordervertices.empty()){ //Preorder stack should now have the reverse of postorder traversal. While loop will add vertices to vector in right order
        visiting = postordervertices.top();
        postordervertices.pop(); 
        vectors.push_back(visiting->vertex);
    }
    return vectors;
}
/* test10 */
template <typename T>
vector<string> BST<T>::breadth_first_traversal() {
    vector<string> vectors; //Create a vector of strings to contain the vertices found while traversing
    queue<Node<T>*> queue; 
    queue.push(root); //Push root of the tree to the queue
    vectors.push_back(root->vertex); //Add root vertex to the vector
    while(!queue.empty()){ //Implement pre-order traversal pushing back vertices when checking if a child exists 
        Node<T>* visiting = queue.front(); //Make visiting the element in the front of the queue
        queue.pop(); //Remove the front element of the queue 
        if(visiting -> left){ //If visiting has a left child, add it to queue and add its vertex to the vector
            queue.push(visiting->left);
            vectors.push_back(visiting->left->vertex);
        }
        if(visiting -> right){ //If visiting has a right child, add it to queue and add its vertex to the vector
            queue.push(visiting->right);
            vectors.push_back(visiting->right->vertex);
        }
    }
    return vectors;
}
/* test11 */
template <typename T>
Node<T>* BST<T>::get_vertex(const string& u) { //Helper function using pre-order traversal to return a node with vertex that was passed to it
    stack<Node<T>*> stack; 
    stack.push(root);
    while(!stack.empty()){
        Node<T> *temp = stack.top(); 
        stack.pop(); 
        if(temp->vertex == u)
            return temp; 
        if(temp->right != NULL)
            stack.push(temp->right);
        if(temp->left != NULL)
            stack.push(temp->left);
    }
    return NULL;
}

template <typename T>
Node<T>* BST<T>::lowestcommonancestor(Node<T>* n1, Node<T>* n2){ //Helper function to find the lowest common ancestor between two vertices
    if (!root)
        return NULL;
    Node<T>* visiting = root; 
    while (visiting){ //While visiting is not NULL
        if (visiting->weight > max(n1->weight,n2->weight)) //Check if the vertex being visited is higher than the max weight of n1 and n2
            visiting = visiting->left;  //If weight is higher than either n1 or n2, traverse left
        else if(visiting->weight < min(n1->weight, n2->weight)) //If weight is lower than n1 or n2, traverse right
            visiting = visiting -> right; 
        else
            return visiting;
    }
    return NULL;
}

template <typename T>
vector<string> BST<T>::path(const string& u, const string& v){
    vector<string> path1, path2; //Create two vectors to store a 
    Node<T> *source_node, *destination_node; //Initialise pointers for the source node and the destination node
    if(get_vertex(u)) //If vertex u exists, let source node be that vertex
        source_node = get_vertex(u);
    if(get_vertex(v)) //If vertex v exists, let destination node be that vertex
        destination_node = get_vertex(v);
    while(source_node->vertex != lowestcommonancestor(source_node,destination_node)->vertex){ //Keep traversing and adding the parents of the 
                                                                                              //source vertex until the lowest common ancestor of both vertices is reached
        if(source_node->parent){
            path1.push_back(source_node->vertex);
            source_node = source_node->parent; 
        }
    }
    path1.push_back(lowestcommonancestor(source_node,destination_node)->vertex); //Add the lowest common ancestor of both vertices to path vector
    while(destination_node->vertex != lowestcommonancestor(source_node,destination_node)->vertex){ //Keep traversing and adding the parents of the 
                                                                                                   //source vertex until the lowest common ancestor of both vertices is reached
        if(destination_node->parent){
            path2.push_back(destination_node->vertex);
            destination_node = destination_node->parent; 
        }
    }
    reverse(path2.begin(),path2.end()); //Reverse the path of the second pass of the lcs. 
    copy(path2.begin(),path2.end(), back_inserter(path1)); //Appends path 2 into path 1 for the final path
    return path1;
}
/* test12 */
template <typename T>
vector<string> BST<T>::path_with_largest_weight(){
    vector<string> currentpath, heaviestpath, leaves, vertices; //Create vector to store the path being traversed, the heaviest path,
                                                                //the leaves in the tree and the vertices in the tree
    T current_path_sum, heaviest_path_sum; //Create T to hold the current path weight and the heaviest path weight
    vertices = get_vertices(); //Get all the vertices that exist in the tree
    leaves = get_leaves(); //Get all the leaves that exist in the tree
    heaviest_path_sum = INT_MIN; //Let heaviest path sum be the lowest number possible 
    for(auto source: vertices){ 
        for(auto leaf: leaves){ //Iterate throuh each leaf for each vertex
            current_path_sum=0; //Initalise the count for the to be path
            currentpath = path(source,leaf); //Find the path between vertex and leaf
            for(auto path: currentpath){ // For each vertex in the path, get the weight and it for the total weight of path
                current_path_sum += get_vertex(path)->weight;
                if(current_path_sum>heaviest_path_sum){ //If the path weight being traversed is heavier than "heaviest path sum"
                    heaviest_path_sum = current_path_sum; //Let the current path sum be the "heaviest path sum"
                    heaviestpath = currentpath;
                }
            }
        }
    }
    return heaviestpath;
}
/* test13 */
template <typename T>
size_t BST<T>::height() {
    if (root == NULL)
        return 0; 
    queue<Node<T>*> queue; //Create a queue to traverse tree
    queue.push(root); //Push root of tree into the queue
    int height = -1; //Initialise height count
    while (true){ 
        int nodeCount = queue.size();
        if (nodeCount == 0)
            return height;
        height++;
        while (nodeCount > 0){ //Keep going down in the tree until visiting hits NULL and queue is 0. Which will then return height 
            Node<T>* visiting = queue.front(); 
            queue.pop();
            if(visiting->left != NULL)
                queue.push(visiting->left);
            if (visiting->right != NULL)
                queue.push(visiting->right);
            nodeCount--;
        }
    }
}
/* test14 */
template <typename T>
void BST<T>::remove_vertex(const string& u) {
    Node<T>* visiting = root; 
    Node<T>* prev = NULL; 
    Node<T>* nodetodelete = get_vertex(u);
    while (visiting != NULL && visiting->vertex != u){ 
        prev = visiting; 
        if (nodetodelete->weight < visiting->weight)
            visiting = visiting->left;
        else
            visiting = visiting->right; 
    }
    if (!visiting->left || !visiting->right){ //Check if node that must be deleted has one child
        Node<T>* replacementnode; //Node the will replace the node to be deleted
        if (!visiting->left) //If there is a right child on the node to delte, make replacementnode that vertex
                             //Otherwise make replacementnode the left child
            replacementnode = visiting->right;
        else
            replacementnode = visiting->left;
        if (visiting == prev->left) //Check if node to be delete is prevs left child, replace it with replacementnode
            prev->left = replacementnode; 
        else //Otherwise replace right child with replacement node
            prev->right = replacementnode; 
        count_weight -= visiting->weight;
        count_edge--;
        free(visiting); //Free memory from the node to be deleted
    }
    else{ //Otherwise the node to delete has two children
        Node<T>* parent = NULL; //Parent of inorder successor node
        Node<T>* inordersuccessor = visiting->right; 
        while (inordersuccessor->left){ //Find the inorder successor node
            parent = inordersuccessor;
            inordersuccessor = inordersuccessor->left;
        }
        if (parent) //Checks if parent is the current node 
            parent->left = inordersuccessor->right; //If it isnt, make left child of parent the right child of inorder successor node
        else
            visiting->right = inordersuccessor->right; 

        visiting->vertex = inordersuccessor->vertex;
        count_weight -= visiting->weight;
        count_edge--;
        free(inordersuccessor);
    }
}