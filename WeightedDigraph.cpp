/**
 * A definition of a weighted digraph
 * Written by James Daly
 * Completed by Alex Bergman
 */

#include "WeightedDigraph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <vector>
#include <list>
#include <utility>

using namespace std;

/**
 * Constructs the digraph from a file.
 * You may add any additional construction to this section.
 */
WeightedDigraph::WeightedDigraph(const string& filename) : numVertices(0), numArcs(0) {
	ifstream in(filename);
	if(!in.is_open()) {
		cerr << "cannot open file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	string line;
	getline(in, line);
	istringstream vertexStream(line);
	vertexStream >> numVertices;
	
	// TODO : You can initialize your data structure here.
	arcs.resize(numVertices);
	while(getline(in,line)) {
		istringstream iss(line);
		int u, v;
		float weight;
		iss >> u >> v >> weight;
		InsertArc(u, v, weight);
	}
}

/**
 * Destructor
 * You can do any needed cleanup here.
 */
WeightedDigraph::~WeightedDigraph() {
	// Intentionally left empty
	// You may do any needed cleanup here
}

/**
 * Inserts a weighted arc into the digraph.
 * This is the sole mutator of this class and it is private
 * so the digraph is immutable once created.
 */
void WeightedDigraph::InsertArc(int from, int to, double weight) {
	// TODO
	arcs[from].push_back(make_pair(to, weight));
	numArcs++;
}

/**
 * Finds the number of arcs leading out of the given vertex
 */
int WeightedDigraph::GetOutDegree(int vertex) const { 
	return arcs[vertex].size();
}

/**
 * Finds the weight of the arc between the two vertices
 * Returns infinity if there is no such arc
 */
double WeightedDigraph::GetArcWeight(int from, int to) const {
	double weight=0;
	bool found = false;
	for(auto p : arcs[from]){
		if(p.first == to){
			weight = p.second;
			found = true;
		}
	}
	if(found) return weight;
	else return numeric_limits<double>::infinity();
}

/**
 * Finds the sum weight of the given path.
 * Returns infinity if the path is broken.
 */
double WeightedDigraph::GetPathWeight(const list<int> & path) const {
	int from = -1;
	int weight = 0;
	double sum = 0;
	for(int i : path ){
		if(from >= 0){
			weight = GetArcWeight(from, i);
			if(weight == numeric_limits<double>::infinity())
				return numeric_limits<double>::infinity();
			else
				sum += weight;
		}
		from = i;
	}

	return sum;
}

/**
 * Checks whether an arc exists between two vertices.
 */
bool WeightedDigraph::AreConnected(int from, int to) const {
	bool connected = false;
	for (auto p : arcs[from]){
		if(p.first == to){ 
			connected = true;
			break;
		}
	}
	return connected;
}

bool WeightedDigraph::DoesPathExistRecur(int from, int to, list<int>& visited) const{
	visited.push_back(from);
	bool found_path = false;
	for(pair<int, double> p : arcs[from]){
		if(find(visited.begin(), visited.end(), p.first) == visited.end()){
			if(p.first == to) return true;
			found_path = DoesPathExistRecur(p.first, to, visited);
			if(found_path) break;
		}
	}
	return found_path;
}

/**
 * Determines whether a path between the two vertices exists.
 */
bool WeightedDigraph::DoesPathExist(int from, int to) const {
	list<int> visited;
	return DoesPathExistRecur(from, to, visited);
}

/**
 * Checks whether the given path goes over existing arcs.
 */
bool WeightedDigraph::IsPathValid(const list<int> & path) const {
	double path_weight = GetPathWeight(path);
	if(path_weight == numeric_limits<double>::infinity())
		return false;
	else return true;
}


/**
 * Finds a path of minimum weight between the two nodes.
 * The behavior is undefined if no such path exists
 * (you may assume that such a path does exist).
 */
list<int> WeightedDigraph::FindMinimumWeightedPath(int from, int to) const {
	
	vector<pair<int,double>> dists;
	dists.resize(numVertices);
	list<int> unvisited;

	for(int i =0; i < numVertices; i++)
		unvisited.push_back(i);
	for(unsigned int i = 0; i < dists.size(); i++){
		dists[i] = make_pair(-1 , numeric_limits<double>::infinity());
	}
	dists[from] = make_pair(from,0);

	int current = from;
	int v_least = -1, v_least_dist = numeric_limits<double>::infinity();
	while(1){
		unvisited.remove(current);
		if(current != to){
			for(pair<int, double> pair : arcs[current]){
				if(find(unvisited.begin(), unvisited.end(), pair.first) != unvisited.end()){
					if(dists[pair.first].second > (dists[current].second + pair.second) ){
						dists[pair.first].second = dists[current].second + pair.second;
						dists[pair.first].first = current;
					}
				}
			}
			v_least_dist = numeric_limits<double>::infinity();
			for(int i : unvisited){
				if(dists[i].second < v_least_dist){
					v_least_dist = dists[i].second;
					v_least = i;
				}
			}
			current = v_least;
		}
		else break;
	}

	list<int> path;
	path.push_front(current);
	while (current != from){
		path.push_front(dists[current].first);
		current = dists[current].first;
	}


	return path;
}
