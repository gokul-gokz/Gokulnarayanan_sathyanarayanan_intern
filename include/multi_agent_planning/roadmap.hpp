#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <array>

using namespace std;

class roadmap
{
private:
	// Create a vector of vector for representing the adjacency list
	vector<vector<pair<int,int>>>adjList;

public:
	//Constructor to create the roadmap
	roadmap(int size_x,int size_y,int w)
	{
		//4 connectivity representation 
		list<array<int,2>> connections{{1,0},{0,1},{-1,0},{0,-1}};
		//Creating the roadmap with 4connectivity
		for(int i=0;i<size_y;i++)
		{
			
			for(int j=0;j<size_x;j++)
			{
				//The connectivity is represented as a vector of pairs(node,edge_weight)
				vector<pair<int,int>> row; 
				//Finding the connectivity of each node
				for (auto const& k : connections) 
				{
				    int node_position[2]={i+k[0],j+k[1]};
				   
    				if(node_position[0]>=0 && node_position[0]<=size_y-1 && node_position[1]>=0 && node_position[1]<=size_x-1)
    				{
    				  row.push_back(make_pair((node_position[0]*10)+node_position[1],w));
    				}
				}
				adjList.push_back(row);
			}
			
		}
	}
	
	void printmap()
	{

	    //Print the map
		for(int i=0;i<100;i++)
		{
			vector<int> x;
			cout<<endl;
			for(int j=0;j<adjList[i].size();j++)
				cout<<adjList[i][j].first<<",";
				cout<<endl;
		}	
	}


};

// int main()
// {
//     roadmap r1(10,10,1);
//     r1.printmap();
//     return 0;
// }
