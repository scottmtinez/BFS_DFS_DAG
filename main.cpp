#include <iostream>
#include "DAG.h"
#include "BFS.h"
#include "DFS.h"
#include "MutantLanguage.h"
using namespace std;

const static string UNWEIGHTED_GRAPH1_PATH = "unweighted1.txt";
const static string UNWEIGHTED_GRAPH2_PATH = "unweighted2.txt";
const static string UNDIRECTED_GRAPH1_PATH = "undirected1.txt";
const static string UNDIRECTED_GRAPH2_PATH = "undirected2.txt";
const static string DAG1_PATH = "dag1.txt";
const static string DAG2_PATH = "dag2.txt";
const static string MUTANT1_PATH = "mutant1.txt";
const static string MUTANT2_PATH = "mutant2.txt";
const static string MUTANT3_PATH = "mutant3.txt";

void printArray(int *A, int len) {
	if (0 == len)
		cout << "[]";
	else {
		cout << "[";
		for (int i = 0; i < len - 1; i++) {
			if (A[i] == INT_MIN)
				cout << "-infty, ";
			else if (A[i] == INT_MAX)
				cout << "infty, ";
			else
				cout << A[i] << ", ";
		}
		if (A[len - 1] == INT_MIN)
			cout << "-infty]";
		else if (A[len - 1] == INT_MAX)
			cout << "infty]";
		else
			cout << A[len - 1] << "]";
		cout << endl;
	}
}

void printArray(char *A, int len) {
	if (0 == len)
		cout << "[]";
	else {
		cout << "[";
		for (int i = 0; i < len - 1; i++) {
			cout << A[i] << ", ";
		}
		cout << A[len - 1] << "]";
		cout << endl;
	}
}

void printArray(bool *A, int len) {
	if (0 == len)
		cout << "[]";
	else {
		cout << "[";
		for (int i = 0; i < len - 1; i++) {
			if (A[i])
				cout << "true" << ", ";
			else
				cout << "false" << ", ";
		}
		if (A[len - 1])
			cout << "true]";
		else
			cout << "false]";
		cout << endl;
	}
}

void testBFS() {

	string filePaths[] = { UNWEIGHTED_GRAPH1_PATH, UNWEIGHTED_GRAPH2_PATH };
	int numFiles = 2;
	for (int i = 0; i < numFiles; i++) {
		printf("*** Test BFS on UnweightedGraph %d ***\n\n", i + 1);
		BFS bfs(filePaths[i]);
		for (int j = 0; j < bfs.numVertices; j++) {
			bfs.executeBFS(j);
			cout << "Level array (from v" << j << "):   ";
			printArray(bfs.level, bfs.numVertices);
		}
		cout << endl;
	}
}

void testComponent() {

	string filePaths[] = { UNDIRECTED_GRAPH1_PATH, UNDIRECTED_GRAPH2_PATH };
	int numFiles = 2;
	for (int i = 0; i < numFiles; i++) {
		printf("*** Test Component Counter on UndirectedGraph %d ***\n\n",
				i + 1);
		BFS bfs(filePaths[i]);
		cout << "Number of components is " << bfs.countComponents() << endl
				<< endl;
	}
}

void testDFS() {
	string filePaths[] = { UNWEIGHTED_GRAPH1_PATH, UNWEIGHTED_GRAPH2_PATH };
	int numFiles = 2;
	for (int i = 0; i < numFiles; i++) {
		printf("*** Test DFS on UnweightedGraph %d ***\n\n", i + 1);
		DFS dfs(filePaths[i]);
		for (int j = 0; j < dfs.numVertices; j++) {
			dfs.executeDFS(j);
			cout << "Level array (from v" << j << "):   ";
			printArray(dfs.level, dfs.numVertices);
		}
		cout << endl;
	}
}

void testTransitiveClosure() {

	string filePaths[] = { UNWEIGHTED_GRAPH1_PATH, UNWEIGHTED_GRAPH2_PATH,
			UNDIRECTED_GRAPH1_PATH, UNDIRECTED_GRAPH2_PATH };
	int numFiles = 2;
	for (int i = 0; i < numFiles; i++) {
		printf("*** Test Transitive Closure on UnweightedGraph %d ***\n\n",
				i + 1);
		DFS dfs(filePaths[i]);
		bool **tc = dfs.computeTransitiveClosure();
		for (int j = 0; j < dfs.numVertices; j++)
			printArray(tc[j], dfs.numVertices);
		cout << endl;
	}
	for (int i = 0; i < numFiles; i++) {
		printf("*** Test Transitive Closure on UndirectedGraph %d ***\n\n",
				i + 1);
		DFS dfs(filePaths[i + 2]);
		bool **tc = dfs.computeTransitiveClosure();
		for (int j = 0; j < dfs.numVertices; j++)
			printArray(tc[j], dfs.numVertices);
		cout << endl;
	}
}

void testDAG() {
	string filePaths[] = { DAG1_PATH, DAG2_PATH };
	int numFiles = 2;
	for (int i = 0; i < numFiles; i++) {
		printf("*** Test Longest Path on DAG %d ***\n\n", i + 1);
		DAG ag(filePaths[i]);
		ag.longestPaths(0);
		cout << "Topological Order: ";
		printArray(ag.topoOrder, ag.numVertices);
		for (int j = 0; j < ag.numVertices; j++) {
			ag.longestPaths(j);
			printf("Longest Path Array (from v%d): ", j);
			printArray(ag.distance, ag.numVertices);
		}
		cout << endl;
	}
}

void testMutantLanguage() {
	string filePaths[] = { MUTANT1_PATH, MUTANT2_PATH, MUTANT3_PATH };
	int numFiles = 3;
	for (int i = 0; i < numFiles; i++) {
		printf("*** Test Mutant Language %d ***\n\n", i + 1);
		MutantLanguage mutant(filePaths[i]);
		char *topoOrder = mutant.getOrder();
		if (topoOrder != nullptr) {
			cout << "Alphabet order: ";
			printArray(topoOrder, mutant.numVertices);
		} else
			cout << "Unfortunately, this language has circular dependency."
					<< endl;
		cout << endl;
	}
}

int main() {
	testBFS();
	testComponent();
	testDFS();
	testTransitiveClosure();
	testDAG();
	testMutantLanguage();
	return 1;
}
