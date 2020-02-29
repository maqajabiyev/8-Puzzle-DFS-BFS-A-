
/* This is the main class that you need to modify. Basically you need to implement the BFS and DFS search algorithms */
/* To make the code compatible, different search algorithms have the same input and output parameters                */


#pragma once

#include <vector>       // std::vector
#include <queue>
#include <stack>

using namespace std;

 
struct MyStruct
{
	int* data;
	MyStruct* parent;
	MyStruct* child;
	int h;
	int g;
	int f;


};

class SolutionSearch
{
	vector<int*> whole;
	int  Empty(int* data); 
	bool Path(int* data);
	bool CheckGoalState(int* data);
	bool equalStates(int* data1, int* data2);
	
public:
	SolutionSearch(void);
	~SolutionSearch(void);
	MyStruct* optimal(vector<MyStruct*> &fringe);
	int hfunction(int* data);
	int* createChild(int* data, int empty, int M);
	vector<MyStruct*> generateChildren(MyStruct* data);
	bool AStarSearch(int *data, vector<int> &solution);
	bool breadthSearch(int *data, vector<int> &solution); //Student Implementation: you need to implement this function
	bool depthSearch(int *data, vector<int> &solution); //Student Implementation: you need to implement this function
};

