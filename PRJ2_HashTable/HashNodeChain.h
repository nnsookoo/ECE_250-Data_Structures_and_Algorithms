#include <iostream>
#include <string>

using namespace std;

class HashNode { 
	public:
		int key;
		//int occupied;
		HashNode* next;
		
		HashNode();
		HashNode(const int& key);
		~HashNode();
};