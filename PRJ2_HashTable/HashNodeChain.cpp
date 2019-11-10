#include <iostream>
#include <string>

#include "HashNodeChain.h"

using namespace std;

HashNode::HashNode(){
	this->key = 0;
	//this->occupied = -1; //If that slot is not occupied as yet, assign it a value of -1
	this->next = NULL;
	//cout << "A new node was made in which key was 0 and occupied was -1" << endl;
}


HashNode::HashNode(const int& key){
	this->key = key;
	//this->occupied = occupied;
	this->next = NULL;
}
		
HashNode::~HashNode(){
	this->key = 0;
	//this->occupied = -1;
	this->next = NULL;
	
	//cout << "Node was destroyed" << endl;
}

