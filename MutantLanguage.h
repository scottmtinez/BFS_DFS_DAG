#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Graph.h"
using namespace std;

#ifndef MUTANTLANGUAGE_H_
#define MUTANTLANGUAGE_H_

class MutantLanguage: public Graph {

	string *words;
	int numWords;
	int *inDegree;


public:

	MutantLanguage(string &filePath) {
        words = nullptr;
        inDegree = nullptr;
		readLanguage(filePath);
		makeGraph();
	}

	~MutantLanguage() {
		delete[] words;
		delete[] inDegree;
	}

private:

	void readLanguage(string &filePath) { // complete this method
    //Create an input file stream fileReader on filePath.
      ifstream fileReader(filePath, ios::in);

    //Read the number of distinct characters into the class-variable numVertices.
      fileReader >> numVertices;

    //Now, read the number of words in the language into the class-variable numWords
        fileReader >> numWords;

    //Allocate numWords cells for the class-array words. Note that words is a string array.
        words = new string [numWords];

    //Run a for loop from i = 0 to i < numWords. Within the for-loop, use fileReader to read the line into the array cell words[i].
      for(int i = 0; i < numWords; i++)
        {
          fileReader >> words[i];
        }

    //After the loop, close fileReader.
      fileReader.close();
	}

	void makeGraph() { // complete this method
    //Allocate numVertices cells for outDegree and inDegree arrays.
      outDegree = new int [numVertices];
      inDegree = new int [numVertices];
    
    //Allocate numVertices rows for adjList.
      adjList.reserve(numVertices);
    
    //for (i = 0 to i < numVertices), do the following:
      for(int i = 0; i < numVertices; i++)
        {
          //set outDegree[i] to 0
            outDegree[i] = 0;
            
          //add a blank row to adjList
            adjList.push_back(vector<Edge>());        
        }
      
    //for (i = 0 to i < numWords − 1), do the following:
      for(int i = 0; i < numWords - 1; i++)
        {
          //let currentWord be the word at index i of words[ ] array
            string currentWord = words[i];
          
          //let nextWord be the word at index i + 1 of words[ ] array
            string nextWord = words[i + 1];

          //let minLength be the minimum of the lengths of currentWord and nextWord
            int minLength;
            if(currentWord.length() < nextWord.length())
              {
                minLength = currentWord.length();
              }
            else
              {
                minLength = nextWord.length();
              }
            
          //for (j = 0 to j < minLength), do the following:
            for(int j = 0; j < minLength; j++)
              {
                //let x be the jth character of currentWord
                  char x = currentWord.at(j);
                
                //let y be the jth character of nextWord
                  char y = nextWord.at(j);
                
                //if (x != y), then:
                  if(x != y)
                    {
                      //let int src = x − 97
                        int src = x - 97;

                      //let int dest = y − 97
                        int dest = y - 97;

                      //create an edge e by calling the Edge constructor with arguments src and dest respectively
                        Edge e(src,dest); 

                      //add the edge e to the end of adjList[src]
                        adjList.at(src).push_back(e);
                      
                      //increment outDegree[src] by 1
                        outDegree[src] += 1;
                      
                        break;

                    }
              }

        }

	}

public:

	char* getOrder() { // complete this method
    //Use a loop to initialize all cells of inDegree[ ] to 0
      for(int i = 0; i < numVertices; i++)
        {
          inDegree[i] = 0;
        }
    
    //Create a char array topoOrder[ ] having length numVertices.
      char *topoOrder = new char[numVertices];
      
    //for (i = 0 to i < numVertices), do the following:
      for(int i = 0; i < numVertices; i++)
        {
          //for (j = 0 to j < outDegree[i]), do the following:
            for(int j = 0; j < outDegree[i]; j++)
              {
                //Let adjEdge be the jth outgoing edge of vertex i
                  Edge &adjEdge = adjList.at(i).at(j);

                //increment inDegree[adjEdge's destination] by 1
                  inDegree[adjEdge.dest]++;             
              }
        }
    
    //Create an integer queue vertexQ.
      list<int> vertexQ;
    
    //Initialize an integer variable topoLevel = 0
      int topoLevel = 0;
    
    //for (i = 0 to i < numVertices)
      for(int i = 0; i < numVertices; i++)
        {
          //if (inDegree[i] equals 0), enqueue i
            if(inDegree[i] == 0)
              {
                vertexQ.push_back(i);
              }
        }
    
    //while (vertexQ's size > 0), do the following:
      while(vertexQ.size() > 0)
        {
          //let v be the vertex obtained by dequeue-ing vertexQ
            int v = vertexQ.front();
            vertexQ.pop_front();

          //assign topoOrder[topoLevel] = (char) (v + 97)
              topoOrder[topoLevel] = (char) (v + 97);

          //increment topoLevel by 1
            topoLevel++;

          //for (j = 0 to j < outDegree[v]), do the following:
            for(int j = 0; j < outDegree[v]; j++)
              {
                //let adjVertex be the destination of the jth outgoing edge of the vertex v
                  int adjVertex;
                  adjVertex = adjList.at(v).at(j).dest;
            
                //decrement inDegree[adjVertex] by 1
                  inDegree[adjVertex] = inDegree[adjVertex]-1;

                //if (inDegree[adjVertex] equals 0), then enqueue adjVertex to vertexQ
                  if(inDegree[adjVertex] == 0)
                    {
                      vertexQ.push_back(adjVertex);
                    }
              }
        }
      
      //if (topoLevel != numVertices), return null, else return topoOrder
        if(topoLevel != numVertices)
          {
            return NULL;
          }
        else
          {
            return topoOrder;
          }
	}
};
#endif /* MUTANTLANGUAGE_H_ */
