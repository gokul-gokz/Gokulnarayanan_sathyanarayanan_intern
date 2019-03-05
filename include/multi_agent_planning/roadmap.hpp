
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include<array>

using namespace std;

class roadmap
{
private:
	// Create a vector of vector for representing the adjacency list
	vector<vector<array<int,3>>>adjList;

public:
	roadmap(int size,int w)
	{
		list<array<int,2>> connections{{1,0},{0,1},{-1,0},{0,-1}};
		for(int i=0;i<10;i++)
		{
			
			for(int j=0;j<10;j++)
			{
			    vector<array<int,3>> row; 
				for (auto const& k : connections) 
				{
				    int node_position[2]={i+k[0],j+k[1]};
				    //cout<<node_position[0]<<"'"<<node_position[1];
    				if(node_position[0]>=0 && node_position[0]<=size-1 && node_position[1]>=0 && node_position[1]<=size-1)
    				{
    				  row.push_back({node_position[0],node_position[1],w});
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
				//cout<<"("<<adjList[i][j][0]<<","<<adjList[i][j][1]<<"),";
				cout<<endl;
		}	
	}
	
	vector<array<int,3>> neighbours(int n[2])
	{
	    int node_position=n[0]+n[1]*10;
	    return adjList[node_position];
	}


};