#include "SolutionSearch.h"


SolutionSearch::SolutionSearch(void)
{
}


SolutionSearch::~SolutionSearch(void)
{
}




/*			Student Implementation: here you need to implement the Breadth First Search Method						*/
/*																													*/
/*			Input: the first parameter is the random order of the 9 numbers, which you need to						*/
/*				   re-organize to make them into the correct order.													*/
/*				   the second parameter is actually an output. It returns or stores the moving						*/ 
/*				   path of the "empty space" that it is involved to make all the sub-images in						*/
/*				   the correct position. The integer seqence varible "solution" should store						*/
/*				   all the steps along the path																		*/
/*                                                                          										*/
/*			For example:																							*/
/*						Input:  data = {8, 4, 1, 3, 0, 2, 6, 7, 5 };												*/
/*						to make it into the correct order {0, 1, 2, 3, 4, 5, 6, 7, 8}								*/
/*						you need to make the following changes on the number 8, since the							*/
/*						number 8 represents the empty space, moving 8 to its neigboring								*/
/*						numbers equals to moving the corresponding number to the empty space.						*/
/*						Below it shows a demo of the steps:															*/
/*																													*/
/*  8 4 1   swap with 4   8 0 1   swap with 1    8 1 0   swap with 2     8 1 2   swap with 5    0 1 2				*/
/*  3 0 2  ------------>  3 4 2  ------------->  3 4 2  -------------->  3 4 8  --------------> 3 4 5  ---> End		*/
/*  6 7 5                 6 7 5                  6 7 5                   6 7 5                  6 7 8				*/
/*																													*/
/*			So from this example, the right path should be {1, 2, 5, 8}.											*/
/*			WHY? You may thought it was {4, 1, 2, 5}, since the number 8 has swapped with them in this order.		*/
/*			That is true. However, we do not care which number it swapped with, but which position the number 8		*/
/*          has gone through. As the numbers can be in any positions during different time, which give no hint		*/
/*			about where the number 8 is. In contrast, the positions are fixed. So we assume the positions are		*/
/*			in the same order as an increasing sequence:															*/
/*																													*/
/*																[0]  [1]  [2]										*/
/*											Fixed Position =    [3]  [4]  [5]										*/
/*																[6]  [7]  [8]										*/
/*																													*/											
/*			Here, I use "[]" to distinguish the positions from the numbers. So now you can see, the number 8 starts */
/*			from position [4], then swapped with number 4, which goes to the position [1]; then swapped with number */
/*			1, which goes to the position [2]; then swapped with number 2, which goes to the position [5]; finally, */
/*			swapped with number 5, which goes to the position [8]. So the path you should assign to the parameter   */
/*			"&solution" with the path sequence {1, 2, 5, 8}.			
*/
int SolutionSearch::hfunction(int* data){
	int wrong = 0;
	for  (int i = 0; i < 9; i++)
	{
		if (data[i] != i){
			wrong++;
		}
	}
	return wrong;
}
MyStruct* SolutionSearch:: optimal(vector<MyStruct*> &fringe){
	if (fringe.size() == 0)
    return NULL;
	int opt = 0;
	for (int i = 0; i<fringe.size(); i++){
		if (fringe[i]->h + fringe[i]->g<fringe[opt]->h + fringe[opt]->g)
			opt = i;
	}
    MyStruct* optimal = fringe[opt];
	fringe.erase(fringe.begin() + opt);
	return optimal;
}
 

bool SolutionSearch:: CheckGoalState (int* data){
	for (int i = 0; i < 9; i++){
		if (data[i] != i)
			return false;
	}
	return true;
}

bool SolutionSearch::equalStates(int* data1, int* data2){
	for (int i = 0; i<9; i++){
		if (data1[i] != data2[i])
			return false;
	}
	return true;
}

bool SolutionSearch::Path(int* data){
	for (int i = 0; i<whole.size(); i++){
		if (equalStates(data, whole[i]))
			return true;
	}
	return false;
}

int SolutionSearch::Empty(int* data){
	int i;
	for ( i=0; i<9; i++){
		if (data[i] == 8){
			break;
		}
			
	}
	return i;
}



int* SolutionSearch::createChild(int* data, int empty, int N){
	int* child = new int[9]; 
	for (int i = 0; i<9; i++) 
    child[i] = data[i];
	int temp = child[N];
	child[N] = 8;
	child[empty] =temp;
	return child;
}

vector<MyStruct*> SolutionSearch::generateChildren(MyStruct* state){
	vector<MyStruct*> temp;
	int empty = Empty(state->data);
	if (empty > 2){
		MyStruct* child = new MyStruct;
		child->parent = state;
		child->data = createChild(state->data, empty, empty - 3);
		temp.push_back(child);
	}
	if (empty < 6){
		MyStruct* child = new MyStruct;
		child->parent = state;
		child->data = createChild(state->data, empty, empty + 3);
		temp.push_back(child);
	}
	if (empty % 3 < 2){
		MyStruct* child = new MyStruct;
		child->parent = state;
		child->data = createChild(state->data, empty, empty + 1);
		temp.push_back(child);
	}
	if (empty % 3 > 0){
		MyStruct* child = new MyStruct;
		child->parent = state;
		child->data = createChild(state->data, empty, empty - 1);
		temp.push_back(child);
	}
	return temp;
}


bool SolutionSearch::breadthSearch(int *data, vector<int> &solution)
{

 whole.clear();
 MyStruct* start= new MyStruct;
 start->parent=NULL;
 start->data = data;


	queue<MyStruct*> states; 
	states.push(start);
	while (states.size()>0){
	
		MyStruct* current = states.front();
		states.pop();
		if (CheckGoalState(current->data)){
			vector<int> path;
			while (current->parent != NULL){
				int position = Empty(current->data);
				path.push_back(position);
				current  = current->parent;
			}
			for (int i = path.size() - 1; i >= 0; i--){
				solution.push_back(path[i]);
			}
			return true;
		}
		else if (!Path(current->data)){
			whole.push_back(current->data);
			vector<MyStruct*> children = generateChildren(current);
			for (int i = 0; i<children.size(); i++){
				states.push(children[i]);
			}
		}
	}
	return false;

}

/*  Student Implementation: here you need to implement the Depth First Search Method   */
/*  The input parameters follow the same rule as above "breadthSearch"				   */
bool SolutionSearch::depthSearch(int *data, vector<int> &solution)
{
    whole.clear();
	MyStruct* start=new MyStruct;
	start->parent = NULL;
	start->data = data;
	stack<MyStruct*> states; // 
	states.push(start);
	while (states.size()>0){
		MyStruct* current = states.top();
		states.pop();
		if (CheckGoalState(current->data)){
			vector<int> path;
			while (current->parent != NULL){
				int position = Empty(current->data);
			    path.push_back(position);
				current = current->parent;
			}
			for (int i = path.size() - 1; i >= 0; i--){
				solution.push_back(path[i]);
			}
			return true;
		}
		else if (!Path(current->data)){
			whole.push_back(current->data);
			vector<MyStruct*> children = generateChildren(current);
			for (int i = 0; i<children.size(); i++){
				states.push(children[i]);
			}
		}
	}
	return false;

	return 1; 
}
bool SolutionSearch::AStarSearch(int *data, vector<int> &solution)
{

    MyStruct* start = new MyStruct;
	start->data = data;
	start->parent = NULL;
	start->g = 0;
	start->h = hfunction(data);
	vector<int> path;
	vector<MyStruct*> fringe;
	fringe.push_back(start);
	while (fringe.size() > 0){
		MyStruct* current = optimal(fringe);
		if (CheckGoalState(current->data)){
			while (current->parent != NULL){
			int position = Empty(current->data);
			path.push_back(position);
			current = current->parent;
			}
			for (int i = path.size() - 1; i >= 0; i--){
			solution.push_back(path[i]);
			}
			return true;
			}
            else if (!Path(current->data)){
			whole.push_back(current->data);
			vector<MyStruct*> children = generateChildren(current);
			for (int i = 0; i < children.size(); i++){
			MyStruct* child = children[i];
			child->g = child->parent->g + 1;
			child->h = hfunction(child->data);
			fringe.push_back(child);
			}
			}
			}
			return false;
}

