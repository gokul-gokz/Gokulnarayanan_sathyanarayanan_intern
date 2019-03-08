#ifndef NODE_H
#define NODE_H
// Math
#include <cmath>

/**
 * @brief Representation of a node for a discretized path plamnning environment.
 */
class node
{
public:
	// Node Variables

	int x;
	int y;
	int theta;
	
	double g; //Cost for the distance from start to the node
	double h; //Heuristic cost for the distance from node to goal(Euclidean)
	double f; //Total cost 
	
	int parent_x;
	int parent_y;
	

	/**
   * @brief Constructor to initialize the node parameters
   * @param node position_x 
   * @param node position_y
   * @param node parent_position_x
   * @param node parent_position_y
   * @param node orientation_yaw 
   */
	node(int x_pos,int y_pos,int p_x,int p_y,int yaw);

	/**
   * @brief Function to update the cost of the node
   * @param parent_g_cost 
   * @param edge_weight between parent and the node
   * @param goal_node_position_x
   * @param goal_node_position_y
   */	
	void update(int g_p,int e_w,int goal_x,int goal_y);

	/**
   * @brief Operator overloading function to compare the nodes based on node positions
   * @param node_to_be_compared
   * @return boolean true if they are same
   */	
	bool operator==(const node& other)const;
	
};




node::node(int x_pos,int y_pos,int p_x,int p_y,int yaw=0)
	{
		//Initialize the node variables 
	    x=x_pos;
	    y=y_pos;
	    theta=yaw; // yaw is set to zero for the current problem as it is not used
	    g=0;
	    h=0;
	    f=0;
	    parent_x=p_x;
	    parent_y=p_y;
	}
	
void node::update(int g_p,int e_w,int goal_x,int goal_y)
    {
    	//Calculate g value based on the parent g and the edge weight
        g=g_p+e_w;

        //Calculate the hvale based on the euclidean distance between the node and the goal node
        h=sqrt(pow((x-goal_x),2)+pow((y-goal_y),2));

        //Calculate the total cost of the node
        f=g+h;
    }

   
bool node:: operator==(const node& other)const
	{
		// Comparison is done based on x and y. yaw angle is neglected as they are fixed in our case.
	    return(x==other.x and y==other.y);
	}

#endif