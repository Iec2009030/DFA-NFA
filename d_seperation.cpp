/* 
 * Probablistic Graphical Model Class 2017,
 * Program For Checking the d-Seperation for 
 * for a given Graph G, SOurce node X, and set
 * of Evidence Variable Z.
 * author @Nitin Bansal UIN: 425007158
 */


#include <iostream>
#include <list>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

/*Defining Direction*/
#define UP "UP"
#define DOWN "DOWN"

/* Definition of The Graph Used */

class Graph{
	public:
	int V;                        // No. of vertices
	list<int> *children;          // Pointer to an array containing adjacency lists for children
	list<int> *parent;	      // Pointer to an array containing adjacency lists for parents
	Graph(int V);                 // Constructor
	void addEdge(int v, int w);   // function to add an edge to graph
};


Graph::Graph(int V){
	this->V = V;
	children  = new list<int>[V];
	parent  = new list<int>[V];
	
}

void Graph::addEdge(int v, int w){
	children[v].push_back(w);     // Add w to v’s list.
	parent[w].push_back(v);       // Add v to w's list.
}



/* Function to Search a Given Element in a List */

bool isPresent(int temp, list<int> A){
	if (A.empty())
		return false;
	else {
		list<int> :: iterator it;
        	it = find(A.begin(),A.end(),temp);
        if (it == A.end())
                return false;
	else
		return true;
	}
}

/* Function to Search a Given Element in a List of Pair */

bool isPresentpair( pair<int,string> temp, list<pair<int,string> > A){
        if (A.empty())
                return false;
        else {
                list<pair<int,string> > :: iterator it;
                it = find(A.begin(),A.end(),temp);
        if (it == A.end())
                return false;
        else
                return true;
        }
}

/*Printing Reachable Nodes */

void reachable_nodes(list<int> R){
	R.sort();
	R.unique();
	list<int> :: iterator it2;
	cout << "Reachable Nodes for Given Graph: ";
	for (it2= R.begin(); it2!=R.end(); it2++){
		cout << *it2 << " ";
	}

	return;
}

/*Priniting D-seperated Nodes */
void d_seperated_nodes(list<int> R, list<int> Z,Graph G){
	vector<int> all_nodes;
	list<int> :: iterator it1;
	list<int> :: iterator it2;
	
	cout << "D-Seperated Nodes for Given Graph: ";
	for (int i =0; i< G.V; i++)
		all_nodes.push_back(i);
	for (int i = 0; i<G.V; i++){
		it1 = find(R.begin(), R.end(), all_nodes[i]);
		it2 = find(Z.begin(), Z.end(), all_nodes[i]);
		if (it1 == R.end() && it2 == Z.end())
			cout << all_nodes[i] << " ";
	}
	cout << endl;
	cout<<"Observed Nodes : ";
	for (it2 = Z.begin(); it2!=Z.end(); it2++)
		cout << *it2 << " ";
	return;
}
	


/* Main Function used for d_seperation 		
 * Consist of the Graph G, source node X
 * and Evidence Provided Z 
 */

void d_seperation(Graph G, int X, list<int> Z){
	//Implemeting Phase ONE:

	// Insert all ancestors of Z into A
	list<int> L(Z.begin(), Z.end());
	list<int> A;
	list<int>::iterator i;

	while(!L.empty()){
		int temp = L.front();
		L.pop_front();
		if (!isPresent(temp, A)) {
			for (i = G.parent[temp].begin(); i!= G.parent[temp].end();i++)
				L.push_back(*i);
			L.unique();
		}
		A.push_back(temp);
	}
	A.unique();
	

	// Implementing Phase TWO:

	// Traverse Active Trails starting from X
	// Using a pair to represent the Node and Direction
	// UP and DOWN.

	list<pair<int,string> > L1; // Including the Nodes and Direction
	list<pair<int,string> > V;  // Node Direction Visited Status
	pair<int,string> temp1;
	list<int> R;                // Nodes Reachable Via Active Trail

	temp1 = make_pair(X, UP);
	L1.push_back(temp1);
	
	while (!L1.empty()){
		pair<int,string> tmp;
		tmp = L1.front();
		L1.pop_front();
		if (!isPresentpair(tmp, V)){
			if(!isPresent(tmp.first, Z)){
				//Y is Rechanble	
				R.push_back(tmp.first);
			}
			//Mark (Y,d) as visited
			V.push_back(tmp);
			V.unique();
			//Trail up through Y active if Y not in Z
			if (tmp.second == UP && !isPresent(tmp.first, Z)){
				int curr = tmp.first;
				// Y's Parent to be visited from bottom
				for (i = G.parent[curr].begin(); i!= G.parent[curr].end();i++){
					pair<int,string> tmp1;
					tmp1 = make_pair(*i, UP);
					L1.push_back(tmp1);
				}
				L1.unique();
				// Y's Children to be visited from top
				for (i = G.children[curr].begin(); i!= G.children[curr].end();i++){
                                        pair<int,string> tmp1;
                                        tmp1 = make_pair(*i, DOWN);
                                        L1.push_back(tmp1);
                                }
				L1.unique();
		
			} // Trail down through Y
			else if ( tmp.second == DOWN) {
				int curr = tmp.first;
				if (!isPresent(tmp.first, Z)){
					//Downward trail to Y's children are active
					// Y's Children to be visited from top
					for (i = G.children[curr].begin(); i!= G.children[curr].end();i++){
						pair<int,string> tmp1;
						tmp1 = make_pair(*i, DOWN);
						L1.push_back(tmp1);
					}
					L1.unique();
				}

				//V-strucutre trails are active
				if (isPresent(tmp.first, A)) {
					// Y's Parent to be visited from bottom
					for (i = G.parent[curr].begin(); i!= G.parent[curr].end();i++){
						pair<int,string> tmp1;
						tmp1 = make_pair(*i, UP);
						L1.push_back(tmp1);
					}
					L1.unique();
				}
			}
		}
	}
	//Printing the source Node
	cout << "Source Node : ";
	cout << X <<endl; 
	//Printing the Reachable Nodes
	reachable_nodes(R);
	R.sort();
	R.unique();
	cout << endl;

	//Printing D-seperated Nodes
	d_seperated_nodes(R,Z,G);
		
	return;
}


				


int main()
{
	Graph g(13);
	list<int> Z;
	
	//Adding the Edge According to Graph
	g.addEdge(0,2);
	g.addEdge(1,2);
	g.addEdge(2,4);
	g.addEdge(2,3);
	g.addEdge(3,5);
	g.addEdge(4,5);
	g.addEdge(4,6);
	g.addEdge(7,6);
	g.addEdge(6,8);
	g.addEdge(8,9);
	g.addEdge(10,8);
	g.addEdge(10,11);
	g.addEdge(11,12);
	
	//Evidence Variable Building
	Z.push_back(9);
	//Z.push_back(6);

	//Main Function Execution
	d_seperation(g, 1, Z);

	cout <<endl<<endl; 

	return 0;
}


//Not Required!!!!
//Extra Information Code
//Code For Printing Child Parent relationship

/*
	        for(int i =0; i<4; i++) {
                list<int> :: iterator it;
                cout << "Children of Index:  " << i << endl;
                for (it = g.children[i].begin(); it!= g.children[i].end(); it++)
                        cout << *(it) << " ";

                cout << endl;

                cout << "Parent of Index: "<< i << endl;
                for (it = g.parent[i].begin(); it!= g.parent[i].end(); it++)
                        cout<< *(it) << " ";
        }
*/

/* 	Comment Out this to Print Ancestors 
        cout << "Printing Ancestors" <<endl;
        list<int>::iterator it1;
        for (it1 = A.begin(); it1!= A.end(); it1++)
                cout << *(it1) << " ";
        cout << endl;

*/
	
