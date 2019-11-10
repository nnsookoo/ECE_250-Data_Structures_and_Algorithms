#include <iostream>
#include <string>

#include "HashNodeChain.h"

class HashTable {
	private: 
		HashNode **hash_table;
		int size; //size of hashtable
	public:
		HashTable();
		
		~HashTable();
		
		void destroy();
		
		bool isEmpty();
		
		int HashFunction(const int val);
		
		bool init(const int m);
		
		bool insert(const int k);
		
		bool search(const int k);
		
		int returnIndex(const int k);
		
		bool remove(const int k);
		
};