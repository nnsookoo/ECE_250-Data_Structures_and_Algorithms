#include <iostream>
#include <string>
#include <vector>

#include "HashNodeOpen.h"

class HashTable {
	private: 
		vector <HashNode*> hash_table;
		int max_size;
		int cur_size;
	public:
		HashTable();
		
		~HashTable();
		
		void destroy();
		
		int HashFunction(const int val);
		
		bool isFull();
		
		bool init(const int m);
		
		bool insert(const int k);
		
		bool search(const int k);
		
		int returnIndex(const int k);
		
		bool remove(const int k);
		
};