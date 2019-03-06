#include <cmath>


class node
{
public:
	// Node Variables
	int x;
	int y;
	double g; //Cost for the distance from start to node
	double h; //Heuristic cost for the distance from node to goal(Euclidean)
	double f; //Total cost 
	int parent_x;
	int parent_y;
	
	node(int x_pos,int y_pos,int p_x,int p_y);
	
	void update(int g_p,int e_w,int goal_x,int goal_y);
	
	bool operator==(const node& other)const;
	
};

node::node(int x_pos,int y_pos,int p_x,int p_y)
	{
		//Initialize the class variables 
	    x=x_pos;
	    y=y_pos;
	    g=0;
	    h=0;
	    f=0;
	    parent_x=p_x;
	    parent_y=p_y;
	}
	
void node::update(int g_p,int e_w,int goal_x,int goal_y)
    {
    	//Update the costs of the node  
        g=g_p+e_w;
        h=sqrt(pow((x-goal_x),2)+pow((y-goal_y),2)); //Cost based on Euclidean distance
        f=g+h;
    }

    //Operator overloading to compare class objects
bool node:: operator==(const node& other)const
	{
	    return(x==other.x and y==other.y);
	}