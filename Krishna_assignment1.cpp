#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h> //required header files

using namespace std;
int node_count=1; //count of nodes generated
class Tree
{
public:
	struct node //structure holding node details such as node movements, state, location of blank in puzzle, branch cost and final cost
	{
	    int branch_cost;//branch cost i.e. g(n)
		int final_cost;//final cost f(n)
        vector<int> state;//vector to store digits of the puzzle
		int index;//used to know the location of blank tile
		node* parent;
		node* up;//4 movements of the blank tile
		node* down;
		node* left;
		node* right;
    };
	vector<int> start_state, end_state; //start and end state vectors
    int heuristic;					//holding the h(n) value
	bool check_path;				//to check if a path is valid
    node* root;           //to hold root of a state
	vector<node*> node_list;  //vector to hold nodes generated

	Tree()
	{
		root=0;		//setting root to 0
	}

void  input() //taking inputs from the user for start and end state.
{
	int input;
	cout<<"Enter digits from 1 - 8 for start state. Enter 0 for blank tile\n";
	for(int i=0;i<9;i++)
	{
		cin>>input;
		start_state.push_back(input);
	}
	cout<<"Enter digits from 1 - 8 for the end state. Enter 0 for blank tile\n";
	for(int i=0;i<9;i++)
	{
		cin>>input;
		end_state.push_back(input);
	}
}

bool if_empty()//checking if root is empty or not.
{
    return root==0;
}


void  construct_root(vector<int> start_state)
 {
	node* new_node=new node; //creating a empty root node
	for(int i=0;i<9;i++)
	new_node->state.push_back(start_state[i]);
	new_node->final_cost=heuristic_dist(new_node);
	new_node->branch_cost=1;  //branch cost i.e. depth
	new_node->parent=0;//parent of the new node set to 0
	new_node->up=0;//setting up the movements to 0 initially
	new_node->down=0;
	new_node->left=0;
	new_node->right=0;
	for(int i=0;i<9;i++) //checking for the index of blank tile
	{
		if (start_state[i]==0)
			new_node->index=i;
	}
	if (if_empty())//need to check if the root of the node doesnt have parent
	{
		root=new_node;    //set new_node_1 to root.
		node_list.push_back(root);
	}
}

int  heuristic_dist(node* temp) //estimating cost to end state from current state h(n)
{
	int heuristic_cost=0;
	for(int i=0;i<temp->state.size();i++)
	{
		if (end_state[i]!=temp->state[i])
		{
			heuristic_cost++;
		}
	}
	return heuristic_cost;
}

void  gen_nodes()//used to generate tree of nodes
{
	construct_root(start_state); //constructing root node
	node* current;
	check_path=false;
	int count=0;
	heuristic=1;
	while(node_list.size()>0)  //comparing current node with all nodes present in the node list
	{
		current=node_list.front(); //choosing the minimum node
		node_list.erase(node_list.begin());
		insert_node(current);
		if(current->branch_cost>count)//choosing the node which has least g(n) value
		{
			count=current->branch_cost;
			cout<<"Number of nodes in path= "<<count<<"\n";
		}
	}
}

void  node_sort()//sorting nodes in descending order.
{
		node* temp;
		for (int i=0;i<node_list.size()-1;i++)
			{
			for (int j=0;j<node_list.size()-1;j++)
				{
					if (node_list[j]->final_cost>node_list[j+1]->final_cost)
					{
						temp=node_list[j];
						node_list[j]=node_list[j+1];
						node_list[j+1]=temp;
					}
				}
			}
}

void  insert_node(node* current)//expanding new nodes of an already existing node
	{
	node* new_node_1=new node;
	state_change(current,new_node_1,1); //swapping the node upwards with blank tile
	new_node_1->branch_cost=current->branch_cost+1; //increasing branch cost by 1
	new_node_1->final_cost=heuristic_dist(new_node_1)+new_node_1->branch_cost;//A* algorithm formula
	new_node_1->parent=current; //make current node as parent node
	//setting all possible movements to zero indicating new node is a leaf node
	new_node_1->up=0;
	new_node_1->down=0;
	new_node_1->left=0;
	new_node_1->right=0;
	node* new_node_2=new node;
	state_change(current,new_node_2,4);//swapping the node right with blank tile
	new_node_2->branch_cost=current->branch_cost+1;//increasing branch cost by 1
	new_node_2->final_cost=heuristic_dist(new_node_2)+new_node_2->branch_cost;//A* algorithm formula
	new_node_2->up=0;//setting all possible movements to zero indicating new node is a leaf node
	new_node_2->down=0;
	new_node_2->left=0;
	new_node_2->right=0;
	new_node_2->parent=current;//make current node as parent node
	node* new_node_3=new node;
	state_change(current,new_node_3,2);//swapping the node down with blank tile
	new_node_3->branch_cost=current->branch_cost+1;//increasing branch cost by 1
	new_node_3->final_cost=heuristic_dist(new_node_3)+new_node_3->branch_cost;//A* algorithm formula
	new_node_3->up=0;//setting all possible movements to zero indicating new node is a leaf node
	new_node_3->down=0;
	new_node_3->left=0;
	new_node_3->right=0;
	new_node_3->parent=current;//make current node as parent node
	node* new_node_4=new node;
	state_change(current,new_node_4,3);//swapping the node left with blank tile
	new_node_4->branch_cost=current->branch_cost+1;//increasing branch cost by 1
	new_node_4->final_cost=heuristic_dist(new_node_4)+new_node_4->branch_cost;//A* algorithm formula
	new_node_4->up=0;//setting all possible movements to zero indicating new node is a leaf node
	new_node_4->down=0;
	new_node_4->left=0;
	new_node_4->right=0;
	new_node_4->parent=current;//make current node as parent node

	if ((current->up==0)&&(new_node_1->state.size()>0))
		//if up node is not linked to current and has non-zero size,
		//then link new_node_1 and current by up.
	{
		node_count++;
		current->up=new_node_1;
		if (!check_path)
            node_list.push_back(current->up);
	}
	else
		delete new_node_1;
	if ((current->down==0)&&(new_node_2->state.size()>0))
	{
		node_count++;
		current->down=new_node_2;
		if (!check_path)
            node_list.push_back(current->down);
	}
	else
		delete new_node_2;
	if ((current->left==0)&&(new_node_3->state.size()>0))
	{
		node_count++;
		current->left=new_node_3;
		if (!check_path)
            node_list.push_back(current->left);
	}
	else
		delete new_node_3;
	if ((current->right==0)&&(new_node_4->state.size()>0))
	{
		node_count++;
		current->right=new_node_4;
		if (!check_path)
            node_list.push_back(current->right);
	}
	else
		delete new_node_4;

	node_sort(); //node_sort nodes with minimum pathcost
	success_check(current); //check if end_state state is reached or not.
}

void  success_check(node* current)//to check if end state is accessible from current state or not
{
	bool check1,check2,check3,check4;
	check1=check2=check3=check4=true;
	for (int i=0;i<9;i++)
        {
		if (current->up!=0)
		{
			if (current->up->state[i]!=end_state[i])
				check1=false;
		}
		else
			check1=false;
		if (current->down!=0)
		{
			if (current->down->state[i]!=end_state[i])
				check2=false;
		}
		else
			check2=false;
		if (current->left!=0)
		{
			if (current->left->state[i]!=end_state[i])
				check3=false;
		}
		else
			check3=false;
		if (current->right!=0)
		{
			if (current->right->state[i]!=end_state[i])
				check4=false;
		}
		else
			check4=false;
	}
	if(check1)
	{
		check_path=true;
		cout<<"Done!\n";
		print(current->up);
	}
	else if(check2)
	{
		check_path=true;
		cout<<"Done!\n";
		print(current->down);
	}
	else if(check3)
	{
		check_path = true;
		cout<<"Done!\n";
		print(current->left);
	}
	else if(check4)
	{
		check_path = true;
		cout<<"Done!\n";
		print(current->right);
	}

	if (check_path)
	{
		while(!node_list.empty())
			node_list.erase(node_list.begin());
	}
}


void  state_change(node* current, node* temp, int dir)//changing the state on basis of manhattan distance
{
	int index;
	bool wrong_move=false;
	for (int i=0;i<current->state.size();i++)
        {
		if (current->state[i]==0)
		{
			index=i;
		}
		temp->state.push_back(current->state[i]);
	}
	temp->index=index;
	if (current->branch_cost>2)
        {
		if (index==current->parent->index)
		{
			wrong_move=true;
		}
	}
	int temp1;
	switch (dir) { //to move tiles in up,down,left,right based on manhattan distance
	case 1: // to move blank space in upward dir
		if ((index > 2)&&(!wrong_move)) // to move upwards only if the blank is in 2 and 3 row
		{
			temp1=temp->state[index];
			temp->state[index]=temp->state[index-3];
			temp->state[index-3]=temp1;
		}
		else //delete the node if upward movement is not possible.
			temp->state.erase(temp->state.begin(),temp->state.end());
		break;
	case 4:
		if ((index%3!=2)&&(!wrong_move))
		{
			temp1=temp->state[index];
			temp->state[index]=temp->state[index+1];
			temp->state[index+1]=temp1;
		}
		else
			temp->state.erase(temp->state.begin(),temp->state.end());
		break;
	case 2:
		if ((index<6)&&(!wrong_move))
		{
			temp1=temp->state[index];
			temp->state[index]=temp->state[index+3];
			temp->state[index+3]=temp1;
		}
		else
			temp->state.erase(temp->state.begin(),temp->state.end());
		break;
	case 3:
		if ((index%3!=0)&&(!wrong_move))
		{
			temp1=temp->state[index];
			temp->state[index]=temp->state[index-1];
			temp->state[index-1]=temp1;
		}
		else
			temp->state.erase(temp->state.begin(),temp->state.end());
		break;
	}
}

void  print(node* root) { //prints states from start to end states.
	vector<node*> pnt;
	while(root!=0)//backtracking to root node from current node
	{
		pnt.push_back(root);
		root=root->parent;
	}

	cout<<"Starting State\n";
	for (int j=pnt.size()-1;j>=0;j--)
	{
		cout<<"Move number "<<pnt.size()-j-1<<":\n";
		for (int i=0;i<pnt[j]->state.size();i++)
		{
			if (pnt[j]->state[i]==0)
				cout<<"0 ";
			else
				cout<<pnt[j]->state[i]<< " ";
			if (i % 3 == 2)
                cout<<"\n"; //indicates end of row.
		}
		cout<<"\n";

	}
	cout<<"End State\n";
	cout<<"Total number of nodes generated=" <<node_count<<"\n";
}

};


int main()
{

	Tree b;//tree object
	b.input();//taking inputs
	b.gen_nodes();//generating tree
	return 0;
}
