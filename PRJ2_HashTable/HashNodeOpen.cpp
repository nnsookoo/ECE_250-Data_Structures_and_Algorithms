#include "HashNodeOpen.h"

using namespace std;

HashNode::HashNode(){
	this->key = 0;
	this->occupied = -1; //If that slot is not occupied as yet, assign it a value of -1
	this->used = -1;
	//cout << "A new node was made in which key was 0 and occupied was -1" << endl;
}


HashNode::HashNode(const int& key, const int& occupied){
	this->key = key;
	this->occupied = occupied;
	this->used = 1;
}
		
HashNode::~HashNode(){
	this->key = 0;
	this->occupied = -1;
	this->used = 1;
	
	//cout << "Node was destroyed" << endl;
}

