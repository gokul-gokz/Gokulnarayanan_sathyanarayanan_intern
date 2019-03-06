
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <array>

#define SIZE_X 10
#define SIZE_Y 10
#define EDGE_W 10 

using namespace std;

class roadmap
{
private:
	// Create a vector of vector for representing the adjacency list
	vector<vector<array<int,3>>>adjList;


public:
	roadmap()
	{
		list<array<int,2>> connections{{1,0},{0,1},{-1,0},{0,-1}};
		for(int i=0;i<SIZE_Y;i++)
		{
			
			for(int j=0;j<SIZE_X;j++)
			{
			    vector<array<int,3>> row; 
				for (auto const& k : connections) 
				{
				    int node_position[2]={i+k[0],j+k[1]};
				    //cout<<node_position[0]<<"'"<<node_position[1];
    				if(node_position[0]>=0 && node_position[0]<=SIZE_X-1 && node_position[1]>=0 && node_position[1]<=SIZE_Y-1)
    				{
    				  row.push_back({node_position[1],node_position[0],EDGE_W});
    				}
				}
				adjList.push_back(row);
			}
			
		}
	}
	
	void printmap()
	{
	    cout<<adjList[0].size();
	    cout<<endl;
		//Print the map
		for(int i=0;i<100;i++)
		{
			vector<int> x;
			cout<<endl;
			for(int j=0;j<adjList[i].size();j++)
				cout<<"("<<adjList[i][j][0]<<","<<adjList[i][j][1]<<"),";
				cout<<endl;
		}	
	}
	
	vector<array<int,3>> neighbours(int n[2])
	{
	    int node_position=n[0]+n[1]*10;
	    return adjList[node_position];
	}


};