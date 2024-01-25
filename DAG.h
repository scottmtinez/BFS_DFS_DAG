#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <list>
#include "Graph.h"
using namespace std;

#ifndef DAG_H_
#define DAG_H_

class DAG: public Graph {

private:
  
	int *inDegree;

public:

	int *topoOrder;
	int *distance;

	DAG(string &filePath) {
		readWeightedGraph(filePath);
        inDegree = nullptr;
        topoOrder = nullptr;
        distance = nullptr;
	}

	~DAG() {
		delete[] inDegree;
		delete[] topoOrder;
		delete[] distance;
	}

	void longestPaths(int s) { // complete this method
    //Allocate numVertices cells for the topoOrder[ ], distance[ ], and inDegree[ ] arrays.
      topoOrder = new int [numVertices];
      distance = new int [numVertices];
      inDegree = new int [numVertices];

    //Use a loop to initialize all cells of inDegree[ ] to 0 and all cells of distance[ ] to −∞
      for(int i = 0; i < numVertices; i++)
        {
          inDegree[i] = 0;
          distance[i] = INT_MIN;
        }
    
    //for (i = 0 to i < numVertices), do the following:
      for(int i = 0; i < numVertices; i++)
          {
            //for(j = 0 to j < outDegree[i]), do the following:
              for(int j = 0; j < outDegree[i]; j++)
                {
                  //Let adjEdge be the jth outgoing edge of i. See BFS pseudo-code for syntax.
                    Edge &adjEdge = adjList.at(i).at(j);

                  //increment inDegree[adjEdge's destination] by 1
                    inDegree[adjEdge.dest] += 1;
                }
          }
      
    //Create an integer queue vertexQ
      list<int> vertexQ;
    
    //for (i = 0 to i < numVertices), do the following:
      for(int i = 0; i < numVertices; i++)
        {
          //if (inDegree[i] equals 0),
            if(inDegree[i] == 0)
              {
                //enqueue i into the vertexQ
                  vertexQ.push_back(i);
              }
        }
    
    //Set distance[s] = 0 and initialize an integer variable topoLevel = 0
      distance[s] = 0;
      int topoLevel = 0;
      
    //while (vertexQ's size > 0), do the following:
      while(vertexQ.size() > 0)
        {
          //let v be the vertex obtained by dequeueing vertexQ
            int v = vertexQ.front();
            vertexQ.pop_front();

          //assign topoOrder[topoLevel] = v
            topoOrder[topoLevel] = v;

          //increment topoLevel by 1
            topoLevel += 1;

          //for (j = 0 to j < outDegree[v]), do the following:
            for(int j = 0; j < outDegree[v]; j++)
              {
                //let adjEdge be the jth outgoing edge of the vertex v
                  Edge &adjEdge = adjList.at(v).at(j);

                //let adjVertex be the destination of adjEdge
                  int adjVertex = adjEdge.dest;
                
                //decrement inDegree[adjVertex] by 1
                  inDegree[adjVertex] -= 1;
                
                //if (inDegree[adjVertex] equals 0), then enqueue adjVertex to vertexQ
                  if(inDegree[adjVertex] == 0)
                    {
                      vertexQ.push_back(adjVertex);
                    }

                //if (distance[v] = −∞), do the following:
                  if(distance[v] != INT_MIN)
                    {
                      //let len = distance[v]+ weight of adjEdge
                        int len = distance[v] + adjEdge.weight;

                      //if (len > distance[adjVertex]), set distance[adjVertex] = len
                        if(len > distance[adjVertex])
                          {
                            distance[adjVertex] = len;
                          }
                    }
              }
        }

	}
};

#endif /* DAG_H_ */
