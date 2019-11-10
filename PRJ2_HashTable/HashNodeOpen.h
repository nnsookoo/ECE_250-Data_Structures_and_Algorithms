#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HashNode { 
	public:
		int key;
		int occupied;
		int used;
		
		HashNode();
		HashNode(const int& key, const int& occupied);
		~HashNode();
};