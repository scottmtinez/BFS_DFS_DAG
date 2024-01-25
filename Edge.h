#include <iostream>
#include <string>
using namespace std;

#ifndef EDGE_H_
#define EDGE_H_

class Edge {

public:

	int src, dest, weight;

	Edge(int src, int dest, int weight) {
		this->src = src;
		this->dest = dest;
		this->weight = weight;
	}

	Edge(int src, int dest) {
		this->src = src;
		this->dest = dest;
		this->weight = 1;
	}

	string toString() {
		return "<" + std::to_string(src) + ", " + std::to_string(dest) + ", "
				+ std::to_string(weight) + ">";
	}
};

#endif /* EDGE_H_ */
