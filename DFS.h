#include <iostream>
#include <climits>
#include <list>
using namespace std;

#ifndef DFS_H_
#define DFS_H_

class DFS: public Graph {

private:

	bool *closed;

public:

	int *level;

	DFS(string &fileName) {
		readUnweightedGraph(fileName);
        level = nullptr;
        closed = nullptr;
	}

	~DFS() {
		delete[] level;
		delete[] closed;
	}

private:

	void helpDFS(int v) { // complete this method; this is the DFS helper function
    //Set closed[v] to true
      closed[v] = true;
    
    //For each adjacent edge adjEdge of v, do the following:
      for(int i = 0; i < outDegree[v]; i++)
        {
          //let w be the destination of adjEdge
            Edge &adjEdge = adjList.at(v).at(i);
            int w = adjEdge.dest; 
          
          //if w is not closed, do the following:
            if(closed[w] == false)
              {
                //set level[w] = level[v] + 1
                  level[w] = level[v] + 1;

                //recursively call DFS Helper on w
                  helpDFS(w);
              } 

        }

	}
    
public:
    
    void executeDFS(int s) { // complete this method; this is the main DFS function
      //Allocate numVertices cells for the level[ ] and closed[ ] arrays.
        level = new int [numVertices];
        closed = new bool [numVertices];

      //Use a loop to initialize each cell of closed[ ] to false and each cell of level[ ] to ∞.
        for(int i = 0; i < numVertices; i++)
          {
            closed[i] = false;
            level[i] = INT_MAX;
          }

      //Set level[s] to 0.
        level[s] = 0;

      //Call DFS Helper method with s as argument.
        helpDFS(s);
    }
    
    bool **computeTransitiveClosure() { // complete this method
      //Create a two-dimensional boolean matrix M that has numV ertices many rows.
        bool **M = new bool*[numVertices];

      //for (i = 0 to i < numVertices), do the following:
        for(int i = 0; i< numVertices; i++)
          {
            //call DFS main method with i as argument
              executeDFS(i);
              
            //set M[i] to closed
              M[i] = closed;
          }
      return M;
    }
};

#endif /* DFS_H_ */
