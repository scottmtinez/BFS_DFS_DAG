#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Edge.h"
using namespace std;

#ifndef GRAPH_H_
#define GRAPH_H_

class Graph {

public:

	int numVertices;
	int *outDegree;
	vector<vector<Edge> > adjList;

	Graph() {
		numVertices = 0;
		outDegree = nullptr;
	}

	~Graph() {
		delete[] outDegree;
	}

	void readUnweightedGraph(string &filePath) {
		ifstream fileReader(filePath, ios::in);

		fileReader >> numVertices;
		adjList.reserve(numVertices);
		outDegree = new int[numVertices];

		for (int i = 0; i < numVertices; i++) {
			int numEdges;
			fileReader >> numEdges;
			outDegree[i] = numEdges;
			vector<Edge> outEdges;
			outEdges.reserve(numEdges);
			for (int j = 0; j < numEdges; j++) {
				int dest;
				fileReader >> dest;
				Edge edge(i, dest, 1);
				outEdges.push_back(edge);
			}
			adjList.push_back(outEdges);
		}
		fileReader.close();
	}

	void readWeightedGraph(string filePath) {
		ifstream fileReader(filePath, ios::in);

		fileReader >> numVertices;
		adjList.reserve(numVertices);
		outDegree = new int[numVertices];

		for (int i = 0; i < numVertices; i++) {
			int numEdges;
			fileReader >> numEdges;
			outDegree[i] = numEdges;
			vector<Edge> outEdges;
			outEdges.reserve(numEdges);
			for (int j = 0; j < numEdges; j++) {
				int dest, weight;
				fileReader >> dest;
				fileReader >> weight;
				Edge edge(i, dest, weight);
				outEdges.push_back(edge);
			}
			adjList.push_back(outEdges);
		}
		fileReader.close();
	}
};

#endif /* GRAPH_H_ */
