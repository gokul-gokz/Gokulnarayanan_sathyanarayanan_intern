#include<iostream>
#include<vector>
#include <list> 
using namespace std;

class Gridmap
{
private:
	vector< vector<int> > map;
	int size_x;
	int size_y;
	int edge_w;

public:
	Gridmap(int s_x,int s_y,int w=1)
	{
		// Initialize the variables
		size_x=s_x;
		size_y=s_y;
		edge_w=w;

		// Create a map
		for(int i=0;i<size_y;i++)
		{
			vector<int> x;
			for(int j=0;j<size_x;j++)
				x.push_back(1);
			map.push_back(x);
		}
	}

	void printmap()
	{
		// Print the map
		for(int i=0;i<size_y;i++)
		{
			vector<int> x;
			for(int j=0;j<size_x;j++)
				cout<<map[i][j];
				cout<<endl;
		}	
	}

	
	void updatemap(int occ[][1][2],int length)
	{

		for(int i=0;i<length;i++)
		{
			map[occ[i][0][0]][occ[i][0][1]] =0;
	}}
};

// int main()
// {
// 	Gridmap m1(10,10,10);
// 	m1.printmap();
//  	int occ[2][1][2]={{1,1},{1,4}};
 	

//  	m1.updatemap(occ,2);
// 	m1.printmap();
// }
