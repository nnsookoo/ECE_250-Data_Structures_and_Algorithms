#include <iostream>
#include <vector>
#include <string>

#include "HashTableOpen.h"

HashTable::HashTable(){
	//Construct an empty hashtable with no constraints
	cur_size = 0;
	
	//cout << "A new hash table was created" << endl;
}
		
HashTable::~HashTable(){
	destroy();
}
		
void HashTable::destroy(){
	
	if(!(this->hash_table.empty())){
		HashNode* to_replace = new HashNode;
		to_replace->key = 0;
		to_replace->occupied = -1;
		to_replace->used = -1;
		
		for(int i = 0; i < max_size; i++){
			hash_table[i] = to_replace;
		}
		this->cur_size = 0;
		
		//cout << "Hash table was reinitialized" << endl;
	}
}
		
int HashTable::HashFunction(const int val){
//Calculates the indexing using the hash function
//returns the index

	int index = val%max_size;
	//cout << "Index generated through hash function is " << index << endl;
	return index;
}
		
bool HashTable::isFull(){
			//cout << "Maximum size is " << max_size << " and current size is " << cur_size << endl;
	return max_size == cur_size;
}

bool HashTable::init(const int m){
	
	//Check if the hashtable is empty. If it isn't, delete all elements
	destroy();
	
	//Initialize the maximum capacity
	//returns true if the initialization was successful
	max_size = m;
	
	HashNode* empty = new HashNode;
					
	for(int i = 0; i < m; i++){
		hash_table.push_back(empty); //initialize entire vector
	}
	
	//cout << "Maximum size is " << m << endl;
	
	//cout << "Hashtable is: " << endl;
	
	/*for(int i = 0; i < m; i++){
		cout << hash_table[i]->key << " " << hash_table[i]->occupied << endl;
	}*/
	
	return true;
	
}

bool HashTable::insert(const int k){
	
	//First we need to check if the hash table is already filled
	
	if(isFull()){
		//cout << "The table is full" << endl;
		return false;
	}
	if(search(k)){
		return false;
	}
	
	//Use the hash function to find the index in which
	//the given key should be placed
	
	int index = HashFunction(k);
	
	//cout << "here1" << endl;
	//cout << "I want to insert at index: " << index << endl;
	
	//Find the next free space
	//If that slot is occupied and does not contain the same value,
	//increment the index.
	//But you must perform the modulo operation onto the index with max_size
	//as the index after incrementing can be more than the max_size
	
	//cout << "occupied" << hash_table[0]->occupied << endl;
	
	while(hash_table[index]->occupied == 1){
		//cout << "This slot is already filled with " << hash_table[index]->key << endl;
		index++;
		index = index%max_size; // If the index after incrementing is more than the max_size
		
		if(hash_table[index]->key==k){
			//cout << "Object " << k << " already found" << endl;
			return false;
			break;
		}
			

		//cout << "Going to index: " << index << endl;
	}
	

	HashNode* to_add = new HashNode(k,1);
	
	//cout << "Created a new node with key " << to_add->key << " and occupied status " << to_add->occupied << endl;
	
	this->hash_table[index] = to_add;
	
	//cout << "Slot at index " << index << " now has a key of " << hash_table[index]->key << " with occupied status " << hash_table[index]->occupied << endl;
	
	this->cur_size++;
	
	//cout << "Inserted object " << k << ". Current size is now " << cur_size << endl;
	
	//cout << "Hashtable is: " << endl;
	
	//for(int i = 0; i < max_size; i++){
	//	cout << hash_table[i]->key << " " << hash_table[i]->occupied << endl;
	//}
	
	return true;
	
}

bool HashTable::search(const int k){
	
	int index = HashFunction(k);
	int i = 0;
	
	while(i < max_size){
		if((hash_table[index]->key == k)&&(hash_table[index]->occupied == 1)){
			return true;
		}
		//cout << "This slot is already filled with " << hash_table[index]->key << endl;
		if(hash_table[index]->used == -1)
			return false;
		
		index++;
		index = index%max_size;
		i++;
		
		//cout << "Going to index " << index << endl;
	}
	
	return false;
	
}

int HashTable::returnIndex(const int k){
	
	int index = HashFunction(k);
	int i = 0;
	
	while(i < max_size){
		if((hash_table[index]->key == k)&&(hash_table[index]->occupied == 1)){
			return index;
		}
		index++;
		index = index%max_size;
		i++;
	}
	
}

bool HashTable::remove(const int k){
	
	if(search(k) == false)
		return false;
	
	//Using the same idea as searching for the key
	int index = HashFunction(k);
	int i = 0;
	
	while(i < max_size){
		if((hash_table[index]->key == k)&&(hash_table[index]->occupied == 1)){
			hash_table[index]->key = 0;
			hash_table[index]->occupied = -1;
			cur_size--;
			
			//cout << "Hashtable is: " << endl;
	/*
			for(int i = 0; i < max_size; i++){
				cout << hash_table[i]->key << " " << hash_table[i]->occupied << endl;
			}
	*/
			return true;
		}
		index++;
		index = index%max_size;
		i++;
	}
	
	return false;
		
}
