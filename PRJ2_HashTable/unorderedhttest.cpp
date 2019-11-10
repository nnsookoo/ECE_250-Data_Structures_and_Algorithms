#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "HashTableChain.h"

int main(){
	
	string oneline;
	HashTable hashtable;
	
	while(!cin.eof()){
		string ws_delim = " ";
		
		getline(cin, oneline); //Get the line from standard input
		
		//cout << "string received: " << oneline << endl;
		
		int length_of_line = oneline.length(); //Calculate the length of the line for future reference
		
		string copy;
		copy = oneline; // Make a copy of the line received so as to not change the contents of the original line received
		
		//cout << "copy: " << copy << endl; //Check to see if the strings copied well
		
		size_t pos_whitespace = copy.find(ws_delim); //Find the position of the first whitespace
		
		//cout << pos << endl; //Check to see if the position is correct
		
		string command = copy.substr(0,pos_whitespace); //Copy over the contents from the first position to the position of the whitespace
		copy.erase(0, pos_whitespace + ws_delim.length());
		
		//cout << "COMMAND IS: " << command << endl;
		
		if(command.compare("n")==0){
			
			string initialize = copy.substr(0, length_of_line);
			
			stringstream ini(initialize);
			
			int i = 0;
			
			ini >> i;
			
			//cout << "Size to initialize: " << i << endl;
			
			if(hashtable.init(i)){
				cout << "success" << endl;
			}
			else
				cout << "could not erase " << i << endl;
			
			//hashtable.print();
			//cout << endl;
		}
		
		else if(command.compare("i")==0){
			
			string ins = copy.substr(0, length_of_line);
			
			stringstream ad(ins);
			
			int p = 0;
			
			ad >> p;
			
			//cout << "Key to insert: " << p << endl;
			
			if(hashtable.insert(p)){
				cout << "success" << endl;
			}
			else
				cout << "failure " << endl;
			
			//hashtable.print();
			//cout << endl;
		}
		
		else if(command.compare("s")==0){
			
			string sea = copy.substr(0, length_of_line);
			
			stringstream fin(sea);
			
			int s = 0;
			
			fin >> s;
			
			//cout << "Search for: " << s << endl;
			
			if(hashtable.search(s)){
				int index = hashtable.returnIndex(s);
				cout << "found in " << index << endl;
			}
			else
				cout << "not found" << endl;
			
			//hashtable.print();
			//cout << endl;
		}
		
		else if(command.compare("d")==0){
			
			string del = copy.substr(0, length_of_line);	
			
			stringstream rem(del);
			
			int d = 0;
			
			rem >> d;
			
			//cout << "Key to delete: " << d << endl;
			
			if(hashtable.remove(d)){
				cout << "success" << endl;
			}
			else
				cout << "failure" << endl;
			
			//hashtable.print();
			//cout << endl;
		}
	}

	return 0;
}