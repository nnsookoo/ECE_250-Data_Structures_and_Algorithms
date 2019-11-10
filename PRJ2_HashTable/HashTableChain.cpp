#include <iostream>
#include <string>

#include "HashTableChain.h"

HashTable::HashTable(){
	//Construct an empty hashtable with no constraints
	size = 0;
	
	//cout << "A new hash table was created" << endl;
}
		
HashTable::~HashTable(){
	destroy();
}
		
void HashTable::destroy(){
	
	if(!(isEmpty())){
		//Start with deleting objects of linked list first then array
		for(int i = 0; i < size; i++){
			if(hash_table[i] != NULL){ //If it does not have a linked list attached
				HashNode* ptr = hash_table[i];
	
				while(ptr != NULL){
					HashNode* tmp = ptr;
					ptr = ptr->next;
					delete tmp;
				}
				
				hash_table[i] = NULL;
				
				size = 0;
			}
		}
		delete[] hash_table;
		//cout << "Hash Table was reinitialized" << endl;
	}
	//else
		//cout << "Hash Table was not empty. Therefore it was not reinitialized" << endl;
	
	/*for(int i = 0; i < size; i++){
		HashNode* slot = hash_table[i];
		
		cout << "Main slot " << i << endl;
		
		int j = 0;
		
		while(slot != NULL){
			cout << "Object " << j << ": " << slot->key << endl;
			slot = slot->next;
			j++;
		}
	}*/
}
		

bool HashTable::isEmpty(){
	
	bool empty = 1;
	
	for(int i = 0; i < this->size; i++){
		if(hash_table[i] == NULL){
			empty = empty&&1;
		}
	}
	
	/*if(empty == 1)
		cout << "Hash Table is empty" << endl;
	else
		cout << "Hash Table is not empty" << endl;
	*/
	return empty;
}

int HashTable::HashFunction(const int val){
//Calculates the indexing using the hash function
//returns the index

	int index = val%size;
	//cout << "Index generated through hash function is " << index << endl;
	return index;
}

bool HashTable::init(const int m){
	
	//Check if the hashtable is empty. If it isn't, delete all elements
	destroy();
	
	//Initialize the maximum capacity
	//returns true if the initialization was successful
	size = m;
	
	hash_table = new HashNode*[size];
	
	for(int i = 0; i < size; i++)
		hash_table[i] = NULL;
	
	//cout << "Maximum size is " << m << endl;
	
	//cout << "Hashtable is: " << endl;
	
	/*for(int i = 0; i < m; i++){
		cout << hash_table[i]->key << " " << hash_table[i]->occupied << endl;
	}*/
	
/*	for(int i = 0; i < size; i++){
		HashNode* slot = hash_table[i];
		
		cout << "Main slot " << i << endl;
		
		int j = 0;
		
		while(slot != NULL){
			cout << "Object " << j << ": " << slot->key << endl;
			slot = slot->next;
			j++;
		}
	}*/
	
	return true;
	
}

bool HashTable::insert(const int k){
	
	//First we need to check if the hash table is already filled
	//In the hashing using chaining, the table can never be filled
	
	//Use the hash function to find the index in which
	//the given key should be placed
	
	int index = HashFunction(k);
	HashNode *to_insert = new HashNode(k); //Create a new node
	//cout << "here1" << endl;
	//cout << "I want to insert at index: " << index << endl;
	
	//If that entry is NULL, we can insert right there into hash_table[index]
	if(hash_table[index] == NULL){
		hash_table[index] = to_insert;
		return true;
	}
	else if(search(k))
		return false;
	else{ //Find the next free space along the linked list
		HashNode *slot = hash_table[index]; //Using the linked list at that index
		//Iterate through list to find the next available node
		while(slot->next != NULL)
			slot = slot->next;
		//When you finally get the empty slot
		if(slot->key == k){
			//cout << "Object " << k << " already found" << endl;
			return false;
		}
		else
			slot->next = to_insert;
	}
	
/*	for(int i = 0; i < size; i++){
		HashNode* slot = hash_table[i];
		
		cout << "Main slot " << i << endl;
		
		int j = 0;
		
		while(slot != NULL){
			cout << "Object " << j << ": " << slot->key << endl;
			slot = slot->next;
			j++;
		}
	}*/
	
	return true;
	
}

bool HashTable::search(const int k){
	
	int index = HashFunction(k);
	
	//Go to that slot in the hash_table, that is, hash_table[index]
	//Iterate through linked list to find object
	
	HashNode *slot = hash_table[index];
	 
	if(hash_table[index] == NULL)
		return false;
	else{
		while((slot->key != k)&&(slot->next != NULL)){
			slot = slot->next;
		}
		if(slot->key == k)
			return true;
		else if(slot->next == NULL)
			return false;
	}
	
	/*HashNode *previous_slot = NULL;
	HashNode *current_slot = hash_table[index];
	
	if(hash_table[index] == NULL){
		cout << "here1" << endl;
		return false;
	}
	else if((current_slot->key == k)&&(current_slot->next == NULL)){
		cout << "here2" << endl;
		return true;
	}
	else if((current_slot->key != k)&&(current_slot->next == NULL)){
		cout << "here3" << endl;
		return false;
	}
	else if((current_slot->key != k)&&(current_slot->next != NULL)){
		cout << "here4" << endl;
		while((current_slot->next != NULL)&&(current_slot->key != k)){
			previous_slot = current_slot;
			current_slot = current_slot->next; //Find the previous slot
		}

		if(current_slot->key == k){
			/*for(int i = 0; i < size; i++){
				HashNode* slot = hash_table[i];
				
				cout << "Main slot " << i << endl;
				
				int j = 0;
				
				while(slot != NULL){
					cout << "Object " << j << ": " << slot->key << endl;
					slot = slot->next;
					j++;
				}
			}
			return true;
		}
	}*/
	
	//return false;
	
}

int HashTable::returnIndex(const int k){
	
	int index = HashFunction(k);
	
	return index;
	
}

bool HashTable::remove(const int k){
	
	int index = HashFunction(k);
	
	//Go to that slot in the hash_table, that is, hash_table[index]
	//Iterate through linked list to find object
	
	//If object is found at the end of the list, we can easily remove
	//If the object is found at the middle of the list, 
	HashNode *previous_slot = NULL;
	HashNode *current_slot = hash_table[index];
	
	if(hash_table[index] == NULL)
		return false;
	
	while((current_slot->next != NULL)&&(current_slot->key != k)){
		previous_slot = current_slot;
		current_slot = current_slot->next; //Find the previous slot
	}
	
	if(current_slot->key == k){
			HashNode *next_reallocation = current_slot->next;
			delete current_slot;
		if(previous_slot != NULL){
			previous_slot->next = next_reallocation;
		}
		else if(previous_slot == NULL){
			hash_table[index] = next_reallocation;
		}
		
		/*for(int i = 0; i < size; i++){
			HashNode* slot = hash_table[i];
			
			cout << "Main slot " << i << endl;
			
			int j = 0;
			
			while(slot != NULL){
				cout << "Object " << j << ": " << slot->key << endl;
				slot = slot->next;
				j++;
			}
		}*/
		return true;
	}
	
	return false;
}
	
