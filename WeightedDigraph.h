/**
 * A definition of a weighted digraph
 * Note that the digraph is immutable once created
 *
 * Stub Written by James Daly
 * Completed by Alex Bergman
 */
 
#ifndef WeightedDigraph_H
#define WeightedDigraph_H

#include <list>
#include <string>
#include <vector>

using namespace std;

class WeightedDigraph {
public:
	WeightedDigraph(const std::string& filename);
	~WeightedDigraph();
	
	WeightedDigraph(const WeightedDigraph&) = delete;
	WeightedDigraph& operator=(const WeightedDigraph&) = delete;
	
	int GetOrder() const { return numVertices; };
	int GetSize() const { return numArcs; };
	
	int GetOutDegree(int vertex) const;
	
	double GetArcWeight(int from, int to) const;
	double GetPathWeight(const std::list<int> & path) const;
	
	bool AreConnected(int from, int to) const;
	bool DoesPathExist(int from, int to) const;
	bool IsPathValid(const std::list<int> & path) const;
	
	std::list<int> FindMinimumWeightedPath(int from, int to) const;
	
private:
	int numVertices;
	int numArcs;
	// Put member data here
	vector<list<pair<int, double>>> arcs;
	
	bool DoesPathExistRecur(int from, int to, list<int>& visited) const;
	void InsertArc(int from, int to, double weight);
};


#endif