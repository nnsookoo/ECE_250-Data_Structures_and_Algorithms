#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**Portions of C++ code (insert function) is written based on PseudoCode structure provided on Wikipedia**/


struct Point{
	float x; //X Coordinate
	float y; //Y Coordinate
	
	Point(const float& xco, const float& yco){ //Creating a defined point
		x = xco;
		y = yco;
	}
	
	Point(){ //Creating an empty point
		x = 0.00;
		y = 0.00;
	}
};

struct Node{
	Point position; //Position defined by coordinates
	string city; //City Name
	int p; //Population
	int r; //Cost of Living
	int s; //Net Average Salary
	
	Node(Point _pos, const string& name, const int& pop, const int& col, const int& nas){ //Creating a defined point
		position = _pos,
		city = name;
		p = pop;
		r = col;
		s = nas;
	}
	
	Node(){ //Creating an empty node
		p = 0;
		r = 0;
		s = 0;
	}

};

struct boundary_box{ //Boundary_box used in subdividing a tree into further subtrees
	Point center; //Contains the centre of the box
	float half_of_dimension; //Contains the length of that box/2
	
	boundary_box(){ //Creating an empty boundary_box
		center = Point(); 
		half_of_dimension = 0;
	}
	
	boundary_box(Point _center, const float& _half){ //Creating a defined boundary_box
		center = _center;
		half_of_dimension = _half;
	}
};

class QuadTree{
	
	private:
		
		vector <Node*> tile; //A vector array containing pointers to the node (which contains the information)
		int _node_capacity; //Maximum capacity of one node (1)
		
		boundary_box boundary; //These act as boundaries of the subtree
		
		QuadTree *northwestTree; //A pointer to the NW tree
		QuadTree *northeastTree; //A pointer to the NE tree
		QuadTree *southwestTree; //A pointer to the SW tree
		QuadTree *southeastTree; //A pointer to the SE tree
		
	public:
		QuadTree();
		QuadTree(boundary_box bounds);
		~QuadTree();
		bool insert(Node *node);
		void subdivide();
		bool search(Point *p);
		void return_cityname(Point *p);
		void query_attribute(Point *p, const string direction, const string stat, const string attribute);
		int p_GetStat(const string stat, vector<int> &values);
		int r_GetStat(const string stat, vector<int> &values);
		int s_GetStat(const string stat, vector<int> &values);
		void print();
		void clear();
		int size(int &initial_size);
};

QuadTree::QuadTree(){ //Creating an empty quadtree (no elements found)
	_node_capacity = 1;
	boundary = boundary_box();
	northwestTree = NULL;
	northeastTree = NULL;
	southwestTree = NULL;
	southeastTree = NULL;
	tile = vector<Node*> ();
	
}

QuadTree::QuadTree(boundary_box bounds){ //Creating a defined quadtree based on boundaries
	_node_capacity = 1; //The maximum amount of cities which can be stored in one node vector is 1
	tile = vector<Node*> (); //An empty node vector
	this->boundary = bounds; //Define the bounds
	northwestTree = NULL; //the tree is not subdivided
	northeastTree = NULL;
	southwestTree = NULL;
	southeastTree = NULL;
}

QuadTree::~QuadTree(){ //Delete the quadtree by utilising the clear function
	clear();
}

void QuadTree::subdivide(){
	float new_half_size = this->boundary.half_of_dimension/2; //To create the boundaries for subtrees, we need to divide the current half dimension by 2.
	
	//cout << "New Half Size " << new_half_size << endl;
	
	Point new_center = Point(boundary.center.x - new_half_size, boundary.center.y - new_half_size);
	//cout << "NW TREE CENTRE: (" << boundary.center.x - new_half_size << " ," << boundary.center.y - new_half_size << ")" << endl;
	this->northwestTree = new QuadTree(boundary_box(new_center, new_half_size));
	
	new_center = Point(boundary.center.x + new_half_size, boundary.center.y - new_half_size);
	//cout << "NE TREE CENTRE: (" << boundary.center.x + new_half_size << " ," << boundary.center.y - new_half_size << ")" << endl;
	this->northeastTree = new QuadTree(boundary_box(new_center, new_half_size));
	
	new_center = Point(boundary.center.x - new_half_size, boundary.center.y + new_half_size);
	//cout << "SW TREE CENTRE: (" << boundary.center.x - new_half_size << " ," << boundary.center.y + new_half_size << ")" << endl;
	this->southwestTree = new QuadTree(boundary_box(new_center, new_half_size));
	
	new_center = Point(boundary.center.x + new_half_size, boundary.center.y + new_half_size);
	//cout << "SE TREE CENTRE: (" << boundary.center.x + new_half_size << " ," << boundary.center.y + new_half_size << ")" << endl;
	this->southeastTree = new QuadTree(boundary_box(new_center, new_half_size));
}
	
bool QuadTree::insert(Node *node){
	
	if(node == NULL){ //Check if the node you are passing in has contents. If not, return false.
		return false;
	}
	
	if(tile.size() < _node_capacity){ //Check if there is space in that block to insert the node. We check if the tile.size() < _node_capacity.
	//The only way this function will work is if the current tile.size() is 0 (_node_capacity is 1).
		tile.push_back(node); //Using the function push_back in the vector STL, add the node and return true.
		return true;
	}
	
	if(northwestTree == NULL){ //If you need to insert a node in a subtree, you will firstly need to check if there are subtrees present. Otherwise, subdivide and create subtrees
		subdivide();
	}
	
	float root_x = tile[0]->position.x; //root_x contains the x coordinate of the root of the current subtree
	float root_y = tile[0]->position.y; //root_y contains the y coordinate of the root of the current subtree
	float insert_x = node->position.x; //insert_x contains the x coordinate of the node you are inserting
	float insert_y = node->position.y; //insert_y contains the y coordinate of the node you are inserting
	
	Point* to_search = new Point(insert_x, insert_y); //Create a point using the insert_x and insert_y in order to search
	
	if(this->search(to_search) == true) //If the point you are trying to insert is already found in the subtree, return a false.
		return false;
	
	if((insert_x < root_x)&&(insert_y >= root_y)){ //Check the condition to see if the point needs to be inserted in the NW subtree
		northwestTree->insert(node);
		return true;
	}
	
	else if((insert_x >= root_x)&&(insert_y > root_y)){ //Check the condition to see if the point needs to be inserted in the NE subtree
		northeastTree->insert(node);
		return true;
	}
	
	else if((insert_x <= root_x)&&(insert_y < root_y)){ //Check the condition to see if the point needs to be inserted in the SW subtree
		southwestTree->insert(node);
		return true;
	}
	
	else if((insert_x > root_x)&&(insert_y <= root_y)){ //Check the condition to see if the point needs to be inserted in the SE subtree
		southeastTree->insert(node);
		return true;
	}

	return false;
}

bool QuadTree::search(Point *p){
	
	if(this->tile.size() < _node_capacity){ //Check if the node is empty. We do this by checking the tile.size(). If the tile.size() == 0, return a false.
		return false;
	}
	
	float root_x = tile[0]->position.x; //root_x contains the x coordinate of the root of the current subtree
	float root_y = tile[0]->position.y; //root_y contains the y coordinate of the root of the current subtree
	float search_x = p->x; //search_x contains the x coordinate of the point you are searching for
	float search_y = p->y; //search_y contains the y coordinate of the point you are searching for
	
	//If the point was found, return true.
	if((root_x == search_x)&&(root_y == search_y)){
			return true;
	}
	
	//Else start traversing from root. If all pointers are equal to NULL, then return false
	else if((this->northwestTree == NULL) && (this->northeastTree == NULL) && (this->southwestTree == NULL) && (this->southeastTree == NULL)){
		return false;
	}
	
	//Else, check if one of the pointers is not NULL and proceed to search recursively within subtrees
	else if((this->northwestTree != NULL) || (this->northeastTree != NULL) || (this->southwestTree != NULL) || (this->southeastTree != NULL)){

		if((search_x < root_x)&&(search_y >= root_y)){ //Check to see if the search point can be found in the NW subtree

			this->northwestTree->search(p);

			if((search_x == root_x)&&(search_y == root_y)){
				return true;
			}
			
		}
		else if((search_x >= root_x)&&(search_y > root_y)){ //Check to see if the search point can be found in the NE subtree
			
			this->northeastTree->search(p);
			
			if((search_x == root_x)&&(search_y == root_y)){
				return true;
			}

		}
		else if((search_x <= root_x)&&(search_y < root_y)){ //Check to see if the search point can be found in the SW subtree
			
			this->southwestTree->search(p);
			
			if((search_x == root_x)&&(search_y == root_y)){
				return true;
			}
			
		}
		else if((search_x > root_x)&&(search_y <= root_y)){ //Check to see if the search point can be found in the SE subtree
			
			this->southeastTree->search(p);
			
			if((search_x == root_x)&&(search_y == root_y)){
				return true;
			}
			
		}
	}
	

}

void QuadTree::return_cityname(Point *p){
	
	//You basically just need to search for the point as these conditions were already checked in the search function
	
	float root_x = tile[0]->position.x;
	float root_y = tile[0]->position.y;
	float search_x = p->x;
	float search_y = p->y;
	
	if((root_x == search_x)&&(root_y == search_y)){
			cout << tile[0]->city << endl;
			return;
	}
	
	//cout << "Looking for " << search_x << "; " << search_y << ". But came across " << root_x << "; " << root_y << ". Looking in the ";
	
	else if((search_x < root_x)&&(search_y >= root_y)){
		//cout << "northwest" << endl;
		this->northwestTree->return_cityname(p);
		
		if((root_x == search_x)&&(root_y == search_y)){
			cout << tile[0]->city << endl;
			return;
		}
	}
	
	else if((search_x >= root_x)&&(search_y > root_y)){
		//cout << "northeast" << endl;
		this->northeastTree->return_cityname(p);
		
		if((root_x == search_x)&&(root_y == search_y)){
			cout << tile[0]->city << endl;
			return;
		}
	}
	
	else if((search_x <= root_x)&&(search_y < root_y)){
		//cout << "southwest" << endl;
		this->southwestTree->return_cityname(p);
		
		if((root_x == search_x)&&(root_y == search_y)){
			cout << tile[0]->city << endl;
			return;
		}
	}
	
	else if((search_x > root_x)&&(search_y <= root_y)){
		//cout << "southeast" << endl;
		this->southeastTree->return_cityname(p);
		
		if((root_x == search_x)&&(root_y == search_y)){
			cout << tile[0]->city << endl;
			return;
		}
	}
}

void QuadTree::query_attribute(Point *p, const string direction, const string stat, const string attribute){
	
	//Can only work if the point is found
	
	//Basically, you need to find the node belonging to that point first. 
	
	//You will want to compare all members of the subtree in that direction
	//Therefore, find the point first, then go to the subtree specified by the direction
	//Check if the pointer to that subtree is NULL. If it is, output a failure
	//If not, go to that subtree. Store the value of the specified attribute of the root
	//of that subtree along with the values of the specified attribute of the children 
	//in an array of size 5. Compare these five numbers to find the min or max.
	
	//**********************Get that point belonging to whatever subtree. Run the function on that subtree recursively. Find the max, min or total for the subtree and
	// and then update the stat**************************************************************************************************
	
	
	if(this->search(p) == 0)
		cout << "failure" << endl;
	
	float root_x = this->tile[0]->position.x;
	float root_y = this->tile[0]->position.y;
	float search_x = p->x;
	float search_y = p->y;
	
	if((root_x == search_x)&&(root_y == search_y)){
		//cout << root_x << "; " << root_y << endl;
		
		vector<int> vals;
		
		if(direction == "NW"){ //If direction is NW, go to the NW and take all subtrees of that NW root
			if(northwestTree == NULL){
				cout << "failure" << endl;
			}
			else if(northwestTree->tile.size()==0){
				cout << "failure" << endl;
			}
			else if(northwestTree->tile.size()==1){
				
				if(attribute == "p")
					cout << stat << " " << this->northwestTree->p_GetStat(stat, vals) << endl;
				else if(attribute == "r")
					cout << stat << " " << this->northwestTree->r_GetStat(stat, vals) << endl;
				else if(attribute == "s")
					cout << stat << " " << this->northwestTree->s_GetStat(stat, vals) << endl;
				
			}
		}
		if(direction == "NE"){
			if(northeastTree == NULL){
				cout << "failure" << endl;
			}
			else if(northeastTree->tile.size()==0){
				cout << "failure" << endl;
			}
			else if(northeastTree->tile.size()==1){
				
				if(attribute == "p")
					cout << stat << " " << this->northeastTree->p_GetStat(stat, vals) << endl;
				else if(attribute == "r")
					cout << stat << " " << this->northeastTree->r_GetStat(stat, vals) << endl;
				else if(attribute == "s")
					cout << stat << " " << this->northeastTree->s_GetStat(stat, vals) << endl;
				
			}
		}
		if(direction == "SW"){
			if(southwestTree == NULL){
				cout << "failure" << endl;
			}
			else if(southwestTree->tile.size()==0){
				cout << "failure" << endl;
			}
			else if(southwestTree->tile.size()==1){
				
				if(attribute == "p")
					cout << stat << " " << this->southwestTree->p_GetStat(stat, vals) << endl;
				else if(attribute == "r")
					cout << stat << " " << this->southwestTree->r_GetStat(stat, vals) << endl;
				else if(attribute == "s")
					cout << stat << " " << this->southwestTree->s_GetStat(stat, vals) << endl;
				
			}
		}
		if(direction == "SE"){ 
			if(southeastTree == NULL){ //Checking for NULL is checking for if the node was subdivided
				cout << "failure" << endl;
			}
			else if(southeastTree->tile.size()==0){ //Checking for tile.size()==0 is checking for if a city is found in a node
				cout << "failure" << endl;
			}
			else if(southeastTree->tile.size()==1){
				
				if(attribute == "p")
					cout << stat << " " << this->southeastTree->p_GetStat(stat, vals) << endl;
				else if(attribute == "r")
					cout << stat << " " << this->southeastTree->r_GetStat(stat, vals) << endl;
				else if(attribute == "s")
					cout << stat << " " << this->southeastTree->s_GetStat(stat, vals) << endl;
				
			}
		}
	}
	
	else if((search_x < root_x)&&(search_y >= root_y)){
		this->northwestTree->query_attribute(p, direction, stat, attribute);
	}
	
	
	else if((search_x >= root_x)&&(search_y > root_y)){
		this->northeastTree->query_attribute(p, direction, stat, attribute);
	}
	
	
	else if((search_x <= root_x)&&(search_y < root_y)){
		this->southwestTree->query_attribute(p, direction, stat, attribute);
	}
	
	
	else if((search_x > root_x)&&(search_y <= root_y)){
		this->southeastTree->query_attribute(p, direction, stat, attribute);
	}
}

int QuadTree::p_GetStat(const string stat, vector<int> &values){ //Basically this function will run the print function on the tree called but store the values of the characteristic in a vector
	
	bool NW = (this->northwestTree == NULL); //Checking to see if the NW tree is subdivided
	bool NE = (this->northeastTree == NULL); //Checking to see if the NE tree is subdivided
	bool SW = (this->southwestTree == NULL); //Checking to see if the SW tree is subdivided
	bool SE = (this->southeastTree == NULL); //Checking to see if the SE tree is subdivided
	
	//If it is not subdivided, but contains a city, just display the name of the city
	if(((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1))&&(tile.size() == 1)){ 
		values.push_back(this->tile[0]->p);
	}
	
	//If it is subdivided, proceed to check if the tile size it has a city stored, recursively call the function and print the root of whichever subtree
	else if((!((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1)))&&(tile.size() == 1)){
		
		if((NE == 0)&&(northeastTree->tile.size() == 1))
			this->northeastTree->p_GetStat(stat, values);
		
		if((NW == 0)&&(northwestTree->tile.size() == 1))
			this->northwestTree->p_GetStat(stat, values);
		
		values.push_back(this->tile[0]->p);
		
		if((SW == 0)&&(southwestTree->tile.size() == 1))
			this->southwestTree->p_GetStat(stat, values);
		
		if((SE == 0)&&(southeastTree->tile.size() == 1))
			this->southeastTree->p_GetStat(stat, values);
	}
	
	if(stat == "min"){
		int minimum = *min_element(values.begin(), values.end());
		return minimum;
	}
	
	else if(stat == "max"){
		int maximum = *max_element(values.begin(), values.end());
		return maximum;
	}
	
	else if(stat == "total"){
		int sum = 0;
		
		for(int i = 0; i < values.size(); i++){
			sum = sum + values[i];
		}
		
		return sum;
	}

}

int QuadTree::r_GetStat(const string stat, vector<int> &values){

	bool NW = (this->northwestTree == NULL); //Checking to see if the NW tree is subdivided
	bool NE = (this->northeastTree == NULL); //Checking to see if the NE tree is subdivided
	bool SW = (this->southwestTree == NULL); //Checking to see if the SW tree is subdivided
	bool SE = (this->southeastTree == NULL); //Checking to see if the SE tree is subdivided
	
	//If it is not subdivided, but contains a city, just display the name of the city
	if(((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1))&&(tile.size() == 1)){ 
		values.push_back(this->tile[0]->r);
	}
	
	//If it is subdivided, proceed to check if the tile size it has a city stored, recursively call the function and print the root of whichever subtree
	else if((!((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1)))&&(tile.size() == 1)){
		
		if((NE == 0)&&(northeastTree->tile.size() == 1))
			this->northeastTree->r_GetStat(stat, values);
		
		if((NW == 0)&&(northwestTree->tile.size() == 1))
			this->northwestTree->r_GetStat(stat, values);
		
		values.push_back(this->tile[0]->r);
		
		if((SW == 0)&&(southwestTree->tile.size() == 1))
			this->southwestTree->r_GetStat(stat, values);
		
		if((SE == 0)&&(southeastTree->tile.size() == 1))
			this->southeastTree->r_GetStat(stat, values);
	}
	
	if(stat == "min"){
		int minimum = *min_element(values.begin(), values.end());
		return minimum;
	}
	
	else if(stat == "max"){
		int maximum = *max_element(values.begin(), values.end());
		return maximum;
	}
	
	else if(stat == "total"){
		int sum = 0;
		
		for(int i = 0; i < values.size(); i++){
			sum = sum + values[i];
		}
		
		return sum;
	}
}

int QuadTree::s_GetStat(const string stat, vector<int> &values){
	
	bool NW = (this->northwestTree == NULL); //Checking to see if the NW tree is subdivided
	bool NE = (this->northeastTree == NULL); //Checking to see if the NE tree is subdivided
	bool SW = (this->southwestTree == NULL); //Checking to see if the SW tree is subdivided
	bool SE = (this->southeastTree == NULL); //Checking to see if the SE tree is subdivided
	
	//If it is not subdivided, but contains a city, just display the name of the city
	if(((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1))&&(tile.size() == 1)){ 
		values.push_back(this->tile[0]->s);
	}
	
	//If it is subdivided, proceed to check if the tile size it has a city stored, recursively call the function and print the root of whichever subtree
	else if((!((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1)))&&(tile.size() == 1)){
		
		if((NE == 0)&&(northeastTree->tile.size() == 1))
			this->northeastTree->s_GetStat(stat, values);
		
		if((NW == 0)&&(northwestTree->tile.size() == 1))
			this->northwestTree->s_GetStat(stat, values);
		
		values.push_back(this->tile[0]->s);
		
		if((SW == 0)&&(southwestTree->tile.size() == 1))
			this->southwestTree->s_GetStat(stat, values);
		
		if((SE == 0)&&(southeastTree->tile.size() == 1))
			this->southeastTree->s_GetStat(stat, values);
	}
	
	if(stat == "min"){
		int minimum = *min_element(values.begin(), values.end());
		return minimum;
	}
	
	else if(stat == "max"){
		int maximum = *max_element(values.begin(), values.end());
		return maximum;
	}
	
	else if(stat == "total"){
		int sum = 0;
		
		for(int i = 0; i < values.size(); i++){
			sum = sum + values[i];
		}
		
		return sum;
	}
}

void QuadTree::clear(){
	if(!tile.empty()){
		tile.clear();
	}
	
	northwestTree = NULL;
	northeastTree = NULL;
	southwestTree = NULL;
	southeastTree = NULL;
}

int QuadTree::size(int &initial_size){
	
	bool NW = (this->northwestTree == NULL); //Checking to see if the NW tree is subdivided
	bool NE = (this->northeastTree == NULL); //Checking to see if the NE tree is subdivided
	bool SW = (this->southwestTree == NULL); //Checking to see if the SW tree is subdivided
	bool SE = (this->southeastTree == NULL); //Checking to see if the SE tree is subdivided
	
	//If it is equal to NULL, that means that it is not subdivided
	if((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1)){
		if(tile.size() == 0){ //Check to see if a city is stored in that node
			initial_size = 0; //If no, the size will be 0 and therefore you will return a size 0 (This only works for a quadtree which has no elements at all)
			return initial_size;
		}
		else if(tile.size() == 1) //Check to see if a city is stored in that node
			initial_size = initial_size + 1;  //If yes, increment the size of the quadtree
	}
	else{
		if((tile.size() == 1)){ //If the tree is subdivided and that node has a city stored
			initial_size = initial_size + 1; //Increment the size 
			
			//Continue by checking to see if each subtree is further subdivided and contains a city and recursively calling the function
			
			if((NW == 0)&&(northwestTree->tile.size() == 1))
				this->northwestTree->size(initial_size);
			
			if((NE == 0)&&(northeastTree->tile.size() == 1))
				this->northeastTree->size(initial_size);
			
			if((SW == 0)&&(southwestTree->tile.size() == 1))
				this->southwestTree->size(initial_size);
			
			if((SE == 0)&&(southeastTree->tile.size() == 1))
				this->southeastTree->size(initial_size);
		}
	}
	
	return initial_size;
}

void QuadTree::print(){
	
	bool NW = (this->northwestTree == NULL); //Checking to see if the NW tree is subdivided
	bool NE = (this->northeastTree == NULL); //Checking to see if the NE tree is subdivided
	bool SW = (this->southwestTree == NULL); //Checking to see if the SW tree is subdivided
	bool SE = (this->southeastTree == NULL); //Checking to see if the SE tree is subdivided
	
	//If it is not subdivided, but contains a city, just display the name of the city
	if(((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1))&&(tile.size() == 1)){ 
		cout << this->tile[0]->city << " ";
	}
	
	//If it is subdivided, proceed to check if the tile size it has a city stored, recursively call the function and print the root of whichever subtree
	else if((!((NW == 1)&&(NE == 1)&&(SW == 1)&&(SE == 1)))&&(tile.size() == 1)){
		
		if((NE == 0)&&(northeastTree->tile.size() == 1))
			this->northeastTree->print();
		
		if((NW == 0)&&(northwestTree->tile.size() == 1))
			this->northwestTree->print();
		
		cout << this->tile[0]->city << " ";
		
		if((SW == 0)&&(southwestTree->tile.size() == 1))
			this->southwestTree->print();
		
		if((SE == 0)&&(southeastTree->tile.size() == 1))
			this->southeastTree->print();
	}
}
			
					
	