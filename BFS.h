#include <iostream>
#include <climits>
#include <list>
#include "Graph.h"
using namespace std;

#ifndef BFS_H_
#define BFS_H_

class BFS: public Graph {

public:

	int *level;

	BFS(string &fileName) {
		readUnweightedGraph(fileName);
        level = nullptr;
	}

	~BFS() {
		delete[] level;
	}

private:

	void helpBFS(int s) { // complete this method
    //Create an integer queue vertexQ.
      list<int> vertexQ;
    
    //Enqueue s to vertexQ.
      vertexQ.push_back(s);
    
    //Set level[s] = 0.
      level[s] = 0;
    
    //while (vertexQ's size > 0), do the following:
      while(vertexQ.size() > 0)
        {
          //let v be the vertex obtained by dequeueing vertexQ
            int v = vertexQ.front();
            vertexQ.pop_front();
          
          //for (i = 0 to i < outDegree[v]), do the following:
            for(int i = 0; i < outDegree[v]; i++)
              {
                //let adjEdge be the ith outgoing edge of v
                  Edge &adjEdge = adjList.at(v).at(i);
                  
                //let w be the destination of adjEdge
                  int w = adjEdge.dest;
                
                //if (level[w] equals ∞) then
                  if(level[w] == INT_MAX)
                    {
                      //set level[w] to level[v] + 1
                        level[w] = level[v] + 1;
                        
                      //enqueue w to vertexQ
                        vertexQ.push_back(w);
                    }
              }

        }
	}

public:

	void executeBFS(int s) { // complete this method
    //Allocate numVertices cells for the level[ ] array.
      level = new int [numVertices];

    //Use a loop to initialize all cells of level[ ] to ∞.
      for(int i = 0; i < numVertices; i++)
        {
            level[i] = INT_MAX;  
        }

    //Call the BFS Helper method with s as argument
      helpBFS(s);
	}

	int countComponents() { // complete this method
    //Allocate numVertices cells for the level[ ] array.
      level = new int [numVertices];

    //Use a loop to initialize all cells of level[ ] to ∞.
      for(int i = 0; i < numVertices; i++)
        {
          level[i] = INT_MAX;
        }
    
    //Initialize a counter to 0.
      int counter = 0;
    
    //for (i = 0 to i < numVertices), do the following:
      for(int i = 0; i < numVertices; i++)
        {
          if(level[i] == INT_MAX)
            {
              helpBFS(i);
              counter += 1;
            }
        }

      return counter;      
	}
};

#endif /* BFS_H_ */
